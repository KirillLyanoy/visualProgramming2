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

void Editor::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles) {
    if (!roles.isEmpty() && !roles.contains(Qt::EditRole))
    {
        return;
    }

    int row = topLeft.row();
    int column = topLeft.column();
    QString newValue = topLeft.model()->data(topLeft, Qt::DisplayRole).toString();

    if (ui->tableView->model() == users)
    {
        if (column == 3 && newValue != "руководитель" && newValue != "администратор")
        {
            QMessageBox::information(nullptr, "Ошибка", "Роль может быть только \"руководитель\" или \"администратор\".");

            QAbstractItemModel *model = const_cast<QAbstractItemModel*>(topLeft.model());

            if (temporaryTableItem == "руководитель" || temporaryTableItem == "администратор")
            {
                model->setData(topLeft, temporaryTableItem, Qt::EditRole);
                return;
            }
            else
            {
                model->setData(topLeft, "руководитель", Qt::EditRole);
                return;
            }
        }
    }

    if (newValue.isEmpty())
    {
        QMessageBox::information(nullptr, "Ошибка", "Поле не может быть пустым.");

        QAbstractItemModel *model = const_cast<QAbstractItemModel*>(topLeft.model());
        model->setData(topLeft, temporaryTableItem, Qt::EditRole);
    }
}


void Editor::on_employeesListButton_clicked()
{
    ui->tableView->setModel(employees);
    currentTableName = "employees";
    currentRow = -1;    

    connect(ui->tableView->model(), &QAbstractItemModel::dataChanged,
            this, &Editor::onDataChanged);

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

    connect(ui->tableView->model(), &QAbstractItemModel::dataChanged,
            this, &Editor::onDataChanged);

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

    connect(ui->tableView->model(), &QAbstractItemModel::dataChanged,
            this, &Editor::onDataChanged);

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
                employees->blockSignals(true);
                employees->removeRow(currentRow);
                employees->select();
                employees->blockSignals(false);

                ui->tableView->setModel(nullptr);
                ui->tableView->setModel(employees);
            }
            else if (currentTableName == "users")
            {
                    users->blockSignals(true);
                    users->removeRow(currentRow);
                    users->select();
                    users->blockSignals(false);

                    ui->tableView->setModel(nullptr);
                    ui->tableView->setModel(users);
            }
            else if (currentTableName == "services")
            {
                services->blockSignals(true);
                services->removeRow(currentRow);
                services->select();
                services->blockSignals(false);

                ui->tableView->setModel(nullptr);
                ui->tableView->setModel(services);
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

void Editor::on_tableView_doubleClicked(const QModelIndex &index)
{
    temporaryTableItem = index.data(Qt::DisplayRole).toString();

    if (temporaryTableItem.isEmpty()) temporaryTableItem = "Пусто";
}
