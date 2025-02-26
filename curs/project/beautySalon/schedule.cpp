#include "schedule.h"
#include "ui_schedule.h"
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlTableModel>
#include "database.h"
#include "client.h"
#include <QTime>
#include "mainwindow.h"

Schedule::Schedule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Schedule)
{
    ui->setupUi(this);

    GetEmployeesList();
    GetServicesList();

    currentDate = QDate::currentDate();

    startTime.setHMS(8, 0, 0);
    endTime.setHMS(18, 0, 0);
    GetTimeList(&startTime, &endTime);

    BuildTable();
    UpdateSchedule();
    ui->dateLabel->setText("Просмотр расписания за " + currentDate.toString("dd.MM.yyyy"));
}

void Schedule::SetSupervisorRules(bool value)
{
    supervisorRules = value;
}

void Schedule::SetUserName(QString name)
{
    ui->userNameLabel->setText(name);
}

void Schedule::BuildTable()
{    
    ui->mainTableWidget->setRowCount(timeList.size());
    ui->mainTableWidget->setColumnCount(employeesList.size());

    for (int i = 0; i < timeList.size(); i++)
    {
        ui->mainTableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(timeList[i].toString("hh:mm")));
        ui->mainTableWidget->setRowHeight(i, 100);
    }

    for (int i = 0; i < employeesList.size(); i++)
    {
        ui->mainTableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(employeesList[i]));
        ui->mainTableWidget->setColumnWidth(i, 180);
    }
}

void Schedule::GetTimeList(QTime *startTime, QTime *endTime)
{
    QTime currentTime(startTime->hour(), startTime->minute());

    while (currentTime <= *endTime)
    {
        timeList.append(currentTime);
        currentTime = currentTime.addSecs((30 * 60));
    }
}

void Schedule::UpdateSchedule()
{
    clientsList.clear();

    QSqlQuery query;
    query.prepare("SELECT last_name, first_name, phone, service, employee, date, time, additional FROM schedule WHERE date = :date");
    query.bindValue(":date", currentDate.toString("yyyy-MM-dd"));

    if (!query.exec())
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при подключении к расписанию.");
        return;
    }

    while (query.next())
    {
        QStringList note;
        note.append(query.value("last_name").toString());
        note.append(query.value("first_name").toString());
        note.append(query.value("phone").toString());
        note.append(query.value("service").toString());
        note.append(query.value("employee").toString());
        note.append(query.value("date").toString());
        note.append(query.value("time").toString());
        note.append(query.value("additional").toString());
        clientsList.append(note);
    }

    for (const QStringList &note : clientsList)
    {
        for (const QString &employee : employeesList)
        {
            if (note[4] == employee)
            {
                for (const QTime &time : timeList)
                {
                    if (note[6] == time.toString("hh:mm"))
                    {
                        QTableWidgetItem *item = new QTableWidgetItem(note[0] + "\n" + note[1] + "\n" + note[2] + "\n" +
                                note[3] + "\n" + note[7]);

                        item->setBackground(QBrush(QColor(135, 206, 250)));
                        ui->mainTableWidget->setItem(timeList.indexOf(time), employeesList.indexOf(employee), item );

                        ui->mainTableWidget->update();
                        break;
                    }
                }
            }
        }
    }
}

void Schedule::ClearTable()
{
    clientsList.clear();
    ui->mainTableWidget->clear();
    BuildTable();
}

void Schedule::GetEmployeesList()
{
    employeesList.clear();

    QSqlQuery query("SELECT last_name, first_name, middle_name FROM employees");

    if (!query.exec()) {
        QMessageBox::critical(0, "Ошибка", "Ошибка при подключении к списку сотрудников.");
        return;
    }

    while(query.next())
    {
        employeesList.append(query.value(0).toString() + " " + query.value(1).toString().at(0) +
                ". " +  query.value(2).toString().at(0) + ".");
    }
}

void Schedule::GetServicesList()
{
    servicesList.clear();

    QSqlQuery query("SELECT service, price FROM services");

    if (!query.exec()) {
        QMessageBox::critical(0, "Ошибка", "Ошибка при подключении к списку услуг.");
        return;
    }

    while(query.next())
    {
        servicesList.append(query.value(0).toString());
    }
}


Schedule::~Schedule()
{
    delete ui;
}

void Schedule::on_calendarWidget_selectionChanged()
{
    currentDate = ui->calendarWidget->selectedDate();

    ClearTable();
    UpdateSchedule();

    ui->dateLabel->setText("Просмотр расписания за " + currentDate.toString("dd.MM.yyyy"));

}

void Schedule::on_addButton_clicked()
{
    Client Client;
    Client.setModal(true);
    Client.SetServicesList(&servicesList);
    Client.SetEmployeesList(&employeesList);
    Client.SetTimeStart(startTime);
    Client.SetTimeEnd(endTime);
    Client.setWindowTitle("Информация о сотруднике");

    if (Client.exec() == QDialog::Accepted)
    {
        QMessageBox::information(nullptr, "Запись", "Клиент записан.");
        UpdateSchedule();
    }
}

void Schedule::on_deleteButton_clicked()
{
    QList<QTableWidgetItem*> items = ui->mainTableWidget->selectedItems();

    if (!items.isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText("Удалить выбранную запись?");

        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        msgBox.setButtonText(QMessageBox::Yes, "Да");
        msgBox.setButtonText(QMessageBox::No, "Нет");

        int ret = msgBox.exec();

        if (ret == QMessageBox::Yes)
        {
            QTableWidgetItem *item = items.first();

            int row = item->row();
            int column = item->column();

            QSqlQuery query;
            query.prepare("DELETE FROM schedule WHERE last_name = :last_name AND first_name = :first_name AND phone = :phone AND service = :service AND employee = :employee AND date = :date AND time = :time");

            QString currentClient = ui->mainTableWidget->item(row, column)->text();
            QStringList currentClientData = currentClient.split(QRegExp("[\n]"), QString::SkipEmptyParts);

            QString temp;
            if (currentClientData.size() == 4)
            {
                currentClientData.append(ui->mainTableWidget->horizontalHeaderItem(column)->text());
                currentClientData.append(currentDate.toString("yyyy-MM-dd"));
                currentClientData.append(ui->mainTableWidget->verticalHeaderItem(row)->text());
                currentClientData.append("");
            }
            else if (currentClientData.size() == 5)
            {
                temp = currentClientData.at(4);
                currentClientData.removeLast();
                currentClientData.append(ui->mainTableWidget->horizontalHeaderItem(column)->text());
                currentClientData.append(currentDate.toString("yyyy-MM-dd"));
                currentClientData.append(ui->mainTableWidget->verticalHeaderItem(row)->text());
                currentClientData.append(temp);
            }

            query.bindValue(":last_name", currentClientData.at(0));
            query.bindValue(":first_name", currentClientData.at(1));
            query.bindValue(":phone", currentClientData.at(2));
            query.bindValue(":service", currentClientData.at(3));
            query.bindValue(":employee", ui->mainTableWidget->horizontalHeaderItem(column)->text());
            query.bindValue(":date", currentDate.toString("yyyy-MM-dd"));
            query.bindValue(":time", ui->mainTableWidget->verticalHeaderItem(row)->text());

            if (query.exec())
            {
                ClearTable();
                UpdateSchedule();
            } else
            {
                QMessageBox::critical(nullptr, "Удаление", "Ошибка при удалении.");
            }
        }
        else if (ret == QMessageBox::No)
        {
            return;
        }
    }
    else
    {
        QMessageBox::information(nullptr, "Ошибка", "Не выбрана запись для удаления.");
    }
}

void Schedule::on_pushButton_clicked()
{
    QApplication::quit();
}

void Schedule::on_pushButton_2_clicked()
{
    this->accept();
}

void Schedule::on_editButton_clicked()
{
    QList<QTableWidgetItem*> items = ui->mainTableWidget->selectedItems();


    if (!items.isEmpty())
    {
        QTableWidgetItem *item = items.first();
        int row = item->row();
        int column = item->column();

        QString currentClient = ui->mainTableWidget->item(row, column)->text();
        QStringList currentClientData = currentClient.split(QRegExp("[\n]"), QString::SkipEmptyParts);

        QString temp;
        if (currentClientData.size() == 4)
        {
            currentClientData.append(ui->mainTableWidget->horizontalHeaderItem(column)->text());
            currentClientData.append(currentDate.toString("yyyy-MM-dd"));
            currentClientData.append(ui->mainTableWidget->verticalHeaderItem(row)->text());
            currentClientData.append("");
        }
        else if (currentClientData.size() == 5)
        {
            temp = currentClientData.at(4);
            currentClientData.removeLast();
            currentClientData.append(ui->mainTableWidget->horizontalHeaderItem(column)->text());
            currentClientData.append(currentDate.toString("yyyy-MM-dd"));
            currentClientData.append(ui->mainTableWidget->verticalHeaderItem(row)->text());
            currentClientData.append(temp);
        }


        QSqlQuery query;
        query.prepare("UPDATE schedule SET "
                      "last_name = :newLastName, first_name = :newFirstName, "
                      "phone = :newPhone, service = :newService, employee = :newEmployee, "
                      "date = :newDate, time = :newTime, additional = :newAdditional "
                      "WHERE last_name = :last_name AND first_name = :first_name AND phone = :phone AND service = :service AND employee = :employee AND date = :date AND time = :time");

        query.bindValue(":last_name", currentClientData.at(0));
        query.bindValue(":first_name", currentClientData.at(1));
        query.bindValue(":phone", currentClientData.at(2));
        query.bindValue(":service", currentClientData.at(3));
        query.bindValue(":employee", ui->mainTableWidget->horizontalHeaderItem(column)->text());
        query.bindValue(":date", currentDate.toString("yyyy-MM-dd"));
        query.bindValue(":time", ui->mainTableWidget->verticalHeaderItem(row)->text());

        Client Client;
        Client.setModal(true);

        Client.SetServicesList(&servicesList);
        Client.SetEmployeesList(&employeesList);
        Client.SetData(currentClientData);

        Client.SetTimeStart(startTime);
        Client.SetTimeEnd(endTime);

        Client.setWindowTitle("Информация о сотруднике");

        if (Client.exec() == QDialog::Accepted)
        {

            QStringList* newClientData = Client.GetData();

            query.bindValue(":newLastName", newClientData->at(0));
            query.bindValue(":newFirstName", newClientData->at(1));
            query.bindValue(":newPhone", newClientData->at(2));
            query.bindValue(":newService", newClientData->at(3));
            query.bindValue(":newEmployee", newClientData->at(4));
            query.bindValue(":newDate", newClientData->at(5));
            query.bindValue(":newTime", newClientData->at(6));
            query.bindValue(":newAdditional", newClientData->at(7));

            if (!query.exec())
            {
                QMessageBox::critical(nullptr, "Ошибка", "Ошибка при редактировании." + query.lastError().text());
            } else
            {
                QMessageBox::information(nullptr, "Редактирование", "Запись отредактирована.");
                ClearTable();
                UpdateSchedule();
            }
            delete newClientData;
        }
    }
    else
    {
        QMessageBox::information(nullptr, "Ошибка", "Не выбрана запись редактирования.");
    }
}
