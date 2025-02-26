#include "client.h"
#include "ui_client.h"
#include <QMessageBox>
#include <QSqlQuery>

Client::Client(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    Clear();

    timeStart.setHMS(8, 0, 0, 0);
    timeEnd.setHMS(18, 0, 0, 0);

    currentServices = new QList<QString>();
    currentEmployees = new QList<QString>();

    UpdateServices();
    UpdateEmployees();

    Clear();
}

void Client::SetClientExist(bool value)
{
    clientExist = value;
}

void Client::SetData(QStringList client)
{
    ui->lastNameLineEdit->setText(client.at(0));
    ui->firstNameLineEdit->setText(client.at(1));
    ui->phoneLineEdit->setText(client.at(2));
    ui->serviceComboBox->setCurrentText(client.at(3));
    ui->employeeComboBox->setCurrentText(client.at(4));
    ui->dateEdit->setDate(QDate::fromString(client.at(5)));
    ui->timeEdit->setTime(QTime::fromString(client.at(6)));
    ui->additionalTextEdit->setText(client.at(7));
}

QStringList* Client::GetData()
{
    QStringList* client = new QStringList();
    client->append(ui->lastNameLineEdit->text());
    client->append(ui->firstNameLineEdit->text());
    client->append(ui->phoneLineEdit->text());
    client->append(ui->serviceComboBox->currentText());
    client->append(ui->employeeComboBox->currentText());
    client->append(ui->dateEdit->date().toString("yyyy-MM-dd"));
    client->append(ui->timeEdit->time().toString("HH:mm"));
    client->append(ui->additionalTextEdit->toPlainText());
    return client;
}

void Client::UpdateEmployees()
{
    for (const QString &item : *currentEmployees)
    {
        ui->employeeComboBox->addItem(item);
    }
}

void Client::UpdateServices()
{
    for (const QString &item : *currentServices)
    {
        ui->serviceComboBox->addItem(item);
    }
}

void Client::SetEmployeesList(QList<QString> *employees)
{
    delete currentEmployees;
    currentEmployees = employees;
    UpdateEmployees();
}
void Client::SetServicesList(QList<QString> *services)
{
    delete currentServices;
    currentServices = services;
    UpdateServices();
}

void Client::SetTimeStart(QTime time)
{
    timeStart = time;
}
void Client::SetTimeEnd(QTime time)
{
    timeEnd = time;
}

void Client::Clear()
{
    ui->firstNameLineEdit->setText("");
    ui->lastNameLineEdit->setText("");
    ui->phoneLineEdit->setText("");
    ui->serviceComboBox->clear();
    ui->employeeComboBox->clear();
    ui->dateEdit->setDate(QDate::currentDate());
    ui->timeEdit->setTime(QTime(0, 0));
    ui->additionalTextEdit->setText("");

    clientExist = false;
}

Client::~Client()
{
    delete ui;
}

void Client::on_pushButton_clicked()
{
    Clear();
    this->close();
}

void Client::on_pushButton_2_clicked()
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

    if (ui->timeEdit->time() < timeStart || ui->timeEdit->time() > timeEnd.addSecs(60 * -30))
    {
        QMessageBox::information(0, "Ошибка", "Выход за пределы графика работы салона.");
        return;
    }

    QSqlQuery query;

    query.prepare("SELECT COUNT(*) FROM schedule "
                  "WHERE employee = :employee "
                  "AND date = :date "
                  "AND time = :time");

    query.bindValue(":employee", ui->employeeComboBox->currentText());
    query.bindValue(":date", ui->dateEdit->date().toString("yyyy-MM-dd"));
    query.bindValue(":time", ui->timeEdit->time().toString("HH:mm"));

    if (query.exec())
    {
        if (query.next())
        {
            int count = query.value(0).toInt();
            if (count > 0)
            {
                QMessageBox::information(nullptr, "Ошибка", "У данного мастера уже есть запись на эту дату и время.");
                return;
            }
        }
    }
    else
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при записи клиента.");
    }

    if (!clientExist)
    {
        query.prepare("INSERT INTO schedule (last_name, first_name, phone, service, employee, date, time, additional)"
                          " VALUES (:last_name, :first_name, :phone, :service, :employee, :date, :time, :additional)");

        query.bindValue(":last_name", ui->lastNameLineEdit->text());
        query.bindValue(":first_name", ui->firstNameLineEdit->text());
        query.bindValue(":phone", ui->phoneLineEdit->text());
        query.bindValue(":service", ui->serviceComboBox->currentText());
        query.bindValue(":employee", ui->employeeComboBox->currentText());
        query.bindValue(":date", ui->dateEdit->date().toString("yyyy-MM-dd"));
        query.bindValue(":time", ui->timeEdit->time().toString("HH:mm"));
        query.bindValue(":additional", ui->additionalTextEdit->toPlainText());

        if (!query.exec())
        {
            QMessageBox::critical(nullptr, "Ошибка", "Ошибка записи: ");
            this->close();
        }
    }
    else
    {



    }
    this->accept();
}
