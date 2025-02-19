#include "filename.h"
#include "ui_filename.h"
#include <QMessageBox>

FileName::FileName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileName)
{
    ui->setupUi(this);
}



bool FileName::checkName(QString name)
{
    if (name.contains("[\\\\/:*?\"<>|]") || name.isEmpty()) return false;
    return true;
}

QString name;

QString FileName::getName()
{
    return name;
}

FileName::~FileName()
{
    delete ui;
}

void FileName::on_pushButton_2_clicked()
{
    FileName::close();
}

void FileName::on_pushButton_clicked()
{
    if (checkName(ui->lineEdit->text()))
    {
        name = ui->lineEdit->text() + ".txt";
        FileName::accept();
    }
    else
    {
        QMessageBox::critical(0, "Ошибка", "Неправильное название файла");
    }
}
