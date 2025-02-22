#include "invitations.h"
#include "ui_invitations.h"
#include <QMessageBox>

invitations::invitations(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::invitations)
{
    ui->setupUi(this);
}

void invitations::setParticipants(QSqlTableModel *participants)
{
    this->participants = participants;
    updateTableView();
}

void invitations::setCity(QString city)
{
    currentCity = city;
    filterByCity();
}

void invitations::filterByCity()
{
    participants->setFilter("city = '" + currentCity + "'");

    for (int row = 0; row < participants->rowCount(); ++row)
    {
        QString name = participants->data(participants->index(row, participants->fieldIndex("name"))).toString();
        QString city = participants->data(participants->index(row, participants->fieldIndex("city"))).toString();
        QString number = participants->data(participants->index(row, participants->fieldIndex("number"))).toString();
    }
}

void invitations::updateTableView()
{
    ui->tableView->setModel(participants);
}

invitations::~invitations()
{
    delete ui;
}

void invitations::sendInvitations(int invitationsCount)
{
    QString count = QString::number(invitationsCount);
    if (count == "1")
        QMessageBox::information(0, "Отправка", "Выслано " + count + " приглашение");
    else if (count == "2" || count == "3" || count == "4")
        QMessageBox::information(0, "Отправка", "Выслано " + count + " приглашения");
    else
        QMessageBox::information(0, "Отправка", "Выслано " + count + " приглашений");
}

void invitations::on_pushButton_2_clicked()
{
    sendInvitations(ui->tableView->selectionModel()->selectedRows().count());
}

void invitations::on_pushButton_3_clicked()
{
    sendInvitations(participants->rowCount());
}

void invitations::on_pushButton_clicked()
{
    this->close();
}

void invitations::on_pushButton_4_clicked()
{
    invitations::participants->insertRow(participants->rowCount());
}

void invitations::on_pushButton_5_clicked()
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
        invitations::participants->removeRow(currentRow);
        participants->select();
    }
    if (ret == QMessageBox::No)
        return;
}

void invitations::on_tableView_clicked(const QModelIndex &index)
{
    currentRow = index.row();
}

void invitations::on_checkBox_stateChanged(int arg1)
{
    if (ui->checkBox->isChecked())
    {
       filterByCity();
    }
    else
    {
        participants->setFilter("");
        participants->select();
    }
}
