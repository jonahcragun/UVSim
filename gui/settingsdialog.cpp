#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QString>
#include <QIntValidator>
#include <QKeyEvent>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Settings");

    this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    QIntValidator *rgb_validator = new QIntValidator(0, 255, this);

    ui->primaryRLineEdit->setValidator(rgb_validator);
    ui->primaryGLineEdit->setValidator(rgb_validator);
    ui->primaryBLineEdit->setValidator(rgb_validator);
    ui->secondaryRLineEdit->setValidator(rgb_validator);
    ui->secondaryGLineEdit->setValidator(rgb_validator);
    ui->secondaryBLineEdit->setValidator(rgb_validator);

    connect(ui->acceptButton, &QPushButton::clicked, this, &SettingsDialog::handle_acceptButton_clicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SettingsDialog::handle_cancelButton_clicked);

    this->setModal(true);
}

SettingsDialog::~SettingsDialog(){
    delete ui;
}

void SettingsDialog::handle_acceptButton_clicked(){
    this->close();
    auto [primary_r, primary_g, primary_b, secondary_r, secondary_g, secondary_b] = get_gui_color_scheme();
    emit process_settings(primary_r, primary_g, primary_b, secondary_r, secondary_g, secondary_b);
}

std::tuple<int, int, int, int, int, int> SettingsDialog::get_gui_color_scheme(){
    int primary_r = ui->primaryRLineEdit->text().toInt();
    int primary_g = ui->primaryGLineEdit->text().toInt();
    int primary_b = ui->primaryBLineEdit->text().toInt();
    int secondary_r = ui->secondaryRLineEdit->text().toInt();
    int secondary_g = ui->secondaryGLineEdit->text().toInt();
    int secondary_b = ui->secondaryBLineEdit->text().toInt();

    return std::make_tuple(primary_r, primary_g, primary_b, secondary_r, secondary_g, secondary_b);
}

void SettingsDialog::handle_cancelButton_clicked(){
    this->close();
}

void SettingsDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        handle_cancelButton_clicked();
    } else {
        QDialog::keyPressEvent(event);
    }
}
