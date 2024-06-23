#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <sstream>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("UVSim");

    this->setFixedSize(this->size());

    userInput = new InputDialog(this);
    input_handler = new QtInputHandler([this](const std::string& str) { this->write_to_console(str); });
    input_handler->tie_input_ui(*userInput);

    output_handler = new QtOutputHandler([this](const std::string& str) { this->write_to_console(str); });

    uv_sim = new UVSim(&(*input_handler), &(*output_handler));

    connect(userInput, &InputDialog::inputSubmitted, this, &MainWindow::on_inputReceived);
    connect(ui->importButton, &QPushButton::clicked, this, &MainWindow::handle_importButton_clicked);
    connect(ui->runButton, &QPushButton::clicked, this, &MainWindow::handle_runButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete userInput;
    delete input_handler;
    delete output_handler;
    delete uv_sim;
}

void MainWindow::closeEvent(QCloseEvent*) {
    QApplication::quit();
}


void MainWindow::write_to_console(const std::string& str)
{
    QString newQString = QString::fromStdString(str);
    write_to_console(newQString);
}

void MainWindow::write_to_console(const char* cstr)
{
    QString newQString = QString::fromUtf8(cstr);
    write_to_console(newQString);
}

void MainWindow::write_to_console(const QString& outputString)
{
    ui->consoleTextEdit->append(outputString);
}

void MainWindow::overwrite_console(const std::string& str)
{
    QString newQString = QString::fromStdString(str);
    overwrite_console(newQString);
}

void MainWindow::overwrite_console(const char* cstr)
{
    QString newQString = QString::fromUtf8(cstr);
    overwrite_console(newQString);
}

void MainWindow::overwrite_console(const QString& outputString)
{
    ui->consoleTextEdit->setPlainText(outputString);
}

void MainWindow::handle_mainWindow_close() {

}

void MainWindow::handle_importButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            QString fileContent = in.readAll();
            file.close();

            std::string stdFileContent = fileContent.toStdString();
            std::istringstream inputStream(stdFileContent);

            importData.clear();
            importData = input_handler->split_lines(inputStream);

            if (!importData.empty()){
                input_handler->set_instr_data(importData);
                write_to_console("File imported successfully.");
            } else {
                write_to_console("Unexpected error occured. File did not import.");
            }
        }
    }
}

void MainWindow::handle_runButton_clicked()
{
    try {
        if (importData.empty()) {
            throw std::runtime_error("Error: No data imported. Please import a file first.");
        }

        overwrite_console("Attempting to run program...");
        uv_sim->run();
        write_to_console("Program complete.");
    }
    catch(const std::exception& e) {
        std::istringstream error(e.what());
        std::cout << e.what() << std::endl;
        write_to_console(error.str());
    }
}

void MainWindow::on_inputReceived(const QString &input)
{
    input_handler->set_input_data(input.toStdString());
}
