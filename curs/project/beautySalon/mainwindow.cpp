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
                QMessageBox msgBox;
                msgBox.setIcon(QMessageBox::Question);
                msgBox.setText("База данных пользователей не найдена. Создать новую базу?");

                msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

                msgBox.setButtonText(QMessageBox::Yes, "Да");
                msgBox.setButtonText(QMessageBox::No, "Нет");

                int ret = msgBox.exec();

                if (ret == QMessageBox::Yes)
                {
                    QSqlQuery query;
                       QString createEmployeesTableQuery = "CREATE TABLE IF NOT EXISTS employees ("
                                                           "last_name TEXT, "
                                                           "first_name TEXT, "
                                                           "middle_name TEXT, "
                                                           "birth_date DATE, "
                                                           "position TEXT)";
                       if (!query.exec(createEmployeesTableQuery)) {
                           QMessageBox::critical(nullptr, "Ошибка", "Ошибка при создании таблицы сотрудников");
                           return;
                       }

                       QString createScheduleTableQuery = "CREATE TABLE IF NOT EXISTS schedule ("
                                                          "last_name TEXT, "
                                                          "first_name TEXT, "
                                                          "phone TEXT, "
                                                          "service TEXT, "
                                                          "employee TEXT, "
                                                          "date TEXT, "
                                                          "time TEXT, "
                                                          "additional TEXT)";
                       if (!query.exec(createScheduleTableQuery)) {
                           QMessageBox::critical(nullptr, "Ошибка", "Ошибка при создании таблицы расписания клиентов");
                           return;
                       }

                       QString createServicesTableQuery = "CREATE TABLE IF NOT EXISTS services ("
                                                          "service TEXT, "
                                                          "price REAL)";
                       if (!query.exec(createServicesTableQuery)) {
                           QMessageBox::critical(nullptr, "Ошибка", "Ошибка при создании таблицы услуг");
                           return;
                       }

                       QString createUsersTableQuery = "CREATE TABLE IF NOT EXISTS users ("
                                                       "login TEXT, "
                                                       "password TEXT, "
                                                       "email TEXT, "
                                                       "role TEXT CHECK(role IN ('руководитель', 'администратор')))";
                       if (!query.exec(createUsersTableQuery)) {
                           QMessageBox::critical(nullptr, "Ошибка", "Ошибка при создании таблицы пользователей");
                           return;
                       }

                       QString insertUserQuery = "INSERT INTO users (login, password, email, role) "
                                                 "VALUES ('admin', 'admin', 'admin@service.com', 'руководитель')";
                       if (!query.exec(insertUserQuery)) {
                           QMessageBox::critical(nullptr, "Ошибка", "Ошибка при добавления стандартного пользователя admin");
                           return;
                       }
                       return;
                }

                if (ret == QMessageBox::No)
                {
                    return;
                }
        }

        if (query.next())
        {
            QString role = query.value(3).toString();

            Schedule schedule;

            schedule.setWindowTitle("Расписание клиентов");

            if (role == "руководитель")
            {
                schedule.SetSupervisorRules(true);
            }
            else if (role == "администратор")
            {
                schedule.SetSupervisorRules(false);
            }
            schedule.SetUserName(ui->loginLineEdit->text());
            this->setVisible(false);
            if (schedule.exec() == QDialog::Accepted)
            {
                ui->passLineEdit->setText("");
                ui->loginLineEdit->setText("");

                this->setVisible(true);
            }
        }
        else
        {
            QMessageBox::information(0, "Ошибка", "Неправильный логин/пароль.");
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    forgotPass forgotPass;
    forgotPass.setModal(true);

    forgotPass.exec();
}
