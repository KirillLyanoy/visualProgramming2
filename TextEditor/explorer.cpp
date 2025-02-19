#include "explorer.h"
#include "ui_explorer.h"
#include <QFileSystemModel>
#include <QModelIndex>
#include <QStringListModel>
#include <QMessageBox>
#include <QTextStream>
#include "mainwindow.h"
#include <QListWidgetItem>

void Explorer::setAction(Actions action)
{
    currentAction = action;

    if (currentAction == Actions::open)
    {
        ui->confirmPushButton->setText("Открыть");
    }
    else if (action == Actions::save)
    {
       ui->confirmPushButton->setText("Сохранить");
    }
}

QString Explorer::getPath()
{
    return currentPath;
}

Explorer::Explorer(QWidget *parent) :

    QDialog(parent),
    ui(new Ui::Explorer)
    {
        ui->setupUi(this);

        currentPath = QDir::currentPath();
        fileSystemModel = new QFileSystemModel;


        if (drivesList.length() == 0)
        {
            QList<QFileInfo> drives = QDir::drives();

            foreach(const QFileInfo &drive, drives)
            {
                drivesList.append(drive.absoluteFilePath());
            }
        }
        ui->comboBox->addItems(drivesList);

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
    QFileInfo current(currentPath);

    if (!current.isRoot())
    {
        currentPath = current.absolutePath();

        ui->listView->setModel(fileSystemModel);
        ui->listView->setRootIndex(fileSystemModel->index(currentPath));
    }
}

void Explorer::on_comboBox_currentTextChanged(const QString &arg1)
{
    QFileSystemModel *fileSystemModel = new QFileSystemModel;
    fileSystemModel->setRootPath(arg1);

    ui->listView->setModel(fileSystemModel);
    ui->listView->setRootIndex(fileSystemModel->index(arg1));

    currentPath = arg1;
}

void Explorer::on_listView_doubleClicked(const QModelIndex &index)
{   
    QString path = currentPath + "/" + index.data(Qt::DisplayRole).toString();

    QFileInfo current(path);   

    Open(current, path);
}

bool Explorer::TxtFileCheck(QFileInfo current)
{
     QString extension = current.suffix();
     if (extension.compare("txt", Qt::CaseInsensitive) == 0) return true;
     else return false;
}

void Explorer::on_cancelPushButton_clicked()
{
    Explorer::close();
}

void Explorer::Open(QFileInfo current, QString path)
{
    if (current.isDir())
    {
        currentPath = path;
        fileSystemModel->setRootPath(currentPath);

        ui->listView->setModel(fileSystemModel);
        ui->listView->setRootIndex(fileSystemModel->index(currentPath));
    }
    else if (current.isFile() && currentAction == Explorer::open)
    {
        QString extension = current.suffix();

        if (extension.compare("txt", Qt::CaseInsensitive) == 0)
        {
            currentPath = path;
            Explorer::accept();
        }
        else
        {
            QMessageBox::critical(0, "Ошибка", "Выбранный файл не является текстовым. Выберите файл c расширением \".txt\"");
        }
    }
}

void Explorer::on_confirmPushButton_clicked()
{
    QModelIndex index = ui->listView->currentIndex();

    QString path = currentPath + "/" + index.data(Qt::DisplayRole).toString();

    QFileInfo current(path);

    if (currentAction == Actions::open)
    {
        Open(current, path);
    }
    else if (currentAction == Actions::save)
    {
        if (current.isDir())
        {
            currentPath = path;
        }
        Explorer::accept();
    }
}
