#include "mainwindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QWidget *centralWidget = new QWidget(&w);

    QVBoxLayout *Layout1 = new QVBoxLayout;

    QLabel *label1 = new QLabel("Выберите фигуру:");
    QLabel *label2 = new QLabel("Выберите формулу:");

    Layout1->addWidget(label1);
    Layout1->addWidget(label2);

    centralWidget->setLayout(Layout1);

    w.setCentralWidget(centralWidget);
    w.show();

    return a.exec();
}
