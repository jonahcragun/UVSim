#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QString>
#include <QIntValidator>
#include <QKeyEvent>
#include <QToolTip>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Settings");

    this->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    connect(ui->primary01RLineEdit, &QLineEdit::textChanged, this, &SettingsDialog::validate_rgb_input);
    connect(ui->primary02GLineEdit, &QLineEdit::textChanged, this, &SettingsDialog::validate_rgb_input);
    connect(ui->primary03BLineEdit, &QLineEdit::textChanged, this, &SettingsDialog::validate_rgb_input);
    connect(ui->secondary01RLineEdit, &QLineEdit::textChanged, this, &SettingsDialog::validate_rgb_input);
    connect(ui->secondary02GLineEdit, &QLineEdit::textChanged, this, &SettingsDialog::validate_rgb_input);
    connect(ui->secondary03BLineEdit, &QLineEdit::textChanged, this, &SettingsDialog::validate_rgb_input);

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
    int primary_r = ui->primary01RLineEdit->text().toInt();
    int primary_g = ui->primary02GLineEdit->text().toInt();
    int primary_b = ui->primary03BLineEdit->text().toInt();
    int secondary_r = ui->secondary01RLineEdit->text().toInt();
    int secondary_g = ui->secondary02GLineEdit->text().toInt();
    int secondary_b = ui->secondary03BLineEdit->text().toInt();

    return std::make_tuple(primary_r, primary_g, primary_b, secondary_r, secondary_g, secondary_b);
}

void SettingsDialog::handle_cancelButton_clicked(){
    this->close();
}

void SettingsDialog::validate_rgb_input(const QString &text)
{
    bool valid_rgb_value;
    int value = text.toInt(&valid_rgb_value);

    if (!valid_rgb_value || value < 0 || value > 255) {
        QLineEdit *line_edit = qobject_cast<QLineEdit *>(sender());
        if (line_edit) {
            QToolTip::showText(line_edit->mapToGlobal(QPoint(0, line_edit->height()/2)),
                               "Must be a valid RGB value between 0-255",
                               line_edit);

            line_edit->setText("0");
        }
    }
}

void SettingsDialog::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        handle_cancelButton_clicked();
    } else if (event->key() == Qt::Key_Enter) {
        return;
    } else {
        QDialog::keyPressEvent(event);
    }
}
