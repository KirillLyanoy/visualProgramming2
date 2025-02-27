#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDialog>
#include <QDate>
#include <QTableWidgetItem>

namespace Ui {
class Schedule;
}

class Schedule : public QDialog
{
    Q_OBJECT

public:
    explicit Schedule(QWidget *parent = nullptr);
    ~Schedule();

    void SetSupervisorRules(bool balue);
    void SetUserName(QString name);


private slots:
    void on_calendarWidget_selectionChanged();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_editButton_clicked();

    void on_mainTableWidget_itemDoubleClicked(QTableWidgetItem *item);

    void on_mainTableWidget_doubleClicked(const QModelIndex &index);

    void on_mainTableWidget_cellDoubleClicked(int row, int column);

private:
    void BuildTable();
    void GetEmployeesList();
    void GetServicesList();
    void GetTimeList(QTime *startTime, QTime *endTime);
    void UpdateSchedule();
    void ClearTable();
    void SetDefaultTableColor();
    void GetDataFromTable(QStringList *currentClientData, int row, int column);
    void addClient();
    void editClient();


    Ui::Schedule *ui;
    bool supervisorRules;
    QDate currentDate;

    QTime startTime;
    QTime endTime;

    QList<QString> employeesList;
    QList<QString> servicesList;
    QList<QTime> timeList;
    QList<QStringList> clientsList;

};

#endif // SCHEDULE_H
