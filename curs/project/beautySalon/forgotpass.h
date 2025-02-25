#ifndef FORGOTPASS_H
#define FORGOTPASS_H

#include <QDialog>

namespace Ui {
class forgotPass;
}

class forgotPass : public QDialog
{
    Q_OBJECT

public:
    explicit forgotPass(QWidget *parent = nullptr);
    ~forgotPass();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::forgotPass *ui;
};

#endif // FORGOTPASS_H
