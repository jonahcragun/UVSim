#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "inputdialog.h"
#include "uvsim.h"
#include "qt_input.h"
#include "qt_output.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void closeEvent(QCloseEvent*);

    void write_to_console(const std::string &str);
    void write_to_console(const QString &outputString);
    void write_to_console(const char* cstr);

    void overwrite_console(const std::string& str);
    void overwrite_console(const char* cstr);
    void overwrite_console(const QString& outputString);

    void set_table_row_count(const int count);

private slots:
    void handle_importButton_clicked();
    void handle_exportButton_clicked();
    void handle_runButton_clicked();
    void on_inputReceived(const QString &input);

private:
    int row_count;

    Ui::MainWindow *ui;
    InputDialog *userInput;
    std::vector<std::string> instruction_data;
    QTableWidget *memoryTable;
    QtInputHandler *input_handler;
    QtOutputHandler *output_handler;
    UVSim *uv_sim;

    void update_instuction_table();
    void reset_instruction_data(size_t start, size_t end_index);
    void set_instruction(size_t index, std::string data);
};

#endif // MAINWINDOW_H
