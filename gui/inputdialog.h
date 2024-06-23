#ifndef INPUTDIALOG_H
#define INPUTDIALOG_H

#include <QDialog>

namespace Ui {
class InputDialog;
}

class InputDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InputDialog(QWidget *parent = nullptr);
    ~InputDialog();

signals:
    void inputSubmitted(const QString &input);

private slots:
    void handle_submitButton_clicked();

private:
    Ui::InputDialog *ui;
};

#endif // INPUTDIALOG_H
