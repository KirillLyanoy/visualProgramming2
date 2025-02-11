#include "mainwindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>

void SetFalseVisibleWidgets(QLabel *image, QLabel *inputLabel1, QLabel *inputLabel2, QLabel *inputLabel3, QLabel *inputLabel4, QLabel *inputLabel5,
                      QLineEdit *inputLineEdit1, QLineEdit *inputLineEdit2, QLineEdit *inputLineEdit3, QLineEdit *inputLineEdit4, QLineEdit *inputLineEdit5) {
    image->setVisible(false);

    inputLabel1->setVisible(false);
    inputLabel2->setVisible(false);
    inputLabel3->setVisible(false);
    inputLabel4->setVisible(false);
    inputLabel5->setVisible(false);

    inputLineEdit1->setVisible(false);
    inputLineEdit2->setVisible(false);
    inputLineEdit3->setVisible(false);
    inputLineEdit4->setVisible(false);
    inputLineEdit5->setVisible(false);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QStringList *figuresList = new QStringList({ "", "Квадрат", "Прямоугольник", "Параллелограмм", "Ромб", "Треугольник", "Трапеция", "Круг", "Сектор" });
    QStringList *squareList = new QStringList { "", "Расчет по двум сторонам", "Расчет по диагонали" };
    QStringList *rectangleList = new QStringList { "", "Расчет по двум сторонам", "Расчет по диагоналям и углу между ними" };
    QStringList *rhombusList = new QStringList { "", "Расчет по двум диагоналям", "Расчет по стороне и высоте", "Расчет по двум сторонам и углу между ними" };
    QStringList *parallelogramList = new QStringList { "", "Расчет по двум диагоналям и углу между ними", "Расчет по стороне и высоте", "Расчет по двум сторонам и углу между ними" };
    QStringList *triangleList = new QStringList { "", "Расчет по стороне и высоте", "Расчет по трем сторонам", "Расчет по 2 сторонам и углу между ними",
                                                "Расчет по стороне и смежным углам", "Расчет по описанной окружности", "Расчет по вписанной окружности"};
    QStringList *trapezoidList = new QStringList { "", "Расчет по основаниям и высоте", "Расчет по двум диагоналям и углу между ними" };
    QStringList *circleList = new QStringList { "", "Расчет по радиусу"};
    QStringList *sectorList = new QStringList { "", "Расчет по радиусу и углу сектора"};

    QPixmap squareImage(":/Resourses/Resourses/square.png");
    QPixmap rectangleImage(":/Resourses/rectangle.png");
    QPixmap rhombusImage(":/Resourses/rhombus.png");
    QPixmap parallelogramImage(":/Resourses/parallelogram.png");
    QPixmap triangleImage(":/Resourses/triangle.png");
    QPixmap trapezoidListImage(":/Resourses/trapezoidList.png");
    QPixmap circleImage(":/Resourses/circle.png");
    QPixmap sectorImage(":/Resourses/sector.png");

    QWidget *centralWidget = new QWidget(&w);

    QVBoxLayout *Layout1 = new QVBoxLayout;

    QHBoxLayout *figureLayout = new QHBoxLayout;
    QHBoxLayout *formulaLayout = new QHBoxLayout;
    QGridLayout *gridLayout = new QGridLayout;

    QLabel *label1 = new QLabel("Выберите фигуру:");
    QLabel *label2 = new QLabel("Выберите формулу:");

    QComboBox *comboBox1 = new QComboBox;
    QComboBox *comboBox2 = new QComboBox;



    comboBox1->addItems(*figuresList);
    comboBox2->addItems(*squareList);
    comboBox2->setVisible(false);
    label2->setVisible(false);

    QObject::connect(comboBox1, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index) {

        comboBox2->clear();
        comboBox2->setVisible(true);
        label2->setVisible(true);

        switch(index) {
            case 0: {
                comboBox2->setVisible(false);
                label2->setVisible(false);
                break;
            }
            case 1: {
                comboBox2->addItems(*squareList);
                break;
            }
            case 2: {
                comboBox2->addItems(*rectangleList);
                break;
            }
            case 3:{
                comboBox2->addItems(*rhombusList);
                break;
            }
            case 4:{
                comboBox2->addItems(*parallelogramList);
                break;
            }
            case 5:{
                comboBox2->addItems(*triangleList);
                break;
            }
            case 6:{
                comboBox2->addItems(*trapezoidList);
                break;
            }
            case 7:{
                comboBox2->addItems(*circleList);
                break;
            }
            case 8:{
                comboBox2->addItems(*sectorList);
                break;
            }
        }
    });

    QLabel *image = new QLabel;

    QLabel *inputLabel1 = new QLabel;
    QLabel *inputLabel2 = new QLabel;
    QLabel *inputLabel3 = new QLabel;
    QLabel *inputLabel4 = new QLabel;
    QLabel *inputLabel5 = new QLabel("Ответ:");

    QLineEdit *inputLineEdit1 = new QLineEdit;
    QLineEdit *inputLineEdit2 = new QLineEdit;
    QLineEdit *inputLineEdit3 = new QLineEdit;
    QLineEdit *inputLineEdit4 = new QLineEdit;
    QLineEdit *inputLineEdit5 = new QLineEdit;

    SetFalseVisibleWidgets(image, inputLabel1, inputLabel2, inputLabel3, inputLabel4, inputLabel5, inputLineEdit1, inputLineEdit2, inputLineEdit3, inputLineEdit4, inputLineEdit5);


    QObject::connect(comboBox2, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index) {
        switch (comboBox1->currentIndex()) {
            case 0:
            SetFalseVisibleWidgets(image, inputLabel1, inputLabel2, inputLabel3, inputLabel4, inputLabel5, inputLineEdit1, inputLineEdit2, inputLineEdit3, inputLineEdit4, inputLineEdit5);
            break;
        case 1: {
            if (index == 0) break;
            else {
                SetFalseVisibleWidgets(image, inputLabel1, inputLabel2, inputLabel3, inputLabel4, inputLabel5, inputLineEdit1, inputLineEdit2, inputLineEdit3, inputLineEdit4, inputLineEdit5);

                image->setPixmap(squareImage);
                image->setVisible(true);

                if (index == 1) {
                    inputLabel1->setText("Введите сторону: ");
                    inputLineEdit1->setText("Введите число");
                } else if (index == 2) {
                    inputLabel1->setText("Введите диагональ: ");
                }
                inputLabel1->setVisible(true);

                inputLineEdit1->setText("Введите число");
                inputLineEdit1->setVisible(true);
            }
            break;
        }
            case 2:
            break;
            case 3:
            break;
            case 4:
            break;
            case 5:
            break;
            case 6:
            break;
            case 7:
            break;
            case 8:
            break;
            default:
            break;
        }


    });



    gridLayout->addWidget(image, 1, 1);

    gridLayout->addWidget(inputLabel1, 1, 2);
    gridLayout->addWidget(inputLineEdit1, 1, 3);

    gridLayout->addWidget(inputLabel2, 2, 2);
    gridLayout->addWidget(inputLineEdit2, 2, 3);

    gridLayout->addWidget(inputLabel3, 3, 2);
    gridLayout->addWidget(inputLineEdit3, 3, 3);

    gridLayout->addWidget(inputLabel4, 4, 2);
    gridLayout->addWidget(inputLineEdit4, 4, 3);





    figureLayout->addWidget(label1);
    figureLayout->addWidget(comboBox1);
    formulaLayout->addWidget(label2);
    formulaLayout->addWidget(comboBox2);

    Layout1->addItem(figureLayout);
    Layout1->addItem(formulaLayout);
    Layout1->addItem(gridLayout);

    centralWidget->setLayout(Layout1);

    w.setCentralWidget(centralWidget);
    w.show();

    return a.exec();
}

