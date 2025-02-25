#include "newclient.h"
#include "ui_newclient.h"
#include <QMessageBox>
#include <QSqlQuery>

NewClient::NewClient(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewClient)
{
    ui->setupUi(this);

    Clear();

    if (currentServices!= nullptr)
    {
        for (const QString &item : *currentServices)
        {
            ui->serviceComboBox->addItem(item);
        }
    }
    if (currentEmployees != nullptr)
    {
        for (const QString &item : *currentEmployees)
        {
            ui->employeeComboBox->addItem(item);
        }
    }
}

void NewClient::SetEmployeesList(QList<QString> *employees)
{
    currentEmployees = employees;
}
void NewClient::SetServicesList(QList<QString> *services)
{
    currentServices = services;
}

void NewClient::Clear()
{
    ui->firstNameLineEdit->setText("");
    ui->lastNameLineEdit->setText("");
    ui->phoneLineEdit->setText("");
    ui->serviceComboBox->clear();
    ui->employeeComboBox->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime(0, 0));
    ui->additionalTextEdit->setText("");
}

NewClient::~NewClient()
{
    delete ui;
}

void NewClient::on_pushButton_clicked()
{
    this->close();
}

void NewClient::on_pushButton_2_clicked()
{
    if  (ui->firstNameLineEdit->text().isEmpty() ||
         ui->lastNameLineEdit->text().isEmpty() ||
         ui->phoneLineEdit->text().isEmpty())
    {
        QMessageBox::information(0, "Ошибка", "Поля не могут быть пустыми.");
        return;
    }

    if (ui->dateEdit->date() < QDate::currentDate())
    {
        QMessageBox::information(0, "Ошибка", "Неверно указана дата.");
        return;
    }
    if (ui->dateEdit->date() == QDate::currentDate() && ui->timeEdit->time() < QTime::currentTime())
    {
        QMessageBox::information(0, "Ошибка", "Неверно указана дата/время.");
        return;
    }

    QSqlQuery query;

    query.prepare("INSERT INTO your_table (last_name, first_name, phone, service, employee, date, time, additional)"
                      " VALUES (:last_name, :first_name, :phone, :service, :employee, :date, :time, :additional)");

    query.bindValue(":last_name", ui->lastNameLineEdit->text());
    query.bindValue(":first_name", ui->firstNameLineEdit->text());
    query.bindValue(":phone", ui->phoneLineEdit->text());
    query.bindValue(":service", ui->serviceComboBox->currentData());
    query.bindValue(":employee", ui->employeeComboBox->currentData());
    query.bindValue(":date", ui->dateEdit->date().toString("yyyy-MM-dd"));
    query.bindValue(":time", ui->timeEdit->time().toString("HH:mm"));
    query.bindValue(":additional", ui->additionalTextEdit->toPlainText());

    if (!query.exec())
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка записи.");
        return;
    }
}
