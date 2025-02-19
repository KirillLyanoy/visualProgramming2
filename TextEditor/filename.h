#ifndef FILENAME_H
#define FILENAME_H

#include <QDialog>

namespace Ui {
class FileName;
}

class FileName : public QDialog
{
    Q_OBJECT

public:
    explicit FileName(QWidget *parent = nullptr);
    ~FileName();

    QString getName();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    bool checkName(QString name);

    void on_comboBox_activated(const QString &arg1);

private:
    Ui::FileName *ui;

    QString name;
    QString extension;

};

#endif // FILENAME_H
