#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>

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
    void on_exit_triggered();

    void on_create_triggered();

    void on_open_triggered();

    void on_save_triggered();

    void on_close_triggered();

    void on_save_as_triggered();

    void closeFile();

    void on_mainTextEdit_textChanged();

    void on_undo_triggered();

    void changeSearchGridVisible(bool value);

    void on_search_triggered();

    void on_replace_triggered();

    void on_closeSearch_clicked();

    void on_search_2_clicked();

    void on_replace_2_clicked();

    void on_replaceAll_clicked();

    void on_copy_triggered();

    void on_paste_triggered();

    void on_clear_triggered();

    void on_toolBarVisibleButton_clicked();

    void on_bold_triggered();

    void on_italic_triggered();

    void on_underlined_triggered();

    void on_color_triggered();

    void on_size_triggered();

    void on_style_triggered();

    void on_fontEdit_triggered();

private:
    Ui::MainWindow *ui;

    void OfferToSave();
    void SaveFile();
    void SaveAs();

    void InFile();

    QString content;
    QString filePath;
    QString currentFileName;
    QList<QString> history;
    QString searchText;
    QString buffer;

    bool isEdit = false;
    bool isNew = false;
    bool isUndo = false;
    short historyIndex = 0;
    int lastSearchPosition = 0;

};

#endif // MAINWINDOW_H
