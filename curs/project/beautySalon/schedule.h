#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <QDialog>
#include <QDate>

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

private slots:
    void on_calendarWidget_selectionChanged();

    void on_addButton_clicked();

private:
    void BuildTable();
    void GetEmployeesList();
    void GetServicesList();

    Ui::Schedule *ui;
    bool supervisorRules;
    QDate currentDate;

    QTime startTime;
    QTime endTime;

    QList<QString> employeesList;
    QList<QString> servicesList;
    QList<QTime> timeList;

};

#endif // SCHEDULE_H
