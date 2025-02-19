#include "filename.h"
#include "ui_filename.h"
#include <QMessageBox>

FileName::FileName(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileName)
{
    ui->setupUi(this);

    QList<QString> extensionList { ".txt", ".html" };
    ui->comboBox->addItems(extensionList);
    extension = extensionList[0];

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
        if (extension == ".txt")
        {
            QMessageBox msgBox;
            msgBox.setIcon(QMessageBox::Question);
            msgBox.setText("Формат .txt не сохраняет формат текста. Продолжить?");

            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

            msgBox.setButtonText(QMessageBox::Yes, "Да");
            msgBox.setButtonText(QMessageBox::No, "Нет");

            int ret = msgBox.exec();

            if (ret == QMessageBox::No)
                return;
        }


        name = ui->lineEdit->text() + extension;
        FileName::accept();

    }
    else
    {
        QMessageBox::critical(0, "Ошибка", "Неправильное название файла");
    }
}

void FileName::on_comboBox_activated(const QString &arg1)
{
    extension = arg1;
}
