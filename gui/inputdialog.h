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

protected:
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void input_submitted(const QString &input);

private slots:
    void handle_submitButton_clicked();

private:
    Ui::InputDialog *ui;
};

#endif // INPUTDIALOG_H
