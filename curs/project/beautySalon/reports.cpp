#include "reports.h"
#include "ui_reports.h"
#include <QDate>
#include <QDebug>
#include <QSqlQuery>
#include <QMessageBox>
#include <QSqlError>

Reports::Reports(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reports)
{
    ui->setupUi(this);

    ui->monthComboBox->clear();
    ui->monthComboBox->addItems({
        "", "Январь", "Февраль", "Март", "Апрель", "Май", "Июнь",
        "Июль", "Август", "Сентябрь", "Октябрь", "Ноябрь", "Декабрь"
    });

    ui->yearComboBox->clear();
    for (int i = 0; i < 50; i++)
    {
        ui->yearComboBox->addItem(QString::number(1990 + i));
    }

    ui->resultLineEdit->clear();
    ui->yearComboBox->setCurrentText(QString::number(QDate::currentDate().year()));

    cashTitle = "Отчёт о доходах\nсалона";
    workTitle = "Отчёт о работе\nсотрудника";
    serviceTitle = "Отчёт о выполнении\nуслуги";

    ChangeVisibleElements(false);
}

Reports::~Reports()
{
    delete ui;
}

void Reports::GetEmployeesList()
{
    employeesList.clear();

    QSqlQuery query("SELECT last_name, first_name, middle_name FROM employees");

    if (!query.exec())
    {
        QMessageBox::critical(0, "Ошибка", "Ошибка при подключении к списку сотрудников.");
        return;
    }

    while(query.next())
    {
        employeesList.append(query.value(0).toString() + " " + query.value(1).toString().at(0) +
                              ". " +  query.value(2).toString().at(0) + ".");
    }
}

void Reports::GetServicesList()
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

void Reports::ChangeVisibleElements(bool value)
{
    ui->temporaryLabel->setVisible(value);
    ui->temporaryComboBox->setVisible(value);

    ui->titleLabel->setVisible(value);
    ui->generateReportButton->setVisible(value);

    ui->label->setVisible(value);
    ui->label_2->setVisible(value);
    ui->label_3->setVisible(value);

    ui->dayComboBox->setVisible(value);
    ui->monthComboBox->setVisible(value);
    ui->yearComboBox->setVisible(value);

    visibleElementsIndex = value;
}

void Reports::SetComboBoxDays(QString month)
{
    ui->dayComboBox->clear();
    ui->dayComboBox->addItems({
          "", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14",
          "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28"
    });

    if (month == "Январь" || month == "Март" || month == "Май" || month == "Июль" || month == "Август" || month == "Октябрь" || month == "Декабрь")
    {
        ui->dayComboBox->addItems({
          "29", "30", "31"
        });
    }
    else if (month == "Апрель" || month == "Июнь" || month == "Сентябрь" || month == "Ноябрь")
    {
        ui->dayComboBox->addItems({
          "29", "30"
        });
    }
    else if (month == "Февраль")
    {
        if((ui->yearComboBox->currentText().toInt() - 1992) % 4 == 0)
        {
            ui->dayComboBox->addItem("29");
        }
    }
}

void Reports::Clear()
{
    ui->temporaryLabel->setText("");
    ui->temporaryLabel->setVisible(false);
    ui->temporaryComboBox->clear();
    ui->temporaryComboBox->setVisible(false);
}

void Reports::on_ExitButton_clicked()
{
    this->close();
}

void Reports::on_cashButton_clicked()
{
    if (!visibleElementsIndex) ChangeVisibleElements(true);
    ui->temporaryLabel->setVisible(false);
    ui->temporaryComboBox->setVisible(false);
    visibleElementsIndex = false;

    ui->titleLabel->setText(cashTitle);
}

void Reports::on_servicesButton_clicked()
{
    if (!visibleElementsIndex) ChangeVisibleElements(true);

    ui->titleLabel->setText(serviceTitle);

    ui->temporaryLabel->setText("Услуга:");
    GetServicesList();
    ui->temporaryComboBox->clear();
    ui->temporaryComboBox->addItems(servicesList);
}

void Reports::on_workButton_clicked()
{
    if (!visibleElementsIndex) ChangeVisibleElements(true);
    ui->titleLabel->setText(workTitle);

    ui->temporaryLabel->setText("Работник:");

    GetEmployeesList();
    ui->temporaryComboBox->clear();
    ui->temporaryComboBox->addItems(employeesList);

}

void Reports::on_monthComboBox_currentIndexChanged(const QString &arg1)
{
    SetComboBoxDays(arg1);
}

void Reports::GenerateCashReport()
{
    QString date = ui->yearComboBox->currentText();
    QSqlQuery query;
    ui->tableWidget->clear();

    QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
    QString currentTime = QTime::currentTime().toString("HH:mm");

    int sum = 0;
    int currentRow = 0;

    QMap<QString, int> price;
    query.prepare("SELECT * FROM services");
    if (query.exec())
    {
        while (query.next())
        {
            price.insert(query.value(0).toString(), query.value(1).toInt());
        }
    } else
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при обращении к списку услуг.");
    }


    if (!ui->monthComboBox->currentText().isEmpty())
    {
        query.clear();
        date += "-" + QString::number(ui->monthComboBox->currentIndex()).rightJustified(2, '0');;

        if (!ui->dayComboBox->currentText().isEmpty())
        {
           date += "-" + QString::number(ui->dayComboBox->currentIndex()).rightJustified(2, '0');;

           query.prepare("SELECT * FROM schedule "
                         "WHERE date = :date "
                         "AND (date < :currentDate "
                         "OR (date = :currentDate AND time < :currentTime));");
           query.bindValue(":date", date);
           query.bindValue(":currentDate", currentDate);
           query.bindValue(":currentTime", currentTime);
        }
        else
        {
            query.prepare("SELECT * FROM schedule "
                          "WHERE date LIKE :date_pattern "
                          "AND (date < :currentDate "
                          "OR (date = :currentDate AND time < :currentTime));");
            query.bindValue(":date_pattern", date + "-%");
            query.bindValue(":currentDate", currentDate);
            query.bindValue(":currentTime", currentTime);
        }
    }
    else
    {
        query.prepare("SELECT * FROM schedule "
                      "WHERE date LIKE :date_pattern "
                      "AND (date < :currentDate "
                      "OR (date = :currentDate AND time < :currentTime));");
        query.bindValue(":date_pattern", date + "%");
        query.bindValue(":currentDate", currentDate);
        query.bindValue(":currentTime", currentTime);
    }

    if (query.exec())
    {
        int rowCount = 0;
        while (query.next())
        {
            rowCount++;
        }
        query.seek(-1);

        ui->tableWidget->setRowCount(rowCount);
        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Услуга"));
        ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Работник"));
        ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Дата"));
        ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Время"));
        ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Стоимость"));

        while (query.next())
        {
            QTableWidgetItem* service = new QTableWidgetItem(query.value(3).toString());
            QTableWidgetItem* employee = new QTableWidgetItem(query.value(4).toString());
            QTableWidgetItem* date = new QTableWidgetItem(query.value(5).toString());
            QTableWidgetItem* time = new QTableWidgetItem(query.value(6).toString());
            QTableWidgetItem* servicePrice = new QTableWidgetItem(QString::number(price.value(query.value(3).toString())));

            ui->tableWidget->setItem(currentRow, 0, service);
            ui->tableWidget->setItem(currentRow, 1, employee);
            ui->tableWidget->setItem(currentRow, 2, date);
            ui->tableWidget->setItem(currentRow, 3, time);
            ui->tableWidget->setItem(currentRow, 4, servicePrice);
            sum += price.value(query.value(3).toString());
            currentRow++;
        }
    } else
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при обращении к расписанию клиентов." + query.lastError().text());
    }

    ui->resultLineEdit->setText("Доход: " + QString::number(sum) + " р. ");
}

void Reports::GenerateServiceReport()
{
    QString date = ui->yearComboBox->currentText();
    QSqlQuery query;
    ui->tableWidget->clear();
    int count = 0;

    QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
    QString currentTime = QTime::currentTime().toString("HH:mm");

    int currentRow = 0;

    if (!ui->monthComboBox->currentText().isEmpty())
    {
        date += "-" + QString::number(ui->monthComboBox->currentIndex()).rightJustified(2, '0');;

        if (!ui->dayComboBox->currentText().isEmpty())
        {
           date += "-" + QString::number(ui->dayComboBox->currentIndex()).rightJustified(2, '0');;

           query.prepare("SELECT * FROM schedule "
                         "WHERE service = :service "
                         "AND date = :date "
                         "AND (date < :currentDate "
                         "OR (date = :currentDate AND time < :currentTime));"
           );
           query.bindValue(":date", date);
           query.bindValue(":service", ui->temporaryComboBox->currentText());
           query.bindValue(":currentDate", currentDate);
           query.bindValue(":currentTime", currentTime);
        }
        else
        {
            query.prepare("SELECT * FROM schedule "
                          "WHERE service = :service "
                          "AND date LIKE :date_pattern "
                          "AND (date < :currentDate "
                          "OR (date = :currentDate AND time < :currentTime));");
            query.bindValue(":date_pattern", date + "-%");
            query.bindValue(":service", ui->temporaryComboBox->currentText());
            query.bindValue(":currentDate", currentDate);
            query.bindValue(":currentTime", currentTime);
        }
    }
    else
    {
        query.prepare("SELECT * FROM schedule "
                      "WHERE service = :service "
                      "AND date LIKE :date_pattern "
                      "AND (date < :currentDate "
                      "OR (date = :currentDate AND time < :currentTime));");
        query.bindValue(":date_pattern", date + "%");
        query.bindValue(":service", ui->temporaryComboBox->currentText());
        query.bindValue(":currentDate", currentDate);
        query.bindValue(":currentTime", currentTime);
    }

    if (query.exec())
    {
        int rowCount = 0;
        while (query.next())
        {
            rowCount++;
        }
        query.seek(-1);

        ui->tableWidget->setRowCount(rowCount);
        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Услуга"));
        ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Работник"));
        ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Дата"));
        ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Время"));

        while (query.next())
        {
            QTableWidgetItem* service = new QTableWidgetItem(query.value(3).toString());
            QTableWidgetItem* employee = new QTableWidgetItem(query.value(4).toString());
            QTableWidgetItem* date = new QTableWidgetItem(query.value(5).toString());
            QTableWidgetItem* time = new QTableWidgetItem(query.value(6).toString());

            ui->tableWidget->setItem(currentRow, 0, service);
            ui->tableWidget->setItem(currentRow, 1, employee);
            ui->tableWidget->setItem(currentRow, 2, date);
            ui->tableWidget->setItem(currentRow, 3, time);
            currentRow++;
            count++;
        }
    } else
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при обращении к расписанию клиентов." + query.lastError().text());
    }
    ui->resultLineEdit->setText("Услуга выполнена : " + QString::number(count) + " раз ");
}

void Reports::GenerateWorkReport()
{
    QString date = ui->yearComboBox->currentText();
    QSqlQuery query;
    ui->tableWidget->clear();

    QString currentDate = QDate::currentDate().toString("yyyy-MM-dd");
    QString currentTime = QTime::currentTime().toString("HH:mm");

    int sum = 0;
    int currentRow = 0;

    QMap<QString, int> price;
    query.prepare("SELECT * FROM services");
    if (query.exec())
    {
        while (query.next())
        {
            price.insert(query.value(0).toString(), query.value(1).toInt());
        }
    } else
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при обращении к списку услуг.");
    }

    if (!ui->monthComboBox->currentText().isEmpty())
    {
        query.clear();
        date += "-" + QString::number(ui->monthComboBox->currentIndex()).rightJustified(2, '0');;

        if (!ui->dayComboBox->currentText().isEmpty())
        {
           date += "-" + QString::number(ui->dayComboBox->currentIndex()).rightJustified(2, '0');;

           query.prepare("SELECT * FROM schedule "
                         "WHERE date = :date "
                         "AND employee = :employee "
                         "AND (date < :currentDate "
                         "OR (date = :currentDate AND time < :currentTime));");
           query.bindValue(":date", date);
           query.bindValue(":employee", ui->temporaryComboBox->currentText());
           query.bindValue(":currentDate", currentDate);
           query.bindValue(":currentTime", currentTime);
        }
        else
        {
            query.prepare("SELECT * FROM schedule "
                          "WHERE date LIKE :date_pattern "
                          "AND employee = :employee "
                          "AND (date < :currentDate "
                          "OR (date = :currentDate AND time < :currentTime));");
            query.bindValue(":date_pattern", date + "-%");
            query.bindValue(":employee", ui->temporaryComboBox->currentText());
            query.bindValue(":currentDate", currentDate);
            query.bindValue(":currentTime", currentTime);
        }
    }
    else
    {
        query.prepare("SELECT * FROM schedule "
                      "WHERE date LIKE :date_pattern "
                      "AND employee = :employee "
                      "AND (date < :currentDate "
                      "OR (date = :currentDate AND time < :currentTime));");
        query.bindValue(":date_pattern", date + "%");
        query.bindValue(":employee", ui->temporaryComboBox->currentText());
        query.bindValue(":currentDate", currentDate);
        query.bindValue(":currentTime", currentTime);
    }

    if (query.exec())
    {
        int rowCount = 0;
        while (query.next())
        {
            rowCount++;
        }
        query.seek(-1);

        ui->tableWidget->setRowCount(rowCount);
        ui->tableWidget->setColumnCount(5);
        ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Услуга"));
        ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Работник"));
        ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Дата"));
        ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Время"));
        ui->tableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem("Стоимость"));

        while (query.next())
        {
            QTableWidgetItem* service = new QTableWidgetItem(query.value(3).toString());
            QTableWidgetItem* employee = new QTableWidgetItem(query.value(4).toString());
            QTableWidgetItem* date = new QTableWidgetItem(query.value(5).toString());
            QTableWidgetItem* time = new QTableWidgetItem(query.value(6).toString());
            QTableWidgetItem* servicePrice = new QTableWidgetItem(QString::number(price.value(query.value(3).toString())));

            ui->tableWidget->setItem(currentRow, 0, service);
            ui->tableWidget->setItem(currentRow, 1, employee);
            ui->tableWidget->setItem(currentRow, 2, date);
            ui->tableWidget->setItem(currentRow, 3, time);
            ui->tableWidget->setItem(currentRow, 4, servicePrice);
            sum += price.value(query.value(3).toString());
            currentRow++;
        }
    } else
    {
        QMessageBox::critical(nullptr, "Ошибка", "Ошибка при обращении к расписанию клиентов." + query.lastError().text());
    }

    ui->resultLineEdit->setText("Доход работника: " + QString::number(sum) + " р. ");
}

void Reports::on_yearComboBox_currentIndexChanged(const QString &arg1)
{
    if (ui->monthComboBox->currentIndex() == 2)
    {
        SetComboBoxDays("Февраль");
    }
}

void Reports::on_generateReportButton_clicked()
{
    if (ui->titleLabel->text() == cashTitle)
    {
        GenerateCashReport();
    }
    else if (ui->titleLabel->text() == serviceTitle)
    {
        GenerateServiceReport();
    }
    else if (ui->titleLabel->text() == workTitle)
    {
        GenerateWorkReport();
    }
}
