#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <string>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , row_count(MEMORY_SIZE)
{
    ui->setupUi(this);
    this->setWindowTitle("UVSim");
    this->setFixedSize(this->size());

    connect(ui->importButton, &QPushButton::clicked, this, &MainWindow::handle_importButton_clicked);
    connect(ui->exportButton, &QPushButton::clicked, this, &MainWindow::handle_exportButton_clicked);
    connect(ui->runButton, &QPushButton::clicked, this, &MainWindow::handle_runButton_clicked);
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::handle_settingsButton_clicked);

    memory_table = new MemoryTableManager(ui->memoryTableTabs, 10, row_count, this);
    connect(memory_table, &MemoryTableManager::input_submitted, this, &MainWindow::handle_input_from_memory_table);

    settings_dialog = new SettingsDialog(this);
    connect(settings_dialog, &SettingsDialog::process_settings, this, &MainWindow::handle_input_from_settings);
    auto [primary_r, primary_g, primary_b, secondary_r, secondary_g, secondary_b] = settings_dialog->get_gui_color_scheme();
    handle_input_from_settings(primary_r, primary_g, primary_b, secondary_r, secondary_g, secondary_b);

    user_input_dialog = new InputDialog(this);
    input_handler = new QtInputHandler([this](const std::string& str) { this->write_to_console(str); });
    input_handler->tie_input_ui(*user_input_dialog);
    connect(user_input_dialog, &InputDialog::input_submitted, this, &MainWindow::handle_input_from_dialog_window);

    output_handler = new QtOutputHandler([this](const std::string& str) { this->write_to_console(str); });

    uv_sim = new UVSim(&(*input_handler), &(*output_handler));

    console_buffer << "Welcome to the UVSim.\n\n"
                      "Please import a text file with lines of BasicML instructions or double click an instruction "
                      "in the memory table on the left to manually set an instruction.\n\n"
                      "When ready hit 'RUN' to execute the program.\n";
    write_buffer_to_console(true);

    console_buffer << std::setw(10) << std::setfill(' ') << "";
    console_buffer <<  std::setw(80) << std::setfill('-') << "";
    console_buffer <<  std::setw(10) << std::setfill(' ') << "\n";
    line_split = console_buffer.str();
    console_buffer.str("");
}

MainWindow::~MainWindow(){
    delete ui;
    delete user_input_dialog;
    delete settings_dialog;
    delete input_handler;
    delete output_handler;
    delete uv_sim;
    delete memory_table;
}

void MainWindow::closeEvent(QCloseEvent*) {
    QApplication::quit();
}

void MainWindow::write_to_console(const std::string& str, bool overwrite){
    QString console_qstring = QString::fromStdString(str);
    write_to_console(console_qstring, overwrite);
}

void MainWindow::write_to_console(const char* cstr, bool overwrite){
    QString console_qstring = QString::fromUtf8(cstr);
    write_to_console(console_qstring, overwrite);
}

void MainWindow::write_to_console(const QString& outputString, bool overwrite){
    if (overwrite) {
        ui->consoleTextEdit->setPlainText(outputString);
    } else {
        ui->consoleTextEdit->append(outputString);
    }
    QCoreApplication::processEvents();
}

void MainWindow::write_buffer_to_console(bool overwrite){
    QString console_qstring = QString::fromStdString(console_buffer.str());
    write_to_console(console_qstring, overwrite);
    console_buffer.str("");
    QCoreApplication::processEvents();
}

void MainWindow::handle_importButton_clicked() {
    size_t size_cap = static_cast<size_t>(row_count);

    std::vector<std::string> file_import_data;
    try {
        write_buffer_to_console(true);
        write_to_console("Please select a file with lines of BasicML instructions to import.");
        file_import_data = input_handler->import_instructions_from_file();
    } catch (const std::exception& e) {
        console_buffer << e.what() << "\nFailed to import file.";
        write_buffer_to_console();
        return;
    }

    size_t last_set_index = file_import_data.size();
    if (file_import_data.size() > size_cap) {
        console_buffer << "\nImport Error: File exceeds the allocated memory size of the UVSim program.\nKeeping the first '"
                       << row_count << "' lines of the file." << "\n";
        write_buffer_to_console();
        last_set_index = size_cap;
    }
    write_to_console("\nFile imported successfully.");

    console_buffer << line_split << "Validating new instructions...\n";
    write_buffer_to_console();

    // Temporarily block signals to avoid recursion
    memory_table->set_input_block_signals_flag(true);
    memory_table->reset_data(0, size_cap);
    for (size_t instruction_index = 0; instruction_index < last_set_index; ++instruction_index) {
        try {
            input_handler->validate_instruction(file_import_data[instruction_index]);
            memory_table->set_data(instruction_index, file_import_data[instruction_index]);
        } catch (const std::exception& error) {
            console_buffer << "Line " << instruction_index << " | " << error.what() << "Skipping instruction." << "\n";
            write_buffer_to_console();
        }
    }
    memory_table->update_active_table();

    // Restore signal unblocked state
    memory_table->set_input_block_signals_flag(false);

    if (!memory_table->get_data().empty()) {
        write_to_console("Validation Complete.");
    } else {
        write_to_console("Unexpected error occurred. File did not import.");
    }

    console_buffer << line_split;
    write_buffer_to_console();
}

void MainWindow::handle_exportButton_clicked(){
    output_handler->export_instructions_to_file(memory_table->get_data());
}

void MainWindow::handle_runButton_clicked(){
    // Temporarily block signals to avoid recursion
    memory_table->set_input_block_signals_flag(true);
    // Block edits from being made during runtime
    memory_table->set_editable_flag(false);
    try {
        if (memory_table->get_data().empty()) {
            throw std::runtime_error("Error: Data is in it's initial unusable state. "
                                     "Please import a file or manually add an instruction before running again.\n");
        }
        console_buffer.str("");
        write_buffer_to_console(true);
        write_to_console("Attempting to run program...\n");
        std::vector<std::string> instruction_data = memory_table->get_data();
        input_handler->set_instr_data(instruction_data);
        uv_sim->run();
        write_to_console("Program complete.");

        console_buffer << line_split;
        write_buffer_to_console();
    } catch( std::exception& e) {
        write_to_console(e.what());
    }
    // Restore editable state
    memory_table->set_editable_flag(true);
    // Restore signal unblocked state
    memory_table->set_input_block_signals_flag(false);
}

void MainWindow::handle_settingsButton_clicked(){
    settings_dialog->show();
}

void MainWindow::handle_input_from_dialog_window(const QString &input){
    input_handler->set_input_data(input.toStdString());
}

void MainWindow::handle_input_from_memory_table(QTableWidgetItem *item){
    int row = item->row();
    int column = item->column();

    if (column == 1) { // Instruction column
        QString new_value = item->text();
        std::string new_instruction = new_value.toStdString();

        // Temporarily block signals to avoid recursion
        memory_table->set_input_block_signals_flag(true);

        try {
            input_handler->validate_instruction(new_instruction);
            memory_table->set_data(row, new_instruction); // Will not reach this update if instruction is invalid
            item->setText(QString::fromStdString(new_instruction));
        } catch (const std::exception &e) {
            // If invalid, revert the change and log the error
            item->setText(QString::fromStdString(memory_table->get_data()[row]));
            write_to_console(e.what(), true);
        }

        // Restore signal blocking state
        memory_table->set_input_block_signals_flag(false);
    }
}

void MainWindow::handle_input_from_settings(const int &primary_r, const int &primary_g,
                                            const int &primary_b, const int &secondary_r,
                                            const int &secondary_g, const int &secondary_b) {
    QString primary_color = QString("rgb(%1, %2, %3)").arg(primary_r).arg(primary_g).arg(primary_b);
    QString secondary_color = QString("rgb(%1, %2, %3)").arg(secondary_r).arg(secondary_g).arg(secondary_b);
    QString table_cell_outline_color = "rgb(50, 50, 50)";
    QString input_field_color = "rgb(10, 10, 10)";
    QString unselected_tab_color = QString("rgb(%1, %1, %1)").arg(
        ((secondary_r + secondary_g + secondary_b)/3 - 150 <= 0) ? 75 : 25);

    QString style_sheet = QString(
                              "QWidget { background-color: %1; font-family: 'Sitka'; font-size: 10pt; }"
                              "QPushButton { background-color: %2; color: %1; }"
                              "QLabel { background-color: %2; color: %1; }"
                              "QLineEdit { background-color: %4; color: %2; }"
                              "QTextEdit { background-color: %4; color: %2; }"
                              "QTabWidget::pane { background-color: %2; }"
                              "QTabBar::tab { background-color: %5; color: %2; min-width: 30px; max-width: 50px; min-height: 10px; max-height: 90px; }"
                              "QTabBar::tab:selected { background-color: %2; color: %1; }"
                              "QTabBar::tab:hover { color: %2; }"
                              "QTableWidget { background-color: %4; color: %2; }"
                              "QTableWidget::item { border: 1px solid %3; }"
                              "QHeaderView::section { background-color: %2; color: %1; }"
                              ).arg(
                                  secondary_color,          // %1
                                  primary_color,            // %2
                                  table_cell_outline_color, // %3
                                  input_field_color,        // %4
                                  unselected_tab_color      // %5
                                  );

    this->setStyleSheet(style_sheet);
    ui->memoryTableTabs->setStyleSheet(style_sheet);
}
