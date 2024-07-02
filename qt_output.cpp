#include "qt_output.h"
#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QStandardPaths>

QtOutputHandler::QtOutputHandler(std::function<void(const std::string&)> console_func)
    : console(console_func) {}

QtOutputHandler::~QtOutputHandler() {}

void QtOutputHandler::handle_output(){
    console(buffer.str());
    buffer.clear();
    buffer.str("");
};

void QtOutputHandler::export_instructions_to_file(const std::vector<std::string>& instructions) {
    QString defaultFileName = "BasicML_instructions.txt";
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString fullPath = desktopPath + "/" + defaultFileName;
    QString fileName = QFileDialog::getSaveFileName(nullptr, QObject::tr("Save File"), fullPath,
                                                    QObject::tr("Text Files (*.txt)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            for (size_t i = 0; i < instructions.size(); ++i) {
                out << QString::fromStdString(instructions[i])
                    << (i != instructions.size() - 1 ? "\n" : "");
            }

            file.close();
            console("Instructions exported successfully.");
        } else {
            console("Failed to open file for writing.");
        }
    } else {
        console("File save cancelled.");
    }
}

