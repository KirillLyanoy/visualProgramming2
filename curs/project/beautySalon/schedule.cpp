#include "schedule.h"
#include "ui_schedule.h"
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlTableModel>
#include "database.h"
#include "newclient.h"
#include <QTime>

Schedule::Schedule(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Schedule)
{
    ui->setupUi(this);

    GetEmployeesList();
    GetServicesList();

    startTime.setHMS(8, 0, 0);
    endTime.setHMS(18, 0, 0);
    BuildTable();
}

void Schedule::SetSupervisorRules(bool value)
{
    supervisorRules = value;
}

void Schedule::BuildTable()
{
    QTime currentTime(startTime.hour(), startTime.minute());

    while (currentTime <= endTime)
    {
        timeList.append(currentTime);
        currentTime = currentTime.addSecs((30 * 60));
    }

    ui->mainTableWidget->setRowCount(timeList.size());
    ui->mainTableWidget->setColumnCount(employeesList.size());

    for (int i = 0; i < timeList.size(); i++)
    {
        ui->mainTableWidget->setVerticalHeaderItem(i, new QTableWidgetItem(timeList[i].toString()));
    }

    for (int i = 0; i < employeesList.size(); i++)
    {
        ui->mainTableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(employeesList[i]));
    }

    for (int i = 0; i < timeList.size(); i++)
    {
        for (int j = 0; j < employeesList.size(); j++)
        {
            ui->mainTableWidget->setItem(i, j, new QTableWidgetItem(""));
        }
    }
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
}

void Schedule::on_addButton_clicked()
{
    NewClient newClient;
    newClient.setModal(true);
    newClient.SetServicesList(&servicesList);
    newClient.SetEmployeesList(&employeesList);

    //добавить редактирование главного окна
    newClient.exec();

}
