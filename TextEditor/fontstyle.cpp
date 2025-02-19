#include "fontstyle.h"
#include "ui_fontstyle.h"

FontStyle::FontStyle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FontStyle)
{
    ui->setupUi(this);
}

FontStyle::~FontStyle()
{
    delete ui;
}
