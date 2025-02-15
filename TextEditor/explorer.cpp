#include "explorer.h"
#include "ui_explorer.h"
#include <QFileSystemModel>
#include <QModelIndex>

QList<QString> drivesList;
QString currentPath = QDir::currentPath();


Explorer::Explorer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Explorer)
{
    ui->setupUi(this);

    QList<QFileInfo> drives = QDir::drives();

    foreach(const QFileInfo &drive, drives)
    {
        drivesList.append(drive.absoluteFilePath());
    }
    ui->comboBox->addItems(drivesList);

    QFileSystemModel *fileSystemModel = new QFileSystemModel;
    fileSystemModel->setRootPath(currentPath);

    ui->listView->setModel(fileSystemModel);
    ui->listView->setRootIndex(fileSystemModel->index(currentPath));

}

Explorer::~Explorer()
{
    delete ui;
}

void Explorer::on_upPushBotton_clicked()
{

}



void Explorer::on_comboBox_currentTextChanged(const QString &arg1)
{
    QFileSystemModel *fileSystemModel = new QFileSystemModel;
    fileSystemModel->setRootPath(arg1);

    ui->listView->setModel(fileSystemModel);
    ui->listView->setRootIndex(fileSystemModel->index(arg1));
}

void Explorer::on_listView_doubleClicked(const QModelIndex &index)
{
   // QString path = currentPath + index.QT::DisplayRole;


}
