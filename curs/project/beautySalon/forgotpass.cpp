#include "forgotpass.h"
#include "ui_forgotpass.h"
#include <QSqlQuery>
#include <QMessageBox>

forgotPass::forgotPass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::forgotPass)
{
    ui->setupUi(this);
}

forgotPass::~forgotPass()
{
    delete ui;
}

void forgotPass::on_pushButton_2_clicked()
{
    this->close();
}

void forgotPass::on_pushButton_clicked()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE email = :email");
    query.bindValue(":email", ui->lineEdit->text());

    if (!query.exec())
    {
        QMessageBox::critical(0, "Ошибка", "Ошибка при обращении к базе пользователей.");
        return;
    }

    if (query.next())
    {
        QMessageBox::information(0, "Отчет", "Логин и пароль отправлены на email.");
        this->close();
    }
    else
    {
        QMessageBox::information(0, "Ошибка", "Пользователь с таким email не найден.");
    }
}
