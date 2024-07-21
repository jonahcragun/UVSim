#ifndef MEMORYTABLEMANAGER_H
#define MEMORYTABLEMANAGER_H

#include <QObject>
#include <QTableWidget>
#include <QTabWidget>
#include <vector>
#include <string>

class MemoryTableManager : public QObject
{
    Q_OBJECT

public:
    explicit MemoryTableManager(QTabWidget *tabWidget, int rowCount, QObject *parent = nullptr);

    void set_row_count(int count);
    void update();
    void reset_data(size_t start_index, size_t end_index);
    void set_data(size_t index, const std::string &data);
    void set_editable_flag(bool editable);
    void set_block_signals_flag(bool is_blocked);
    const std::vector<std::string>& get_data();
    void add_new_tab();

signals:
    void input_submitted(QTableWidgetItem *item);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void handle_item_changed(QTableWidgetItem *item);
    void handle_tab_changed();
    void handle_create_tab_clicked(int index);
    void handle_tab_close(int index);

private:
    QTabWidget *tab_widget;
    int row_count;
    std::vector<QTableWidget*> memory_table_widgets;
    std::vector<std::vector<std::string>> memory_tables_data;
    QTableWidget *active_memory_table_widget;
    std::vector<std::string> *active_memory_table_data;
    bool signals_blocked;

    void setup_tab_widget();
    void update_headers(QTableWidget *memory_table_widget);
    void update_active_memory_table();
    void add_create_tab();
    void move_create_tab_to_end();
};

#endif
