#include "inputdialog.h"
#include "ui_inputdialog.h"
#include <QDebug>

InputDialog::InputDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InputDialog)
{
    ui->setupUi(this);
}

InputDialog::~InputDialog()
{
    delete ui;
}

void InputDialog::on_submitButton_clicked()
{
    QString input = ui->inputLineEdit->text();
    ui->inputLineEdit->clear();
    this->close();
    emit inputSubmitted(input);
}
