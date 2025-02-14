#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_triggered();
    
    void on_action_12_triggered();

    void on_exit_triggered();

    void on_create_triggered();

    void on_open_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
