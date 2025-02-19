#ifndef FONTEDIT_H
#define FONTEDIT_H

#include <QDialog>
#include <QMap>
#include <QTextCharFormat>

namespace Ui {
class FontEdit;
}

class FontEdit : public QDialog
{
    Q_OBJECT

public:
    explicit FontEdit(QWidget *parent = nullptr);
    ~FontEdit();

    void setFormat(QTextCharFormat* currentFormat);
    QTextCharFormat* getFormat();

    static QTextCharFormat *format;

private slots:
    void on_cancelButton_clicked();

    void on_confirmButton_clicked();

    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_spinBox_valueChanged(const QString &arg1);

    void on_boldCheckBox_stateChanged(int arg1);

    void on_italicCheckBox_stateChanged(int arg1);

    void on_underlinedCheckBox_stateChanged(int arg1);

    void on_colorsComboBox_currentIndexChanged(const QString &arg1);

    void on_colorComboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::FontEdit *ui;

    QMap<QString, QColor> colorMap;

    bool editColorComboBox = false;
};

#endif // FONTEDIT_H
