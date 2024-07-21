#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();

    std::tuple<int, int, int, int, int, int> get_gui_color_scheme();

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void process_settings(const int &primary_r_input, const int &primary_g_input,
                          const int &primary_b_input, const int &secondary_r_input,
                          const int &secondary_g_input, const int &secondary_b_input);

private slots:
    void handle_acceptButton_clicked();
    void handle_cancelButton_clicked();
    void validate_rgb_input(const QString &text);

private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
