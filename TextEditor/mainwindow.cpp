#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "explorer.h"

//документ редактируется
bool isEdit = false;
bool isNew = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    ui->mainTextEdit->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void OfferToSave() {
    QMessageBox::question(0, "Выход", "Сохранить файл?", QMessageBox::Yes, QMessageBox::No);
}


void MainWindow::on_create_triggered()
{
    if (!isEdit) {
        ui->mainTextEdit->setVisible(true);
        isEdit = true;
        isNew = true;
    }
}

void MainWindow::on_exit_triggered()
{
    if (isEdit) {
        OfferToSave();
    }
    else this->close();
}

void MainWindow::on_open_triggered()
{
    Explorer explorer;

    explorer.setModal(true);
    explorer.exec();
}
