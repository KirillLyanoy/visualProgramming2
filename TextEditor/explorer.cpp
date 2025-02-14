#include "explorer.h"
#include "ui_explorer.h"
#include <QFileSystemModel>
#include <QModelIndex>

Explorer::Explorer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Explorer)
{
    ui->setupUi(this);

    QList<QFileInfo> drives = QDir::drives();

    QMap<QString, QFileInfo> drivesMap;

    foreach(const QFileInfo &fileInfo, drives)
    {
        drivesMap.insert(fileInfo.fileName(), fileInfo);
    }

    ui->comboBox->addItems(drivesMap.keys());

    QFileSystemModel *fileSystemModel = new QFileSystemModel;
    fileSystemModel->setRootPath(QDir::currentPath());

    ui->listView->setModel(fileSystemModel);
    ui->listView->setRootIndex(fileSystemModel->index(QDir::currentPath()));

}

Explorer::~Explorer()
{
    delete ui;
}

//  QList<QFileInfo> drives = QDir::drives();
//    for (const QFileInfo &drive : drives) {
//      qDebug() << "Drive:" << drive.absoluteFilePath();
//  }
