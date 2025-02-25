#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "schedule.h"
#include "forgotpass.h"
#include <QMessageBox>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Вход");

    if (!DataBase::Instance().connectToDatabase("salonDB"))
        QMessageBox::critical(0, "Ошибка", "Ошибка при подключении к базе данных.");

    QSqlTableModel* users = new QSqlTableModel(this, DataBase::Instance().getDatabase());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_authButton_3_clicked()
{
    if (ui->loginLineEdit->text().isEmpty() || ui->passLineEdit->text().isEmpty())
        QMessageBox::information(0, "Ошибка", "Поля не могут быть пустыми.");
    else
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM users WHERE login = :login AND password = :password");
        query.bindValue(":login", ui->loginLineEdit->text());
        query.bindValue(":password", ui->passLineEdit->text());

        if (!query.exec())
        {
            QMessageBox::critical(0, "Ошибка", "Ошибка при обращении к базе пользователей.");
            return;
        }

        if (query.next())
        {
            QWidget* schedule = new QWidget();

            schedule->setWindowTitle("Расписание клиентов");
            schedule->show();
            this->close();
        }
        else
        {
            QMessageBox::information(0, "Ошибка", "Неправильный логин/пароль.");
            QMessageBox msg;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    forgotPass forgotPass;
    forgotPass.setModal(true);

    forgotPass.exec();
}
