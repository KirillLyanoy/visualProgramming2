#ifndef EDITOR_H
#define EDITOR_H

#include <QDialog>
#include <QSqlTableModel>

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

private:
    Ui::Editor *ui;

    QSqlTableModel* services;
    QSqlTableModel* users;
    QSqlTableModel* employees;

    QString currentTableName;

    int currentRow;
};

#endif // EDITOR_H
