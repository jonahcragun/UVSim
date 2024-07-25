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
    explicit MemoryTableManager(QTabWidget *tabWidget, int maxTabs, int rowCount, QObject *parent = nullptr);
    ~MemoryTableManager();

    void set_row_count(int count);
    void update_active_table();
    void reset_data(size_t start_index, size_t end_index);
    void set_data(size_t index, const std::string &data);
    void set_editable_flag(bool editable);
    void set_input_block_signals_flag(bool is_blocked);
    const std::vector<std::string>& get_data();
    void add_new_tab();

signals:
    void input_submitted(QTableWidgetItem *item);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void handle_item_changed(QTableWidgetItem *item);
    void handle_tab_changed(int index);
    void handle_tab_close(int index);

private:
    QTabWidget *tab_widget;
    int max_tabs;
    int row_count;
    std::vector<QTableWidget*> memory_table_widgets;
    std::vector<std::vector<std::string>> memory_tables_data;
    QTableWidget *active_table_widget;
    std::vector<std::string> *active_table_data;
    bool tab_signals_blocked;
    bool table_signals_blocked;

    void set_tab_block_signals_flag(bool is_blocked);
    void update_tabs();
    void setup_tab_widget();

    void format_table_widget(QTableWidget* table_widget, std::vector<std::string>& table_data);
    void reset_data(size_t table_index, size_t start_index, size_t end_index);
};

#endif
