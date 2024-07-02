#include "memory_table_manager.h"
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QKeyEvent>
#include <sstream>
#include <iostream>

MemoryTableManager::MemoryTableManager(QTableWidget *tableWidget, int rowCount, QObject *parent)
    : QObject(parent), memory_table_widget(tableWidget), row_count(rowCount), signals_blocked(false)
{
    memory_table_widget->verticalHeader()->setVisible(false);
    QStringList headers = {"Memory Address", "Instruction"};
    memory_table_widget->setHorizontalHeaderLabels(headers);
    memory_table_widget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    memory_table_widget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    set_row_count(rowCount);

    update_headers();

    connect(memory_table_widget, &QTableWidget::itemChanged, this, &MemoryTableManager::handle_item_changed);

    memory_table_widget->installEventFilter(this);

    memory_table_widget->horizontalHeader()->setSectionsClickable(false);
    memory_table_widget->horizontalHeader()->setSectionsMovable(false);
}

void MemoryTableManager::set_row_count(int count) {
    row_count = count;
    memory_table_widget->setRowCount(row_count);
    update();
}

void MemoryTableManager::update() {
    if (data.size() == 0) {
        reset_data(0, row_count);
    }
    if (static_cast<size_t>(row_count) != data.size()) {
        std::ostringstream throw_context;
        throw_context << "Update Table Error: Table size '" << row_count << "' and instruction count '"
                      << data.size() << "' mismatch.";
        throw std::out_of_range(throw_context.str());
    }

    for (int instruction_index = 0; instruction_index < row_count; ++instruction_index) {
        QString memoryAddress = QString("%1:").arg(instruction_index, 2, 10, QChar('0'));
        QTableWidgetItem *addressItem = new QTableWidgetItem(memoryAddress);
        addressItem->setFlags(addressItem->flags() & ~Qt::ItemIsEditable & ~Qt::ItemIsSelectable);
        addressItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        memory_table_widget->setItem(instruction_index, 0, addressItem);

        QTableWidgetItem *instructionItem = new QTableWidgetItem(QString::fromStdString(data[instruction_index]));
        instructionItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignCenter);
        instructionItem->setFlags(instructionItem->flags() & ~Qt::ItemIsSelectable);
        memory_table_widget->setItem(instruction_index, 1, instructionItem);
    }
    memory_table_widget->viewport()->update();
}

void MemoryTableManager::update_headers() {
    for (int column = 0; column < memory_table_widget->columnCount(); ++column) {
        QTableWidgetItem *headerItem = memory_table_widget->horizontalHeaderItem(column);
        if (headerItem) {
            headerItem->setFlags(headerItem->flags() & ~Qt::ItemIsSelectable);
        }
    }
}

void MemoryTableManager::set_editable_flag(bool editable) {
    for (int instruction_index = 0; instruction_index < row_count; ++instruction_index) {
        QTableWidgetItem *item = memory_table_widget->item(instruction_index, 1); // Column 1: Instruction
        if (item) {
            if (editable) {
                item->setFlags(item->flags() | Qt::ItemIsEditable);
            } else {
                item->setFlags(item->flags() & ~Qt::ItemIsEditable);
            }
        }
    }
    memory_table_widget->viewport()->update();
}

void MemoryTableManager::set_block_signals_flag(bool is_blocked) {
    signals_blocked = is_blocked;
    memory_table_widget->blockSignals(is_blocked);
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
    if (data.capacity() < end_index) {
        data.reserve(end_index);
    }

    std::string default_instruction = "+0000";
    for (size_t instruction_index = start_index; instruction_index < end_index; ++instruction_index) {
        if (instruction_index >= data.size()) {
            data.push_back(default_instruction);
        } else if (data[instruction_index] == default_instruction) {
            continue;
        } else {
            data[instruction_index] = default_instruction;
        }
    }
}

void MemoryTableManager::set_data(size_t index, const std::string &incoming_data) {
    if (index >= data.size()) {
        std::ostringstream context;
        context << "Set Instruction Error: The provided index '" << index
                << "' is outside the expected range of [0-" << data.size() - 1 << "]";
        throw std::out_of_range(context.str());
    }

    data[index] = incoming_data;
}

const std::vector<std::string>& MemoryTableManager::get_data() {
    return data;
}

void MemoryTableManager::handle_item_changed(QTableWidgetItem *item) {
    if (!signals_blocked) {
        emit input_submitted(item);
    }
}

bool MemoryTableManager::eventFilter(QObject *obj, QEvent *event) {
    if (obj == memory_table_widget && event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        if (keyEvent->key() == Qt::Key_Tab && !keyEvent->modifiers().testFlag(Qt::ShiftModifier)) {
            QTableWidgetItem *currentItem = memory_table_widget->currentItem();
            if (currentItem && currentItem->column() == 1) {
                int currentRow = currentItem->row();
                int nextRow = (currentRow + 1) % row_count;
                memory_table_widget->setCurrentItem(memory_table_widget->item(nextRow, 1));
                return true;
            }
        } else if (keyEvent->key() == Qt::Key_Backtab) { // Shift+Tab is represented by Qt::Key_Backtab
            QTableWidgetItem *currentItem = memory_table_widget->currentItem();
            if (currentItem && currentItem->column() == 1) {
                int currentRow = currentItem->row();
                int prevRow = (currentRow - 1 + row_count) % row_count;
                memory_table_widget->setCurrentItem(memory_table_widget->item(prevRow, 1));
                return true;
            }
        }
    }
    return QObject::eventFilter(obj, event);
}
