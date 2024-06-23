#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private slots:
    void handle_importButton_clicked();
    void handle_runButton_clicked();
    void handle_mainWindow_close();
    void on_inputReceived(const QString &input);

private:
    Ui::MainWindow *ui;
    InputDialog *userInput;
    std::vector<std::string> importData;
    QtInputHandler *input_handler;
    QtOutputHandler *output_handler;
    UVSim *uv_sim;
};

#endif // MAINWINDOW_H
