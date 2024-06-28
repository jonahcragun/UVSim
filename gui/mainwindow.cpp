#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <sstream>
#include <iostream>
#include <string>
#include <QTableWidget>
#include <QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("UVSim");
    this->setFixedSize(this->size());

    memoryTable = ui->memoryTable;
    memoryTable->verticalHeader()->setVisible(false);
    QStringList headers = {"Memory Address", "Instruction"};
    memoryTable->setHorizontalHeaderLabels(headers);
    memoryTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    memoryTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    userInput = new InputDialog(this);
    input_handler = new QtInputHandler([this](const std::string& str) { this->write_to_console(str); });
    input_handler->tie_input_ui(*userInput);

    output_handler = new QtOutputHandler([this](const std::string& str) { this->write_to_console(str); });

    uv_sim = new UVSim(&(*input_handler), &(*output_handler));

    connect(userInput, &InputDialog::inputSubmitted, this, &MainWindow::on_inputReceived);
    connect(ui->importButton, &QPushButton::clicked, this, &MainWindow::handle_importButton_clicked);
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::handle_exportButton_clicked);
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

void MainWindow::set_table_row_count(const int count){
    if (row_count == count){
        return;
    }
    row_count = count;
    memoryTable->setRowCount(row_count);
    update_instuction_table();
}

void MainWindow::update_instuction_table(){
    if (instruction_data.size() == 0){
        reset_instruction_data(0, row_count);
    }
    if (static_cast<size_t>(row_count) != instruction_data.size()){
        std::ostringstream output_error;
        output_error << "Update Table Error: Table size '" << row_count << "' and instruction count '"
                     << instruction_data.size() << "' mismatch.";
        throw std::out_of_range(output_error.str());
    }

    for (int instruction_index = 0; instruction_index < row_count; ++instruction_index) {
        // Update the memory address column (zero-filled 2-width numbers)
        QString memoryAddress = QString("%1:").arg(instruction_index, 2, 10, QChar('0'));
        QTableWidgetItem *addressItem = new QTableWidgetItem(memoryAddress);
        addressItem->setFlags(addressItem->flags() & ~Qt::ItemIsEditable);
        addressItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        memoryTable->setItem(instruction_index, 0, addressItem);

        // Update the instruction column
        QTableWidgetItem *instructionItem = new QTableWidgetItem(QString::fromStdString(instruction_data[instruction_index]));
        instructionItem->setTextAlignment(Qt::AlignVCenter | Qt::AlignCenter);
        memoryTable->setItem(instruction_index, 1, instructionItem);
    }
}

void MainWindow::reset_instruction_data(size_t start_index, size_t end_index) {
    if (end_index > static_cast<size_t>(row_count)) {
        end_index = static_cast<size_t>(row_count);
    }
    if (start_index > end_index){
        std::ostringstream output_error;
        output_error << "Reset Instruction Vector Error: The passed start index '" << start_index
                     << "' is beyond the end index '" << end_index << "'";
        throw std::out_of_range(output_error.str());
    }
    if (instruction_data.capacity() < end_index) {
        instruction_data.reserve(end_index);
    }

    std::string default_instruction = "+0000";
    for (size_t instruction_index = start_index; instruction_index < end_index; ++instruction_index) {
        if (instruction_index >= instruction_data.size()) {
            instruction_data.push_back(default_instruction);
        } else if (instruction_data[instruction_index] == default_instruction) {
            continue;
        } else {
            instruction_data[instruction_index] = default_instruction;
        }
    }
}


void MainWindow::set_instruction(size_t index, std::string data){
    if (index >= instruction_data.size()) {
        std::ostringstream output_error;
        output_error << "Set Instruction Error: The provided index '" << index
                     << "' is outside the expected range of [0-" << instruction_data.size() - 1 << "]";
        throw std::out_of_range(output_error.str());
    }

    instruction_data[index] = data;
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

            size_t size_cap = static_cast<size_t>(row_count);
            reset_instruction_data(0, size_cap);
            const std::vector<std::string> file_import_data = input_handler->split_lines(inputStream);
            size_t last_set_index = file_import_data.size();
            if (file_import_data.size() > size_cap) {
                std::ostringstream output_warning;
                output_warning << "File exceeds the size of the UVSim. Keeping the first '"
                               << row_count << "' lines of the file.";
                write_to_console(output_warning.str());
                last_set_index = size_cap;
            }

            for (size_t instruction_index = 0; instruction_index < last_set_index; ++instruction_index){
                set_instruction(instruction_index, file_import_data[instruction_index]);
            }
            update_instuction_table();

            if (!instruction_data.empty()){
                input_handler->set_instr_data(instruction_data);
                overwrite_console("File imported successfully.");
            } else {
                overwrite_console("Unexpected error occured. File did not import.");
            }
        }
    }
}


void MainWindow::handle_exportButton_clicked()
{
    QString defaultFileName = "BasicML_instructions.txt";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), defaultFileName, tr("Text Files (*.txt)"));
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            for (size_t i = 0; i < instruction_data.size(); ++i) {
                out << QString::fromStdString(instruction_data[i])
                    << (i != instruction_data.size() - 1 ? "\n" : "");
            }

            file.close();
            overwrite_console("Instructions exported successfully.");
        } else {
            overwrite_console("Failed to open file for writing.");
        }
    } else {
        overwrite_console("File save cancelled.");
    }
}


void MainWindow::handle_runButton_clicked()
{
    try {
        if (instruction_data.empty()) {
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
