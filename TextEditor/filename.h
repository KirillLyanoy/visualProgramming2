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

private:
    Ui::FileName *ui;

    QString name;

};

#endif // FILENAME_H
