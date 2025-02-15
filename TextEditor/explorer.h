#ifndef EXPLORER_H
#define EXPLORER_H

#include <QDialog>

namespace Ui {
class Explorer;
}

class Explorer : public QDialog
{
    Q_OBJECT

public:
    explicit Explorer(QWidget *parent = nullptr);
    ~Explorer();

private slots:
    void on_upPushBotton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::Explorer *ui;
};

#endif // EXPLORER_H
