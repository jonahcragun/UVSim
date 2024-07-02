#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "inputdialog.h"
#include "settingsdialog.h"
#include "uvsim.h"
#include "memory_table_manager.h"
#include "qt_input.h"
#include "qt_output.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void write_to_console(const std::string& str, bool overwrite=false);
    void write_to_console(const QString& output_string, bool overwrite=false);
    void write_to_console(const char* cstr, bool overwrite=false);

protected:
    void closeEvent(QCloseEvent*);

private slots:
    void handle_importButton_clicked();
    void handle_exportButton_clicked();
    void handle_runButton_clicked();
    void handle_settingsButton_clicked();
    void handle_input_from_dialog_window(const QString &input);
    void handle_input_from_memory_table(QTableWidgetItem *item);
    void handle_input_from_settings(const int &primary_r_input, const int &primary_g_input,
                                    const int &primary_b_input, const int &secondary_r_input,
                                    const int &secondary_g_input, const int &secondary_b_input);

private:
    Ui::MainWindow *ui;

    InputDialog *user_input_dialog;

    SettingsDialog *settings_dialog;

    QtInputHandler *input_handler;
    QtOutputHandler *output_handler;
    UVSim *uv_sim;

    std::ostringstream console_buffer;
    void write_buffer_to_console(bool overwrite=false);

    int row_count;
    std::vector<std::string> instruction_data;
    MemoryTableManager *memory_table;

    std::string line_split;
};

#endif // MAINWINDOW_H
