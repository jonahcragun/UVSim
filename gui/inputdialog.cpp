#include "inputdialog.h"
#include "ui_inputdialog.h"
#include <QDebug>

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Enter Your Input");

    this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    connect(ui->submitButton, &QPushButton::clicked, this, &InputDialog::handle_submitButton_clicked);
    this->setModal(true);
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::handle_submitButton_clicked()
{
    QString input = ui->inputLineEdit->text();
    ui->inputLineEdit->clear();
    this->close();
    emit inputSubmitted(input);
}
