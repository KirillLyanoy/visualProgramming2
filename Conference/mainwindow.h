#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_scheduleTableView_clicked(const QModelIndex &index);

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_scheduleTableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;

    int currentRow;

    QSqlTableModel *conferences;
    QSqlTableModel *schedule;
    QSqlTableModel *participants;
};

#endif // MAINWINDOW_H
