#include "memory_table_manager.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <sstream>
#include <iostream>

MemoryTableManager::MemoryTableManager(QTabWidget *tabWidget, int maxTabs, int rowCount, QObject *parent)
    : QObject(parent), tab_widget(tabWidget), max_tabs(maxTabs), row_count(rowCount), table_signals_blocked(false)
{
    setup_tab_widget();
    connect(tab_widget, &QTabWidget::currentChanged, this, [this](int index) { handle_tab_changed(index); });
    connect(tab_widget->tabBar(), &QTabBar::tabCloseRequested, this, [this](int index) { handle_tab_close(index); });

}

MemoryTableManager::~MemoryTableManager(){
    for (auto widget : memory_table_widgets){
        delete widget;
    }
    for (int i = memory_tables_data.size() - 1; i > 0; --i){
        memory_tables_data.erase(memory_tables_data.begin() + i);
    }
}


void MemoryTableManager::setup_tab_widget() {
    tab_widget->setTabsClosable(true);
    tab_widget->tabBar()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    active_table_widget = nullptr;
    active_table_data = nullptr;

    memory_tables_data.resize(max_tabs);
    for (int i = 0; i <= max_tabs; ++i) {
        memory_tables_data[i].resize(row_count, "+000000");

        QTableWidget *table_widget = new QTableWidget(row_count, 2, tab_widget);
        format_table_widget(table_widget, memory_tables_data[i]);
        memory_table_widgets.push_back(table_widget);

        memory_tables_data.emplace_back(std::vector<std::string>(row_count, "+000000"));

        connect(table_widget, &QTableWidget::itemChanged, this, &MemoryTableManager::handle_item_changed);

        table_widget->hide();
    }

    if (tab_widget->count()>1){
        for(int i = tab_widget->count() - 2; i > 0; --i){
            tab_widget->removeTab(i);
        }
    }

    add_new_tab();

    active_table_widget = memory_table_widgets[0];
    active_table_data = &memory_tables_data[0];
}

void MemoryTableManager::set_row_count(int count) {
    if(memory_tables_data.size() != memory_table_widgets.size()) {
        throw std::runtime_error("Set Row Count Error: Fatal data encountered.");
    }

    row_count = count;

    for (size_t i = 0; i < memory_table_widgets.size(); ++i) {
        memory_table_widgets[i]->setRowCount(row_count);
        memory_tables_data[i].resize(row_count, "+000000");
    }
    update_tabs();
}

void MemoryTableManager::format_table_widget(QTableWidget* table_widget, std::vector<std::string>& table_data){
    table_widget->setRowCount(row_count);

    QStringList headers = {"Memory Address", "Instruction"};
    table_widget->verticalHeader()->setVisible(false);
    table_widget->setHorizontalHeaderLabels(headers);
    table_widget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table_widget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    table_widget->installEventFilter(this);
    table_widget->horizontalHeader()->setSectionsClickable(false);
    table_widget->horizontalHeader()->setSectionsMovable(false);

    for (int instruction_index = 0; instruction_index < row_count; ++instruction_index) {
        QString memory_address = QString("%1:").arg(instruction_index, 3, 10, QChar('0'));
        QTableWidgetItem *address_item = new QTableWidgetItem(memory_address);
        address_item->setFlags(address_item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
        address_item->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        table_widget->setItem(instruction_index, 0, address_item);

        QTableWidgetItem *instruction_item = new QTableWidgetItem(QString::fromStdString(table_data[instruction_index]));
        instruction_item->setTextAlignment(Qt::AlignVCenter | Qt::AlignCenter);
        instruction_item->setFlags(instruction_item->flags() & ~Qt::ItemIsSelectable);
        table_widget->setItem(instruction_index, 1, instruction_item);
    }

    for (int column = 0; column < table_widget->columnCount(); ++column) {
        QTableWidgetItem *header_item = table_widget->horizontalHeaderItem(column);
        if (header_item) {
            header_item->setFlags(header_item->flags() & ~Qt::ItemIsSelectable);
        }
    }
}

void MemoryTableManager::update_active_table() {
    int current_index = tab_widget->currentIndex();
    if(current_index < 0 || current_index > static_cast<int>(memory_table_widgets.size())) {
        throw std::out_of_range("Update Table Error: Current memory table index[" + std::to_string(current_index) + "] out of range.");
    }

    active_table_widget = memory_table_widgets[current_index];
    active_table_data = &memory_tables_data[current_index];

    active_table_widget->viewport()->update();
}

void MemoryTableManager::set_editable_flag(bool editable) {
    for (int instruction_index = 0; instruction_index < row_count; ++instruction_index) {
        QTableWidgetItem *item = active_table_widget->item(instruction_index, 1); // Column 1: Instruction
        if (item) {
            (editable) ? item->setFlags(item->flags() | Qt::ItemIsEditable) : item->setFlags(item->flags() & ~Qt::ItemIsEditable);
        }
    }
    active_table_widget->viewport()->update();
}

void MemoryTableManager::set_input_block_signals_flag(bool is_blocked) {
    table_signals_blocked = is_blocked;
    for (auto tableWidget : memory_table_widgets) {
        tableWidget->blockSignals(is_blocked);
    }
}

void MemoryTableManager::set_tab_block_signals_flag(bool is_blocked) {
    tab_signals_blocked = is_blocked;
    tab_widget->blockSignals(is_blocked);
}

void MemoryTableManager::reset_data(size_t start_index, size_t end_index) {
    reset_data(tab_widget->currentIndex(), start_index, end_index);
}

void MemoryTableManager::reset_data(size_t table_index, size_t start_index, size_t end_index) {
    if (end_index > static_cast<size_t>(row_count)) {
        end_index = static_cast<size_t>(row_count);
    }

    if (start_index > end_index) {
        std::ostringstream throw_context;
        throw_context << "Reset Instruction Vector Error: The passed start index '" << start_index
                      << "' is beyond the end index '" << end_index << "'";
        throw std::out_of_range(throw_context.str());
    }

    std::string default_instruction = "+000000";
    for (size_t instruction_index = start_index; instruction_index < end_index; ++instruction_index) {
        if (instruction_index >= memory_tables_data[table_index].size()) {
            memory_tables_data[table_index].push_back(default_instruction);
        } else if (memory_tables_data[table_index][instruction_index] != default_instruction) {
            memory_tables_data[table_index][instruction_index] = default_instruction;
        }

        QTableWidgetItem *item = memory_table_widgets[table_index]->item(instruction_index, 1);
        if (item) {
            item->setText(QString::fromStdString(memory_tables_data[table_index][instruction_index]));
        }
    }
}

void MemoryTableManager::set_data(size_t index, const std::string &incoming_data) {
    if (index >= active_table_data->size()) {
        std::ostringstream context;
        context << "Set Instruction Error: The provided index '" << index
                << "' is outside the expected range of [0-" << active_table_data->size() - 1 << "]";
        throw std::out_of_range(context.str());
    }

    memory_tables_data[tab_widget->currentIndex()][index] = incoming_data;

    QTableWidgetItem *item = active_table_widget->item(index, 1);
    if (item) {
        item->setText(QString::fromStdString((*active_table_data)[index]));
    }

    update_active_table();
}

const std::vector<std::string>& MemoryTableManager::get_data() {
    return *active_table_data;
}

void MemoryTableManager::add_new_tab() {
    set_tab_block_signals_flag(true);

    int tab_count = tab_widget->count();
    if (tab_count >= max_tabs) {
        set_tab_block_signals_flag(false);
        return;
    }

    int tab_index = 0;
    if (tab_count > 0){
        tab_index = tab_count - 1;
        tab_widget->removeTab(tab_index);
    }

    QTableWidget *table_widget = memory_table_widgets[tab_index];
    tab_index = tab_widget->addTab(table_widget, QString("tab"));

    qDebug() << "CREATED TAB AT: " << tab_index;

    QWidget *create_tab = new QWidget();
    int create_tab_index = tab_widget->addTab(create_tab, "+");
    tab_widget->tabBar()->setTabButton(create_tab_index, QTabBar::RightSide, nullptr);

    set_tab_block_signals_flag(false);

    tab_widget->setCurrentIndex(tab_widget->count()-2);

    update_tabs();

}

void MemoryTableManager::update_tabs() {
    set_tab_block_signals_flag(true);
    int tab_count = tab_widget->count();
    if (tab_count > 2){
        for (int i = 0; i < tab_count - 1; ++i) {
            QPushButton *close_button = new QPushButton("x");
            close_button->setFixedSize(16, 16);
            tab_widget->tabBar()->setTabButton(i, QTabBar::RightSide, close_button);
            connect(close_button, &QPushButton::clicked, this, [this, i]() { handle_tab_close(i); });
        }
    } else {
        tab_widget->tabBar()->setTabButton(0, QTabBar::RightSide, nullptr);
    }

    for (int i = tab_widget->count() - 2; i >= 0; --i) {
        tab_widget->setTabText(i, QString("Script %1").arg(i + 1));
    }

    if (tab_count == max_tabs) {
        tab_widget->removeTab(tab_count - 1);
        tab_widget->setCurrentIndex(tab_count - 2);
    }
    set_tab_block_signals_flag(false);
}

void MemoryTableManager::handle_item_changed(QTableWidgetItem *item) {
    if (!table_signals_blocked) {
        emit input_submitted(item);
    }
}

void MemoryTableManager::handle_tab_changed(int index) {
    if (!tab_signals_blocked){
        set_tab_block_signals_flag(true);
        qDebug() << "handle_tab_changed index passed: " << index;
        int tab_count = tab_widget->count();
        if(tab_count - 1 == index && tab_widget->tabText(index) == "+"){
            add_new_tab();
        }
        set_tab_block_signals_flag(false);

        update_active_table();
    }
}

void MemoryTableManager::handle_tab_close(int index) {
    qDebug() << "handle_tab_close index passed: " << index;
    set_tab_block_signals_flag(true);

    int tab_count = tab_widget->count();

    // Prevent closing the first tab (count 2 should mean 1 script tab + the create tab) or the last (should be the create tab) tab
    if (index == 0 && tab_count < 2) {
        set_tab_block_signals_flag(false);
        return;
    }

    if (static_cast<size_t>(index) > memory_table_widgets.size()) {
        throw std::out_of_range("Tab Closing Error: Error attempting to close tab[" + std::to_string(index) + "].");
    }
    memory_tables_data.erase(memory_tables_data.begin() + index);
    memory_tables_data.emplace_back(std::vector<std::string>(row_count, "+000000"));

    qDebug() << "REMOVING INDEX: " << index;

    tab_widget->removeTab(index);
    tab_count = tab_widget->count();

    memory_table_widgets.erase(memory_table_widgets.begin() + index);
    QTableWidget *table_widget = new QTableWidget(row_count, 2, tab_widget);
    format_table_widget(table_widget, memory_tables_data[memory_tables_data.size() - 1]);
    memory_table_widgets.push_back(table_widget);

    int current_tab = -1;
    int selected_tab = -1;
    qDebug() << "TAB COUNT: " << tab_count << "MAX: " << max_tabs - 1;
    if (tab_count == max_tabs - 2 && tab_widget->tabText(tab_count - 1) != "+"){
        qDebug() << "adding +: " << max_tabs - 1;
        QWidget *create_tab = new QWidget();
        int create_tab_index = tab_widget->addTab(create_tab, "+");
        tab_widget->tabBar()->setTabButton(create_tab_index, QTabBar::RightSide, nullptr);

        tab_count = tab_widget->count();
        current_tab = tab_widget->currentIndex();
        selected_tab = (index > 0) ?
                               (current_tab == tab_count - 1) ? current_tab - 2 : current_tab : 0;
    } else{
        current_tab = tab_widget->currentIndex();
        selected_tab = (index > 0) ?
                           (current_tab == tab_count - 1) ? current_tab - 1 : current_tab : 0;

    }

    for (int i = index; i < tab_count - 1; ++i) {
        tab_widget->removeTab(i);
        QTableWidget *table_widget = memory_table_widgets[i];
        tab_widget->insertTab(i, table_widget, QString("Script "));
    }
    set_tab_block_signals_flag(false);

    tab_widget->setCurrentIndex(selected_tab);

    update_tabs();
}

bool MemoryTableManager::eventFilter(QObject *obj, QEvent *event) {
    if (obj == active_table_widget && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Tab && !keyEvent->modifiers().testFlag(Qt::ShiftModifier)) {
            QTableWidgetItem *currentItem = active_table_widget->currentItem();
            if (currentItem && currentItem->column() == 1) {
                int currentRow = currentItem->row();
                int nextRow = (currentRow + 1) % row_count;
                active_table_widget->setCurrentItem(active_table_widget->item(nextRow, 1));
                return true;
            }
        } else if (keyEvent->key() == Qt::Key_Backtab) { // Shift+Tab is represented by Qt::Key_Backtab
            QTableWidgetItem *currentItem = active_table_widget->currentItem();
            if (currentItem && currentItem->column() == 1) {
                int currentRow = currentItem->row();
                int prevRow = (currentRow - 1 + row_count) % row_count;
                active_table_widget->setCurrentItem(active_table_widget->item(prevRow, 1));
                return true;
            }
        }
    }
    return QObject::eventFilter(obj, event);
}
