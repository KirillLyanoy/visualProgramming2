#ifndef EXPLORER_H
#define EXPLORER_H

#include <QDialog>
#include <QFileSystemModel>

namespace Ui {
class Explorer;
}

class Explorer : public QDialog
{
    Q_OBJECT

public:

    explicit Explorer(QWidget *parent = nullptr);
    ~Explorer();

    enum Actions
    {
        open = 1,
        save = 2
    };

    void setAction(Actions action);

    QString getPath();

private slots:
    void on_upPushBotton_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_listView_doubleClicked(const QModelIndex &index);

    void on_cancelPushButton_clicked();

    void on_confirmPushButton_clicked();

    void Open(QFileInfo current, QString path);

    bool TxtFileCheck(QFileInfo current);

private:
    Ui::Explorer *ui;


    QList<QString> drivesList;
    QString currentPath;
    QFileSystemModel *fileSystemModel;
    Actions currentAction;

};

#endif // EXPLORER_H
