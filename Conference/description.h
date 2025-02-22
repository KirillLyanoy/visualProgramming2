#ifndef DESCRIPTION_H
#define DESCRIPTION_H

#include <QDialog>
#include <QTime>

namespace Ui {
class description;
}

class description : public QDialog
{
    Q_OBJECT

public:
    explicit description(QWidget *parent = nullptr);
    ~description();

    void SetName(QString name);
    void SetShortDescription(QString shortDescription);
    void SetOrginizer(QString organizer);
    void SetDuration(QTime time);
    bool IsEdited();

    QString GetName();
    QString GetShortDescription();
    QString GetOrginizer();
    QTime GetDuration();



private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::description *ui;

    void ChangeReadOnly(bool value);

    void UpdateView();

    bool isEdited;
    QString name;
    QString shortDescription;
    QString organizer;
    QTime duration;

};

#endif // DESCRIPTION_H
