#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QDate>

namespace Ui {
class Client;
}

class Client : public QDialog
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = nullptr);
    ~Client();

    void SetEmployeesList(QList<QString> *employees);
    void SetServicesList(QList<QString> *services);

    void SetTimeStart(QTime time);
    void SetTimeEnd(QTime time);

    void SetClientExist(bool value);

    void SetData(QStringList client);
    QStringList* GetData();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::Client *ui;

    void Clear();
    void UpdateEmployees();
    void UpdateServices();

    QList<QString> *currentEmployees;
    QList<QString> *currentServices;

    bool clientExist;
    QStringList client;

    QTime timeStart;
    QTime timeEnd;

};

#endif
