#ifndef MEMORYTABLEMANAGER_H
#define MEMORYTABLEMANAGER_H

#include <QObject>
#include <QTableWidget>
#include <vector>
#include <string>

class MemoryTableManager : public QObject
{
    Q_OBJECT

public:
    explicit MemoryTableManager(QTableWidget *tableWidget, int rowCount, QObject *parent = nullptr);

    void set_row_count(int count);
    void update();
    void reset_data(size_t start_index, size_t end_index);
    void set_data(size_t index, const std::string &data);
    void set_editable_flag(bool editable);
    void set_block_signals_flag(bool is_blocked);
    const std::vector<std::string>& get_data();

signals:
    void input_submitted(QTableWidgetItem *item);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void handle_item_changed(QTableWidgetItem *item);

private:
    QTableWidget *memory_table_widget;
    int row_count;
    std::vector<std::string> data;
    bool signals_blocked;
    void update_headers();
};

#endif
