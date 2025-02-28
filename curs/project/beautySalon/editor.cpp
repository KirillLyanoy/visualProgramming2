#include "editor.h"
#include "ui_editor.h"
#include "database.h"
#include <QMessageBox>

Editor::Editor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Editor)
{
    ui->setupUi(this);

    DataBase& db = DataBase::Instance();

    services = new QSqlTableModel(this, db.getDatabase());
    services->setTable("services");
    services->select();

    employees = new QSqlTableModel(this, db.getDatabase());
    employees->setTable("employees");
    employees->select();

    users = new QSqlTableModel(this, db.getDatabase());
    users->setTable("users");
    users->select();

    currentTableName = "";
    currentRow = -1;
}

void Editor::SetSupervisorRules(bool value)
{
    ui->administratorListButton->setVisible(value);
}

Editor::~Editor()
{
    delete ui;
}

void Editor::on_employeesListButton_clicked()
{
    ui->tableView->setModel(employees);
    currentTableName = "employees";
    currentRow = -1;    

    employees->setHeaderData(0, Qt::Horizontal, tr("Фамилия"));
    employees->setHeaderData(1, Qt::Horizontal, tr("Имя"));
    employees->setHeaderData(2, Qt::Horizontal, tr("Отчество"));
    employees->setHeaderData(3, Qt::Horizontal, tr("Дата рождения"));
    employees->setHeaderData(4, Qt::Horizontal, tr("Должность"));
}

void Editor::on_administratorListButton_clicked()
{
    ui->tableView->setModel(users);
    currentTableName = "users";
    currentRow = -1;

    users->setHeaderData(0, Qt::Horizontal, tr("Логин"));
    users->setHeaderData(1, Qt::Horizontal, tr("Пароль"));
    users->setHeaderData(2, Qt::Horizontal, tr("Email"));
    users->setHeaderData(3, Qt::Horizontal, tr("Роль"));
}

void Editor::on_serviceListButton_clicked()
{
    ui->tableView->setModel(services);
    currentTableName = "services";
    currentRow = -1;

    services->setHeaderData(0, Qt::Horizontal, tr("Услуга"));
    services->setHeaderData(1, Qt::Horizontal, tr("Стоимость"));
}

void Editor::on_addButton_clicked()
{
    if (currentTableName == "employees")
    {
        employees->insertRow(employees->rowCount());
    }
    else if (currentTableName == "users")
    {
        users->insertRow(users->rowCount());
    }
    else if (currentTableName == "services")
    {
        services->insertRow(services->rowCount());
    }
    else
    {
        QMessageBox::information(nullptr, "Ошибка", "Выберите список.");
    }
}

void Editor::on_deleteButton_clicked()
{
    if (currentRow == -1)
    {
        QMessageBox::information(nullptr, "Ошибка", "Строка не выбрана.");
    }
    QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Question);
        msgBox.setText("Удалить выбранную строку?");

        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

        msgBox.setButtonText(QMessageBox::Yes, "Да");
        msgBox.setButtonText(QMessageBox::No, "Нет");

        int ret = msgBox.exec();
        if (ret == QMessageBox::Yes)
        {
            if (currentTableName == "employees")
            {
                employees->removeRow(currentRow);
                employees->select();;
            }
            else if (currentTableName == "users")
            {
                users->removeRow(currentRow);
                users->select();
            }
            else if (currentTableName == "services")
            {
                services->removeRow(currentRow);
                services->select();
            }
            else
            {
                QMessageBox::information(nullptr, "Ошибка", "Выберите список.");
            }
        }
        if (ret == QMessageBox::No)
            return;
}

void Editor::on_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}

void Editor::on_pushButton_clicked()
{
    this->close();
}
