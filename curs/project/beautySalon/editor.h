#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>
#include <QSqlTableModel>
#include <QTableWidgetItem>

namespace Ui {
class Editor;
}

class Editor : public QDialog
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);
    ~Editor();

    void SetSupervisorRules(bool value);

private slots:
    void on_employeesListButton_clicked();

    void on_administratorListButton_clicked();

    void on_serviceListButton_clicked();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight, const QVector<int> &roles);


    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::Editor *ui;

    QSqlTableModel* services;
    QSqlTableModel* users;
    QSqlTableModel* employees;
    QString temporaryTableItem;
    QString currentTableName;

    int currentRow;
};

#endif // EDITOR_H
