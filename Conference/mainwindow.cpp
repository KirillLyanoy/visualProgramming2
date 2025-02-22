#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "invitations.h"
#include "description.h"
#include <QDebug>
#include <QTextCodec>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("cp1251"));

    QStringList drivers = QSqlDatabase::drivers();
    qDebug() << "Available drivers:" << drivers;

    db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("conf");

    if (db.open())
    {
        ui->statusBar->showMessage("Подключено к базе данных: " + db.databaseName());

        schedule = new QSqlTableModel(this, db);
        schedule->setTable("schedule");
        schedule->select();

        conferences = new QSqlTableModel(this, db);
        conferences->setTable("conferences");
        conferences->select();

        participants = new QSqlTableModel(this, db);
        participants->setTable("participants");
        participants->select();

        ui->scheduleTableView->setModel(schedule);

        currentRow = -1;
    }
    else
    {
        ui->statusBar->showMessage("Ошибка при подключении к базе данных: " + db.lastError().databaseText());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    schedule->insertRow(schedule->rowCount());
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("Удалить выбранную строку?");

    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    msgBox.setButtonText(QMessageBox::Yes, "Да");
    msgBox.setButtonText(QMessageBox::No, "Нет");

    int ret = msgBox.exec();
    if (ret == QMessageBox::Yes)
    {
        schedule->removeRow(currentRow);
        schedule->select();
    }
    if (ret == QMessageBox::No)
        return;
}

void MainWindow::on_scheduleTableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}

void MainWindow::on_pushButton_4_clicked()
{
    if (currentRow >= 0)
    {
        invitations invitations;
        invitations.setModal(true);

        invitations.setParticipants(participants);

        int columnIndex = schedule->fieldIndex("city");
        QModelIndex index = schedule->index(currentRow, columnIndex);

        invitations.setCity(schedule->data(index, Qt::DisplayRole).toString());

        invitations.exec();
    }
    else
    {
        QMessageBox::information(0, "Ошибка", "Конференция не выбрана");
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if (currentRow >= 0)
    {
        description description;
        description.setModal(true);

        int columnIndex = schedule->fieldIndex("name");
        QModelIndex index = schedule->index(currentRow, columnIndex);

        int row;
        for (row = 0; row < conferences->rowCount(); ++row) {
            if (conferences->data(conferences->index(row, columnIndex)).toString() == schedule->data(index, Qt::DisplayRole).toString()) {
                break;
            }
        }

        int nameColumnIndex = conferences->fieldIndex("name");
        int descriptionColumnIndex = conferences->fieldIndex("description");
        int organizerColumnIndex = conferences->fieldIndex("organizer");
        int durationColumnIndex = conferences->fieldIndex("duration");

        QModelIndex nameIndex = conferences->index(row, nameColumnIndex);
        QModelIndex descriptionIndex = conferences->index(row, descriptionColumnIndex);
        QModelIndex organizerIndex = conferences->index(row, organizerColumnIndex);
        QModelIndex durationIndex = conferences->index(row, durationColumnIndex);

        description.SetName(conferences->data(nameIndex, Qt::DisplayRole).toString());
        description.SetShortDescription(conferences->data(descriptionIndex, Qt::DisplayRole).toString());
        description.SetOrginizer(conferences->data(organizerIndex, Qt::DisplayRole).toString());
        description.SetDuration(conferences->data(durationIndex, Qt::DisplayRole).toTime());

        description.exec();
        if (description.IsEdited())
        {
            conferences->setData(conferences->index(row, nameColumnIndex), description.GetName());
            conferences->setData(conferences->index(row, descriptionColumnIndex), description.GetShortDescription());
            conferences->setData(conferences->index(row, organizerColumnIndex), description.GetOrginizer());
            conferences->setData(conferences->index(row, durationColumnIndex), description.GetDuration().toString("HH:mm:ss"));

            conferences->submitAll();
            conferences->select();
            schedule->select();
        }
    }
    else
    {
        QMessageBox::information(0, "Ошибка", "Конференция не выбрана");
    }
}

void MainWindow::on_scheduleTableView_doubleClicked(const QModelIndex &index)
{
    conferences->select();
}
