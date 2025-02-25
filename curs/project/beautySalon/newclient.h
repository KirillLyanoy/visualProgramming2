#ifndef NEWCLIENT_H
#define NEWCLIENT_H

#include <QDialog>
#include <QDate>

namespace Ui {
class NewClient;
}

class NewClient : public QDialog
{
    Q_OBJECT

public:
    explicit NewClient(QWidget *parent = nullptr);
    ~NewClient();

    void SetEmployeesList(QList<QString> *employees);
    void SetServicesList(QList<QString> *services);

private slots:
    void on_pushButton_clicked();
    void Clear();

    void on_pushButton_2_clicked();

private:
    Ui::NewClient *ui;



    QList<QString> *currentEmployees;
    QList<QString> *currentServices;

};

#endif // NEWCLIENT_H
