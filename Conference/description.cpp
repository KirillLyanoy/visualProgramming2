#include "description.h"
#include "ui_description.h"
#include <QMessageBox>

description::description(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::description)
{
    ui->setupUi(this);
    ChangeReadOnly(true);
    isEdited = false;
}

bool description::IsEdited()
{
    return this->isEdited;
}
void description::SetName(QString name)
{
    ui->lineEdit->setText(name);
}
void description::SetShortDescription(QString shortDescription)
{
    ui->textEdit->setText(shortDescription);
}
void description::SetOrginizer(QString organizer)
{
    ui->lineEdit_2->setText(organizer);
}
void description::SetDuration(QTime duration)
{
    ui->timeEdit->setTime(duration);
}

QString description::GetName()
{
    return this->name;
}
QString description::GetShortDescription()
{
    return this->shortDescription;
}
QString description::GetOrginizer()
{
    return this->organizer;
}
QTime description::GetDuration()
{
    return this->duration;
}

void description::UpdateView()
{
    ui->lineEdit->setText(this->name);
    ui->textEdit->setText(this->shortDescription);
    ui->lineEdit_2->setText(this->organizer);
    ui->timeEdit->setTime(this->duration);
}

void description::ChangeReadOnly(bool value)
{
    ui->lineEdit->setReadOnly(value);
    ui->lineEdit_2->setReadOnly(value);
    ui->timeEdit->setReadOnly(value);
    ui->textEdit->setReadOnly(value);
}

description::~description()
{
    delete ui;
}

void description::on_pushButton_3_clicked()
{
    ChangeReadOnly(false);
}

void description::on_pushButton_2_clicked()
{
    this->name = ui->lineEdit->text();
    this->shortDescription = ui->textEdit->toPlainText();
    this->organizer = ui->lineEdit_2->text();
    this->duration = ui->timeEdit->time();

    this->isEdited = true;

    QMessageBox::information(0, "Сохранение", "Изменения сохранены");
}

void description::on_pushButton_clicked()
{
    this->close();
}
