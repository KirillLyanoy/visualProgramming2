#include "fontedit.h"
#include "ui_fontedit.h"
#include <QTextCharFormat>
#include <QDebug>
QTextCharFormat *FontEdit::format;

FontEdit::FontEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontEdit)
{
    ui->setupUi(this);

    FontEdit::colorMap.insert("Чёрный", Qt::black);
    FontEdit::colorMap.insert("Красный", Qt::red);
    FontEdit::colorMap.insert("Зелёный", Qt::green);
    FontEdit::colorMap.insert("Синий", Qt::blue);
    FontEdit::colorMap.insert("Жёлтый", Qt::yellow);
    FontEdit::colorMap.insert("Белый", Qt::white);
    FontEdit::colorMap.insert("Серый", Qt::gray);
    FontEdit::colorMap.insert("Голубой", Qt::cyan);
    FontEdit::colorMap.insert("Пурпурный", Qt::magenta);

    if (format == nullptr)
        format = new QTextCharFormat();

    editColorComboBox = true;
    for (auto it = colorMap.begin(); it != colorMap.end(); ++it)
    {
        ui->colorComboBox->addItem(it.key());
    }
    editColorComboBox = false;

    ui->fontComboBox->setCurrentFont(FontEdit::format->font());
    ui->spinBox->setValue(FontEdit::format->font().pointSize());

    QString colorName;
    for (auto it = colorMap.begin(); it != colorMap.end(); ++it)
    {
        if (FontEdit::format->foreground().color()  == it.value())
        {
            colorName = it.key();
            break;
        }
    }

    int index = ui->colorComboBox->findText(colorName);
    if (index != -1)
        ui->colorComboBox->setCurrentIndex(index);

    if (FontEdit::format->fontWeight() == QFont::Bold)
        ui->boldCheckBox->setChecked(true);
    else
        ui->boldCheckBox->setChecked(false);
    ui->italicCheckBox->setChecked(FontEdit::format->fontItalic());
    ui->underlinedCheckBox->setChecked(FontEdit::format->fontUnderline());
}

QTextCharFormat* FontEdit::getFormat()
{
    if (FontEdit::format == nullptr)
        FontEdit::format = new QTextCharFormat();

    return FontEdit::format;
}

void FontEdit::setFormat(QTextCharFormat* currentFormat)
{
    if (FontEdit::format == nullptr)
        FontEdit::format = new QTextCharFormat();

    FontEdit::format->setFont(currentFormat->font());
    FontEdit::format->setFontWeight(currentFormat->fontWeight());
    FontEdit::format->setFontItalic(currentFormat->fontItalic());
    FontEdit::format->setFontUnderline(currentFormat->fontUnderline());
    FontEdit::format->setForeground(currentFormat->foreground());
}

FontEdit::~FontEdit()
{
    delete ui;
}

void FontEdit::on_cancelButton_clicked()
{
    this->close();
}

void FontEdit::on_confirmButton_clicked()
{
    this->accept();
}


void FontEdit::on_fontComboBox_currentFontChanged(const QFont &f)
{
    FontEdit::format->setFont(f);
}

void FontEdit::on_spinBox_valueChanged(const QString &arg1)
{
    QFont font = FontEdit::format->font();
    font.setPointSize(arg1.toInt());
    FontEdit::format->setFont(font);
}

void FontEdit::on_boldCheckBox_stateChanged(int arg1)
{
    if (ui->boldCheckBox->isChecked())
        FontEdit::format->setFontWeight(QFont::Bold);
    else
        FontEdit::format->setFontWeight(QFont::Normal);
}

void FontEdit::on_italicCheckBox_stateChanged(int arg1)
{
    FontEdit::format->setFontItalic(ui->italicCheckBox->isChecked());
}

void FontEdit::on_underlinedCheckBox_stateChanged(int arg1)
{
    FontEdit::format->setFontUnderline(ui->underlinedCheckBox->isChecked());
}

void FontEdit::on_colorComboBox_currentIndexChanged(const QString &arg1)
{
    if (!editColorComboBox) FontEdit::format->setForeground(colorMap.value(arg1));
}
