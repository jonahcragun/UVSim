#include "memory_table_manager.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QPushButton>
#include <sstream>
#include <iostream>

MemoryTableManager::MemoryTableManager(QTabWidget *tabWidget, int rowCount, QObject *parent)
    : QObject(parent), tab_widget(tabWidget), row_count(rowCount), signals_blocked(false)
{
    setup_tab_widget();
    connect(tab_widget, &QTabWidget::currentChanged, this, &MemoryTableManager::handle_tab_changed);
    connect(tab_widget->tabBar(), &QTabBar::tabCloseRequested, this, &MemoryTableManager::handle_tab_close);
    add_create_tab();
}


void MemoryTableManager::setup_tab_widget() {
    tab_widget->setTabsClosable(true);
    tab_widget->tabBar()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    active_memory_table_widget = nullptr;
    active_memory_table_data = nullptr;
    if (tab_widget->count()>0){
        for(int i = tab_widget->count() - 1; i > 0; --i){
            tab_widget->removeTab(i);
        }
    }
    // Initialize the first memory table
    add_new_tab();
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
    update();
}

void MemoryTableManager::update() {
    int current_index = tab_widget->currentIndex();
    if(current_index < 0 || current_index > static_cast<int>(memory_table_widgets.size())) {
        throw std::out_of_range("Update Table Error: Current memory table index[" + std::to_string(current_index) + "] out of range.");
    }

    active_memory_table_widget = memory_table_widgets[current_index];
    active_memory_table_data = &memory_tables_data[current_index];
    update_active_memory_table();
}

void MemoryTableManager::update_active_memory_table() {
    if (active_memory_table_data->size() != static_cast<size_t>(row_count)) {
        std::ostringstream throw_context;
        throw_context << "Update Table Error: Table size '" << row_count << "' and instruction count '"
                      << active_memory_table_data->size() << "' mismatch.";
        throw std::out_of_range(throw_context.str());
    }

    for (int instruction_index = 0; instruction_index < row_count; ++instruction_index) {
        QString memory_address = QString("%1:").arg(instruction_index, 3, 10, QChar('0'));
        QTableWidgetItem *address_item = new QTableWidgetItem(memory_address);
        address_item->setFlags(address_item->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
        address_item->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        active_memory_table_widget->setItem(instruction_index, 0, address_item);

        QTableWidgetItem *instruction_item = new QTableWidgetItem(QString::fromStdString((*active_memory_table_data)[instruction_index]));
        instruction_item->setTextAlignment(Qt::AlignVCenter | Qt::AlignCenter);
        instruction_item->setFlags(instruction_item->flags() & ~Qt::ItemIsSelectable);
        active_memory_table_widget->setItem(instruction_index, 1, instruction_item);
    }
    active_memory_table_widget->viewport()->update();
}

void MemoryTableManager::update_headers(QTableWidget *memory_table_widget) {
    for (int column = 0; column < memory_table_widget->columnCount(); ++column) {
        QTableWidgetItem *header_item = memory_table_widget->horizontalHeaderItem(column);
        if (header_item) {
            header_item->setFlags(header_item->flags() & ~Qt::ItemIsSelectable);
        }
    }
}

void MemoryTableManager::set_editable_flag(bool editable) {
    for (int instruction_index = 0; instruction_index < row_count; ++instruction_index) {
        QTableWidgetItem *item = active_memory_table_widget->item(instruction_index, 1); // Column 1: Instruction
        if (item) {
            if (editable) {
                item->setFlags(item->flags() | Qt::ItemIsEditable);
            } else {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
    active_memory_table_widget->viewport()->update();
}

void MemoryTableManager::set_block_signals_flag(bool is_blocked) {
    signals_blocked = is_blocked;
    for (auto tableWidget : memory_table_widgets) {
        tableWidget->blockSignals(is_blocked);
    }
}

void MemoryTableManager::reset_data(size_t start_index, size_t end_index) {
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
        if (instruction_index >= active_memory_table_data->size()) {
            active_memory_table_data->push_back(default_instruction);
        } else if ((*active_memory_table_data)[instruction_index] != default_instruction) {
            (*active_memory_table_data)[instruction_index] = default_instruction;
        }
    }
}

void MemoryTableManager::set_data(size_t index, const std::string &incoming_data) {
    if (index >= active_memory_table_data->size()) {
        std::ostringstream context;
        context << "Set Instruction Error: The provided index '" << index
                << "' is outside the expected range of [0-" << active_memory_table_data->size() - 1 << "]";
        throw std::out_of_range(context.str());
    }

    (*active_memory_table_data)[index] = incoming_data;
}

const std::vector<std::string>& MemoryTableManager::get_data() {
    return *active_memory_table_data;
}

void MemoryTableManager::add_new_tab() {
    QTableWidget *table_widget = new QTableWidget(row_count, 2, tab_widget);
    table_widget->verticalHeader()->setVisible(false);
    QStringList headers = {"Memory Address", "Instruction"};
    table_widget->setHorizontalHeaderLabels(headers);
    table_widget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    table_widget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    memory_table_widgets.push_back(table_widget);
    memory_tables_data.emplace_back(std::vector<std::string>(row_count, "+000000"));

    update_headers(table_widget);

    connect(table_widget, &QTableWidget::itemChanged, this, &MemoryTableManager::handle_item_changed);

    table_widget->installEventFilter(this);
    table_widget->horizontalHeader()->setSectionsClickable(false);
    table_widget->horizontalHeader()->setSectionsMovable(false);

    int new_tab_index = memory_table_widgets.size() - 1;
    // tab_widget->addTab(table_widget, QString("Script %1").arg(tab_index + 1));
    tab_widget->insertTab(new_tab_index, table_widget, QString("Script %1").arg(new_tab_index + 1));

    if(new_tab_index == 0) {
        tab_widget->tabBar()->setTabButton(new_tab_index, QTabBar::RightSide, nullptr);
    } else {
        QPushButton *close_button = new QPushButton("x");
        close_button->setFixedSize(16, 16);
        tab_widget->tabBar()->setTabButton(new_tab_index, QTabBar::RightSide, close_button);
        connect(close_button, &QPushButton::clicked, close_button, [this, new_tab_index]() { handle_tab_close(new_tab_index); });
    }

    tab_widget->setCurrentIndex(new_tab_index);
    update();
}

void MemoryTableManager::add_create_tab() {
    QWidget *create_tab = new QWidget();
    int create_tab_index = tab_widget->addTab(create_tab, "+");
    tab_widget->tabBar()->setTabButton(create_tab_index, QTabBar::RightSide, nullptr);

    connect(tab_widget, &QTabWidget::currentChanged, this, &MemoryTableManager::handle_create_tab_clicked);
}

void MemoryTableManager::handle_create_tab_clicked(int index) {
    if (tab_widget->tabText(index) == "+") {
        add_new_tab();
        int new_tab_index = tab_widget->count() - 2;
        move_create_tab_to_end();
        tab_widget->setCurrentIndex(new_tab_index);
    }
}

void MemoryTableManager::move_create_tab_to_end() {
    int create_tab_index = tab_widget->count() - 1;
    QWidget *create_tab = tab_widget->widget(create_tab_index);
    QString create_tab_text = tab_widget->tabText(create_tab_index);

    tab_widget->removeTab(create_tab_index);
    tab_widget->addTab(create_tab, create_tab_text);
}

void MemoryTableManager::handle_item_changed(QTableWidgetItem *item) {
    if (!signals_blocked) {
        emit input_submitted(item);
    }
}

void MemoryTableManager::handle_tab_changed() {
    update();
}

void MemoryTableManager::handle_tab_close(int index) {
    // Prevent closing the first tab
    if (index == 0) {
        return;
    }
    tab_widget->removeTab(index);
    memory_table_widgets.erase(memory_table_widgets.begin() + index);
    memory_tables_data.erase(memory_tables_data.begin() + index);
    update();
}

bool MemoryTableManager::eventFilter(QObject *obj, QEvent *event) {
    if (obj == active_memory_table_widget && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Tab && !keyEvent->modifiers().testFlag(Qt::ShiftModifier)) {
            QTableWidgetItem *currentItem = active_memory_table_widget->currentItem();
            if (currentItem && currentItem->column() == 1) {
                int currentRow = currentItem->row();
                int nextRow = (currentRow + 1) % row_count;
                active_memory_table_widget->setCurrentItem(active_memory_table_widget->item(nextRow, 1));
                return true;
            }
        } else if (keyEvent->key() == Qt::Key_Backtab) { // Shift+Tab is represented by Qt::Key_Backtab
            QTableWidgetItem *currentItem = active_memory_table_widget->currentItem();
            if (currentItem && currentItem->column() == 1) {
                int currentRow = currentItem->row();
                int prevRow = (currentRow - 1 + row_count) % row_count;
                active_memory_table_widget->setCurrentItem(active_memory_table_widget->item(prevRow, 1));
                return true;
            }
        }
    }
    return QObject::eventFilter(obj, event);
}
