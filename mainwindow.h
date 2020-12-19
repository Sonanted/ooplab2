#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "prefixtree.h"
#include <QMainWindow>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void refreshTable();

    string keyFromStr();

private slots:
    void on_addButton_clicked();

    void on_checkButton_clicked();

    void on_DeleteButton_clicked();

    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_list_itemClicked();

    void on_keyLineEdit_textChanged();

private:
    Ui::MainWindow *ui;
    PrefixTree<string, string> tree;
};

#endif // MAINWINDOW_H
