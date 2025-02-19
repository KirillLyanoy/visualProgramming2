#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "explorer.h"
#include "fontedit.h"
#include "filename.h"
#include <QFileInfo>
#include <QStringListModel>
#include <QTextStream>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
        ui->setupUi(this);

        changeSearchGridVisible(false);

        QLocale::setDefault(QLocale(QLocale::Russian, QLocale::Russia));
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

        ui->mainTextEdit->setVisible(false);
    }

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeSearchGridVisible(bool value)
{
    if (!isEdit && value) return;

    ui->searchLabel->setVisible(value);
    ui->replaceLabel->setVisible(value);
    ui->searchLineEdit->setVisible(value);
    ui->replaceLineEdit->setVisible(value);
    ui->search_2->setVisible(value);
    ui->replace_2->setVisible(value);
    ui->replaceAll->setVisible(value);
    ui->closeSearch->setVisible(value);
}

void MainWindow::closeFile()
{
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("Сохранить документ перед закрытием?");

    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    QPushButton *customButton = msgBox.addButton("Отмена", QMessageBox::ActionRole);

    msgBox.setButtonText(QMessageBox::Yes, "Да");
    msgBox.setButtonText(QMessageBox::No, "Нет");

    int ret = msgBox.exec();

    if (ret == QMessageBox::Yes)
    {
        if (isNew)
            SaveAs();
        else
            SaveFile();

        isEdit = false;
        isNew = false;
        ui->mainTextEdit->setText("");
        ui->mainTextEdit->setVisible(false);
    }
    else if (ret == QMessageBox::No)
    {
        isEdit = false;
        isNew = false;
        ui->mainTextEdit->setText("");
        ui->mainTextEdit->setVisible(false);

    }
    else return;
}

void MainWindow::SaveAs()
{
    Explorer explorer;

    explorer.setModal(true);

    explorer.setAction(Explorer::save);

    if (explorer.exec() == QDialog::Accepted)
    {
        FileName fileName;
        fileName.setModal(true);

        if (fileName.exec() == QDialog::Accepted)
        {
           filePath = explorer.getPath();

           if (filePath.lastIndexOf("/"))
                currentFileName = filePath + fileName.getName();
           else
                currentFileName = filePath + "/" + fileName.getName();

           QFile file(currentFileName);

           if (file.open(QIODevice::WriteOnly | QIODevice::Text))
           {
              QTextStream out(&file);
              out << content;
              file.close();
              QMessageBox::information(0, "Запись", "Файл успешно сохранён");
              isNew = false;
           }
           else
           {
               QMessageBox::critical(0, "Ошибка", "Ошибка при записи файла");
           }
        }
    }
}

void MainWindow::SaveFile()
{
    if (isEdit)
    {
        QFile file(currentFileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
           QTextStream out(&file);
           out << content;
           file.close();
           QMessageBox::information(0, "Запись", "Файл успешно сохранён");
        }
        else
        {
            QMessageBox::critical(0, "Ошибка", "Ошибка при записи файла");
        }
    }
}


void MainWindow::on_create_triggered()
{
    if (!isEdit)
    {
        ui->mainTextEdit->setVisible(true);
        isEdit = true;
        isNew = true;
    }
    else
    {
        QMessageBox::information(0, "Предупреждение", "Чтобы создать новый документ необходимо закрыть текущий документ.");
    }
}

void MainWindow::on_exit_triggered()
{
    if (isEdit)
    {
        closeFile();
    }
    this->close();
}

void MainWindow::on_open_triggered()
{
    if (!isEdit)
    {
        Explorer explorer;

        explorer.setModal(true);

        explorer.setAction(Explorer::open);

        if (explorer.exec() == QDialog::Accepted)
        {

            filePath = explorer.getPath();


            QFile file(filePath);

            if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            {
                QMessageBox::critical(0, "Ошибка", "Ошибка при открытии файла");
                return;
            }

            currentFileName = filePath;

            QTextStream in(&file);

            content = in.readAll();
            file.close();

            isEdit = true;
            ui->mainTextEdit->setVisible(true);
            ui->mainTextEdit->setText(content);
        }
    }
    else
    {
        QMessageBox::information(0, "Предупреждение", "Чтобы открыть новый документ необходимо закрыть текущий документ.");
    }
}

void MainWindow::on_save_triggered()
{
    if (isEdit)
    {
        content = ui->mainTextEdit->toPlainText();

    if (isNew)
        SaveAs();
    else
        SaveFile();
    }
}

void MainWindow::on_close_triggered()
{
    if (isEdit)
    {
        closeFile();
    }
}

void MainWindow::on_save_as_triggered()
{
    if (isEdit)
    {
        content = ui->mainTextEdit->toPlainText();
        SaveAs();

        isNew = false;
    }
}

void MainWindow::on_mainTextEdit_textChanged()
{
    if (!isUndo) {
        if (isNew && history.empty())
        {
            history.append("");
            historyIndex++;
        }

        if (historyIndex != history.length())
            history = history.mid(0, historyIndex);

        if (history.length() < 10)
        {
            history.append(ui->mainTextEdit->toPlainText());
            historyIndex = history.length();
        }
        else
        {
            history.removeAt(0);
            history.append(ui->mainTextEdit->toPlainText());
        }
    }

    content = ui->mainTextEdit->toPlainText();
}

void MainWindow::on_undo_triggered()
{
    isUndo = true;

    QTextCursor cursor = ui->mainTextEdit->textCursor();

    if (historyIndex >= 2)
    {
        ui->mainTextEdit->setText(history.at(historyIndex - 2));
        historyIndex--;
    }

    ui->mainTextEdit->setTextCursor(cursor);

    isUndo = false;
}

void MainWindow::on_search_triggered()
{
    changeSearchGridVisible(true);
}

void MainWindow::on_replace_triggered()
{
    changeSearchGridVisible(true);
}

void MainWindow::on_closeSearch_clicked()
{
    changeSearchGridVisible(false);
    ui->searchLineEdit->setText("");
    ui->replaceLineEdit->setText("");
}

void MainWindow::on_search_2_clicked()
{
    QTextCursor cursor = ui->mainTextEdit->textCursor();
    QString searchTerm = ui->searchLineEdit->text();

    lastSearchPosition = content.indexOf(searchTerm, lastSearchPosition);

    if (lastSearchPosition != -1) {

        cursor.setPosition(lastSearchPosition);
        cursor.movePosition(QTextCursor::NextCharacter, QTextCursor::KeepAnchor, searchTerm.length());
        ui->mainTextEdit->setTextCursor(cursor);

        lastSearchPosition += searchTerm.length();
    }
}

void MainWindow::on_replace_2_clicked()
{
    int index = content.indexOf(ui->searchLineEdit->text());
    content.replace(index, ui->searchLineEdit->text().length(), ui->replaceLineEdit->text());

    ui->mainTextEdit->setText(content);
}

void MainWindow::on_replaceAll_clicked()
{
    content.replace(ui->searchLineEdit->text(), ui->replaceLineEdit->text());
    ui->mainTextEdit->setText(content);
}

void MainWindow::on_copy_triggered()
{
    QTextCursor cursor = ui->mainTextEdit->textCursor();

    if (cursor.hasSelection())
        buffer = cursor.selectedText();
}

void MainWindow::on_paste_triggered()
{
    QTextCursor cursor = ui->mainTextEdit->textCursor();

    cursor.insertText(buffer);

    ui->mainTextEdit->setTextCursor(cursor);
}

void MainWindow::on_clear_triggered()
{
    content = "";
    ui->mainTextEdit->setText(content);
}

void MainWindow::on_fontEdit_triggered()
{
    FontEdit fontEdit;
    fontEdit.setModal(true);

    QTextCursor cursor = ui->mainTextEdit->textCursor();
    QTextCharFormat format = cursor.charFormat();

    fontEdit.setFormat(&format);

    if (fontEdit.exec() == QDialog::Accepted)
    {
        QTextCharFormat* currentFormat = fontEdit.getFormat();

        cursor.mergeCharFormat(*currentFormat);
    }
}
