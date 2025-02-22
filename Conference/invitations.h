#ifndef INVITATIONS_H
#define INVITATIONS_H

#include <QDialog>
#include <QSqlTableModel>

namespace Ui {
class invitations;
}

class invitations : public QDialog
{
    Q_OBJECT

public:
    explicit invitations(QWidget *parent = nullptr);
    ~invitations();

    void setParticipants(QSqlTableModel *participants);
    void setCity(QString city);

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::invitations *ui;

    void updateTableView();

    void filterByCity();

    void sendInvitations(int invitationsCount);

    int currentRow;

    QString currentCity;
    QSqlTableModel *participants;
};

#endif // INVITATIONS_H
