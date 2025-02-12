#include "mainwindow.h"
#include <string>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include "FiguresArea.h"
#include <QMessageBox>

void SetFalseVisibleWidgets(QLabel *image, QLabel *inputLabel1, QLabel *inputLabel2, QLabel *inputLabel3, QLabel *inputLabel4, QLabel *inputLabel5,
                      QLineEdit *inputLineEdit1, QLineEdit *inputLineEdit2, QLineEdit *inputLineEdit3, QLineEdit *inputLineEdit4, QLineEdit *inputLineEdit5, QPushButton *button) {
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

    button->setVisible(false);
}

void SetEmptyText(QLabel *inputLabel1, QLabel *inputLabel2, QLabel *inputLabel3, QLabel *inputLabel4, QLabel *inputLabel5,
                  QLineEdit *inputLineEdit1, QLineEdit *inputLineEdit2, QLineEdit *inputLineEdit3, QLineEdit *inputLineEdit4, QLineEdit *inputLineEdit5) {
    inputLabel1->setText("");
    inputLabel2->setText("");
    inputLabel3->setText("");
    inputLabel4->setText("");
    inputLineEdit1->setText("0");
    inputLineEdit2->setText("0");
    inputLineEdit3->setText("0");
    inputLineEdit4->setText("0");
    inputLineEdit5->setText("0");
}

bool DoubleCheck(QLineEdit *lineEdit) {
    bool is_number;
    lineEdit->text().toDouble(&is_number);

    if (is_number) return true;
    else return false;

}

void ErrorNumberMessage()
{
    QMessageBox::critical(0, "Ошибка", "Во всех полях должны быть числовые значения больше нуля!");
}

void ErrorFigureMessage()
{
    QMessageBox::critical(0, "Ошибка", "Такой фигуры не существует!");
}

void ErrorAngleMessage()
{
    QMessageBox::critical(0, "Ошибка", "Неправильное значение для угла!");
}

bool CheckTriangle(double a, double b, double c) {
    if (a + b <= c) return false;
    if (a + c <= b) return false;
    if (b + c <= a) return false;
    return true;
}

void setLabelAndInput(QLabel* label, QLineEdit* input, const QString& text) {
    label->setText(text);
    label->setVisible(true);
    input->setPlaceholderText("Введите число");
    input->setVisible(true);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    FiguresArea area;

    QStringList *figuresList = new QStringList({ "", "Квадрат", "Прямоугольник", "Параллелограмм", "Ромб", "Треугольник", "Трапеция", "Круг", "Сектор" });
    QStringList *squareList = new QStringList { "", "рассчет одной стороне", "рассчет по диагонали" };
    QStringList *rectangleList = new QStringList { "", "рассчет по двум сторонам", "рассчет по диагоналям и смежному углу" };
    QStringList *rhombusList = new QStringList { "", "рассчет по двум диагоналям", "рассчет по стороне и высоте", "рассчет по сторонам и смежному углу" };
    QStringList *parallelogramList = new QStringList { "", "рассчет по диагоналям и смежному углу", "рассчет по стороне и высоте", "рассчет по сторонам и смежному углу" };
    QStringList *triangleList = new QStringList { "", "рассчет по стороне и высоте", "рассчет по трем сторонам", "рассчет по сторонам и смежному углу",
                                                "рассчет по стороне и смежным углам", "рассчет по описанной окружности", "рассчет по вписанной окружности"};
    QStringList *trapezoidList = new QStringList { "", "рассчет по основаниям и высоте", "рассчет по диагоналям и смежному углу" };
    QStringList *circleList = new QStringList { "", "рассчет по радиусу"};
    QStringList *sectorList = new QStringList { "", "рассчет по радиусу и углу сектора"};

    QPixmap squareImage(":/Resourses/Resourses/square.png");
    QPixmap rectangleImage(":/Resourses/Resourses/rectangle.png");
    QPixmap rhombusImage(":/Resourses/Resourses/rhombus.png");
    QPixmap parallelogramImage(":/Resourses/Resourses/parallelogram.png");
    QPixmap triangleImage(":/Resourses/Resourses/triangle.png");
    QPixmap trapezoidImage(":/Resourses/Resourses/trapezoid.png");
    QPixmap circleImage(":/Resourses/Resourses/circle.png");
    QPixmap sectorImage(":/Resourses/Resourses/sector.png");

    QWidget *centralWidget = new QWidget(&w);

    QVBoxLayout *Layout1 = new QVBoxLayout;

    Layout1->setAlignment(Qt::AlignTop);

    QHBoxLayout *figureLayout = new QHBoxLayout;
    QHBoxLayout *formulaLayout = new QHBoxLayout;
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setSpacing(5);
    gridLayout->setColumnMinimumWidth(3, 100);

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
                comboBox2->addItems(*parallelogramList);
                break;
            }
            case 4:{                
                comboBox2->addItems(*rhombusList);
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
    image->setMargin(10);

    QLabel *inputLabel1 = new QLabel;
    QLabel *inputLabel2 = new QLabel;
    QLabel *inputLabel3 = new QLabel;
    QLabel *inputLabel4 = new QLabel;
    QLabel *inputLabel5 = new QLabel();

    QLineEdit *inputLineEdit1 = new QLineEdit;
    QLineEdit *inputLineEdit2 = new QLineEdit;
    QLineEdit *inputLineEdit3 = new QLineEdit;
    QLineEdit *inputLineEdit4 = new QLineEdit;
    QLineEdit *inputLineEdit5 = new QLineEdit;

    inputLabel5->setText("Ответ:");
    QPushButton *button = new QPushButton;
    button->setText("Рассчитать");

    inputLineEdit5->setReadOnly(true);

    SetFalseVisibleWidgets(image, inputLabel1, inputLabel2, inputLabel3, inputLabel4, inputLabel5, inputLineEdit1, inputLineEdit2, inputLineEdit3, inputLineEdit4, inputLineEdit5, button);

    QObject::connect(comboBox2, QOverload<int>::of(&QComboBox::currentIndexChanged), [&](int index) {
        SetFalseVisibleWidgets(image, inputLabel1, inputLabel2, inputLabel3, inputLabel4, inputLabel5,
                               inputLineEdit1, inputLineEdit2, inputLineEdit3, inputLineEdit4, inputLineEdit5, button);
        SetEmptyText(inputLabel1, inputLabel2, inputLabel3, inputLabel4, inputLabel5,
                     inputLineEdit1, inputLineEdit2, inputLineEdit3, inputLineEdit4, inputLineEdit5);

        if (index == -1 || index == 0) return;

        switch (comboBox1->currentIndex()) {
            case 1:
                image->setPixmap(squareImage);
                break;
            case 2:
                image->setPixmap(rectangleImage);
                break;
            case 3:
                image->setPixmap(parallelogramImage);
                break;
            case 4:
                image->setPixmap(rhombusImage);
                break;
            case 5:
                image->setPixmap(triangleImage);
                break;
            case 6:
                image->setPixmap(trapezoidImage);
                break;
            case 7:
                image->setPixmap(circleImage);
                break;
            case 8:
                image->setPixmap(sectorImage);
                break;
            default:
                return;
        }

        image->setVisible(true);
        button->setVisible(true);
        inputLabel5->setVisible(true);
        inputLineEdit5->setVisible(true);

        if (comboBox1->currentIndex() == 1) {
            setLabelAndInput(inputLabel1, inputLineEdit1, index == 1 ? "Введите сторону: " : "Введите диагональ: ");
        } else if (comboBox1->currentIndex() == 2) {
            if (index == 1) {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите первую сторону: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите вторую сторону: ");
            } else {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите диагональ: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите угол между диагоналями: ");
            }
        } else if (comboBox1->currentIndex() == 3) {
            if (index == 1) {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите первую диагональ: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите вторую диагональ: ");
                setLabelAndInput(inputLabel3, inputLineEdit3, "Введите угол между диагоналями: ");
            } else if (index == 2) {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите основание: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите высоту: ");
            } else {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите первую сторону: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите вторую сторону: ");
                setLabelAndInput(inputLabel3, inputLineEdit3, "Введите угол между сторонами: ");
            }
        } else if (comboBox1->currentIndex() == 4) {
            if (index == 1) {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите первую диагональ: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите вторую диагональ: ");
            } else if (index == 2) {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите сторону: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите высоту: ");
            } else if (index == 3) {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите сторону: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите угол: ");
            }
        } else if (comboBox1->currentIndex() == 5) {
            if (index == 1) {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите сторону: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите высоту: ");
            } else if (index == 2) {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите первую сторону: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите вторую сторону: ");
                setLabelAndInput(inputLabel3, inputLineEdit3, "Введите третью сторону: ");
            } else if (index == 3) {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите первую сторону: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите вторую сторону: ");
                setLabelAndInput(inputLabel3, inputLineEdit3, "Введите смежный угол: ");
            } else if (index == 4) {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите сторону: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите первый смежный угол: ");
                setLabelAndInput(inputLabel3, inputLineEdit3, "Введите второй смежный угол: ");
            } else if (index == 5) {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите первую сторону: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите вторую сторону: ");
                setLabelAndInput(inputLabel3, inputLineEdit3, "Введите третью сторону: ");
                setLabelAndInput(inputLabel4, inputLineEdit4, "Введите радиус описанной окружности: ");
            } else if (index == 6) {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите первую сторону: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите вторую сторону: ");
                setLabelAndInput(inputLabel3, inputLineEdit3, "Введите третью сторону: ");
                setLabelAndInput(inputLabel4, inputLineEdit4, "Введите радиус вписанной окружности: ");
            }
        } else if (comboBox1->currentIndex() == 6) {
            if (index == 1) {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите первое основание: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите второе основание: ");
                setLabelAndInput(inputLabel3, inputLineEdit3, "Введите высоту: ");
            } else if (index == 2) {
                setLabelAndInput(inputLabel1, inputLineEdit1, "Введите первую диагональ: ");
                setLabelAndInput(inputLabel2, inputLineEdit2, "Введите вторую диагональ: ");
                setLabelAndInput(inputLabel3, inputLineEdit3, "Введите смежный угол: ");
            }
        } else if (comboBox1->currentIndex() == 7) {
            setLabelAndInput(inputLabel1, inputLineEdit1, "Введите радиус: ");
        } else if (comboBox1->currentIndex() == 8) {
            setLabelAndInput(inputLabel1, inputLineEdit1, "Введите радиус: ");
            setLabelAndInput(inputLabel2, inputLineEdit2, "Введите угол сектора: ");
        }
    });



    QObject::connect(button, &QPushButton::clicked, [&]() {

        int index = comboBox2->currentIndex();

        if (DoubleCheck(inputLineEdit1) &&  DoubleCheck(inputLineEdit2) && DoubleCheck(inputLineEdit2) && DoubleCheck(inputLineEdit2) &&
                inputLineEdit1->text().toDouble() > 0 && inputLineEdit1->text().toDouble() > 0 &&
                inputLineEdit1->text().toDouble() > 0 &&inputLineEdit1->text().toDouble() > 0) {

            switch (comboBox1->currentIndex()) {
                case 0:
                    break;
                case 1:
                    if (index == -1 || index == 0) break;
                    else {
                        if (index == 1) {
                            double a = inputLineEdit1->text().toDouble();
                            inputLineEdit5->setText(QString::number(area.SquareAreaSide(a)));
                        } else if (index == 2) {
                            double d = inputLineEdit1->text().toDouble();
                            inputLineEdit5->setText(QString::number(area.SquareAreaDiagonal(d)));
                        }
                    }
                    break;
                case 2:
                    if (index == -1 || index == 0) break;
                    else {
                        if (index == 1) {
                            double a = inputLineEdit1->text().toDouble();
                            double b = inputLineEdit2->text().toDouble();

                            inputLineEdit5->setText(QString::number(area.RectangleAreaSides(a, b)));
                        } else if (index == 2) {
                            double d = inputLineEdit1->text().toDouble();
                            double angle = inputLineEdit2->text().toDouble();
                            if (angle <= 0 || angle >= 180) {
                                ErrorAngleMessage();
                                return;
                            }
                            inputLineEdit5->setText(QString::number(area.RectangleAreaDiagonal(d, angle)));
                        }
                    }
                    break;
                case 3:
                    if (index == -1 || index == 0) break;
                    else {
                        if (index == 1) {
                            double d1 = inputLineEdit1->text().toDouble();
                            double d2 = inputLineEdit2->text().toDouble();
                            double angle = inputLineEdit3->text().toDouble();
                            if (angle <= 0 || angle >= 180) {
                                ErrorAngleMessage();
                                return;
                            }
                            inputLineEdit5->setText(QString::number(area.ParallelogramAreaDiagonals(d1, d2, angle)));
                        } else if (index == 2) {
                            double a = inputLineEdit1->text().toDouble();
                            double b = inputLineEdit2->text().toDouble();

                            inputLineEdit5->setText(QString::number(area.ParallelogramAreaHeight(a, b)));
                        } else if (index == 3) {
                            double a = inputLineEdit1->text().toDouble();
                            double b = inputLineEdit2->text().toDouble();
                            double angle = inputLineEdit3->text().toDouble();
                            if (angle <= 0 || angle >= 180) {
                                ErrorAngleMessage();
                                return;
                            }
                            inputLineEdit5->setText(QString::number(area.ParallelogramAreaAdjacentSides(a, b, angle)));
                        }
                    }
                    break;
                case 4:
                    if (index == -1 || index == 0) break;
                    else {
                        if (index == 1) {
                            double d1 = inputLineEdit1->text().toDouble();
                            double d2 = inputLineEdit2->text().toDouble();

                            inputLineEdit5->setText(QString::number(area.RhombusAreaDiagonals(d1, d2)));
                        } else if (index == 2) {
                            double a = inputLineEdit1->text().toDouble();
                            double h = inputLineEdit2->text().toDouble();

                            inputLineEdit5->setText(QString::number(area.RhombusAreaHeight(a, h)));
                        } else if (index == 3) {
                            double a = inputLineEdit1->text().toDouble();
                            double angle = inputLineEdit2->text().toDouble();
                            if (angle <= 0 || angle >= 180) {
                                ErrorAngleMessage();
                                return;
                            }
                            inputLineEdit5->setText(QString::number(area.RhombusAreaSides(a, angle)));
                        }
                  }
                    break;
                case 5:
                    if (index == -1 || index == 0) break;
                    else {
                        if (index == 1) {
                            double a = inputLineEdit1->text().toDouble();
                            double h = inputLineEdit2->text().toDouble();
                            inputLineEdit5->setText(QString::number(area.TriangleAreaHeight(a, h)));
                        } else if (index == 2) {
                            double a = inputLineEdit1->text().toDouble();
                            double b = inputLineEdit2->text().toDouble();
                            double c = inputLineEdit3->text().toDouble();

                            if (!CheckTriangle(a, b, c)) {
                                ErrorFigureMessage();
                                return;
                            }

                            inputLineEdit5->setText(QString::number(area.TriangleAreaThreeSides(a, b, c)));
                        } else if (index == 3) {
                            double a = inputLineEdit1->text().toDouble();
                            double b = inputLineEdit2->text().toDouble();
                            double angle = inputLineEdit3->text().toDouble();
                            if (angle <= 0 || angle >= 180) {
                                ErrorAngleMessage();
                                return;
                            }
                            inputLineEdit5->setText(QString::number(area.TriangleAreaAdjacentSides(a, b, angle)));
                        } else if (index == 4) {
                            double a = inputLineEdit1->text().toDouble();
                            double angle1 = inputLineEdit2->text().toDouble();
                            double angle2 = inputLineEdit3->text().toDouble();
                            if (angle1 <= 0 || angle1 >= 180 || angle2 <=0 || angle2 >=180 ) {
                                ErrorAngleMessage();
                                return;
                            }
                            inputLineEdit5->setText(QString::number(area.TriangleAreaTwoAngles(a, angle1, angle2)));
                        } else if (index == 5) {
                            double a = inputLineEdit1->text().toDouble();
                            double b = inputLineEdit2->text().toDouble();
                            double c = inputLineEdit3->text().toDouble();
                            double r = inputLineEdit4->text().toDouble();
                            if (!CheckTriangle(a, b, c)) {
                                ErrorFigureMessage();
                                return;
                            }
                            inputLineEdit5->setText(QString::number(area.TriangleAreaCircumscribedCircle(a, b, c, r)));
                        } else if (index == 6) {
                            double a = inputLineEdit1->text().toDouble();
                            double b = inputLineEdit2->text().toDouble();
                            double c = inputLineEdit3->text().toDouble();
                            double r = inputLineEdit4->text().toDouble();
                            if (!CheckTriangle(a, b, c)) {
                                ErrorFigureMessage();
                                return;
                            }
                            inputLineEdit5->setText(QString::number(area.TriangleAreaInscribedCircle(a, b, c, r)));
                        }
                    }
                    break;
                case 6:
                    if (index == -1 || index == 0) break;
                    else {
                        if (index == 1) {
                            double a = inputLineEdit1->text().toDouble();
                            double b = inputLineEdit2->text().toDouble();
                            double h = inputLineEdit3->text().toDouble();

                            inputLineEdit5->setText(QString::number(area.TrapezoidAreaHeight(a, b, h)));
                        } else if (index == 2) {
                            double d1 = inputLineEdit1->text().toDouble();
                            double d2= inputLineEdit2->text().toDouble();
                            double angle = inputLineEdit3->text().toDouble();
                            if (angle <= 0 || angle >= 180) {
                                ErrorAngleMessage();
                                return;
                            }
                            inputLineEdit5->setText(QString::number(area.TrapezoidAreaDiagonal(d1, d2, angle)));
                        }
                    }
                    break;
                case 7:
                    if (index == -1 || index == 0) break;
                    else {
                       if (index == 1) {
                           double r = inputLineEdit1->text().toDouble();
                           inputLineEdit5->setText(QString::number(area.CircleArea(r)));
                       }
                    }
                    break;
                case 8:
                    if (index == -1 || index == 0) break;
                    else {
                       if (index == 1) {
                           double r = inputLineEdit1->text().toDouble();
                           double angle = inputLineEdit2->text().toDouble();
                           if (angle < 0 || angle > 360) {
                               ErrorAngleMessage();
                               return;
                           }
                           inputLineEdit5->setText(QString::number(area.SectorArea(r, angle)));
                       }
                    }
                    break;
                default:
                    break;

            }
        }
        else ErrorNumberMessage();
    });

    gridLayout->setMargin(5);

    gridLayout->addWidget(image, 0, 1, 6, 1);

    gridLayout->addWidget(inputLabel1, 0, 2);
    gridLayout->addWidget(inputLineEdit1, 0, 3);

    gridLayout->addWidget(inputLabel2, 1, 2);
    gridLayout->addWidget(inputLineEdit2, 1, 3);

    gridLayout->addWidget(inputLabel3, 2, 2);
    gridLayout->addWidget(inputLineEdit3, 2, 3);

    gridLayout->addWidget(inputLabel4, 3, 2);
    gridLayout->addWidget(inputLineEdit4, 3, 3);

    gridLayout->addWidget(button, 4, 2, 1, 2);

    gridLayout->addWidget(inputLabel5, 5, 2);
    gridLayout->addWidget(inputLineEdit5, 5, 3);

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

