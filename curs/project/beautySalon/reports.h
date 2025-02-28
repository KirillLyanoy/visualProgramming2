#ifndef REPORTS_H
#define REPORTS_H

#include <QDialog>

namespace Ui {
class Reports;
}

class Reports : public QDialog
{
    Q_OBJECT

public:
    explicit Reports(QWidget *parent = nullptr);
    ~Reports();

private slots:
    void on_ExitButton_clicked();

    void on_cashButton_clicked();

    void on_servicesButton_clicked();

    void on_workButton_clicked();

    void on_monthComboBox_currentIndexChanged(const QString &arg1);

    void on_temporaryButton_clicked();

    void on_yearComboBox_currentIndexChanged(const QString &arg1);

    void on_generateReportButton_clicked();

private:
    Ui::Reports *ui;

    void Clear();
    void SetComboBoxDays(QString month);
    void ChangeVisibleElements(bool value);
    void GetServicesList();
    void GetEmployeesList();

    void GenerateCashReport();
    void GenerateServiceReport();
    void GenerateWorkReport();

    QString cashTitle;
    QString workTitle;
    QString serviceTitle;

    QList<QString> employeesList;
    QList<QString> servicesList;
    bool visibleElementsIndex;

};

#endif // REPORTS_H
