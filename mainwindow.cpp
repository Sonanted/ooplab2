#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->checkButton->setEnabled(false);
    ui->DeleteButton->setEnabled(false);
    ui->saveButton->setEnabled(false);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addButton_clicked() {
    string key = ui->keyLineEdit->text().toStdString();
    string value = ui->valueLineEdit->text().toStdString();
    tree.addChild(key, value);
    refreshTable();
    ui->checkButton->setEnabled(true);
    ui->saveButton->setEnabled(true);
}

void MainWindow::on_checkButton_clicked() {
   string key = ui->keyLineEdit->text().toStdString();
   QString qkey = QString::fromStdString(key);
    if (tree.isKeyInTree(key)) {
        ui->keyStatus->setText(qkey + " is in trie");
    }
    else {
        ui->keyStatus->setText(qkey + " is not in trie");
    }
}

void MainWindow::on_DeleteButton_clicked() {
    string key = keyFromStr();
    tree.deleteChild(key);
    refreshTable();
    ui->list->setCurrentRow(-1);
    ui->DeleteButton->setEnabled(false);
    if (tree.getValueCount() == 0) {
        ui->saveButton->setEnabled(false);
    }
}

void MainWindow::on_saveButton_clicked() {
    if (tree.getValueCount() != 0) {
        QString filename = QFileDialog::getSaveFileName(this,
                           tr("Save menu to txt"), "",
                           tr("Text files (*.txt)"));
        if (!filename.isEmpty()) {
            tree.saveTree(filename.toStdString());
        }
    }
}

void MainWindow::on_loadButton_clicked() {
    QString filename = QFileDialog::getOpenFileName(this,
                       tr("Open menu from txt"), "", tr("Text files (*.txt)"));
    if (!filename.isEmpty()) {
        tree.loadTree(filename.toStdString());
    }
    refreshTable();
}

void MainWindow::refreshTable() {
    ui->list->clear();
    vector<string> keys = tree.getKeys();
    for (auto key : keys) {
        QString qkey = QString::fromStdString(key);
        QString qvalue = QString::fromStdString(tree[key]);
        ui->list->addItem(qkey + ": " + qvalue);
    }
}

string MainWindow::keyFromStr() {
    int index = ui->list->currentRow();
    string key = ui->list->takeItem(index)->text().toStdString();
    index = key.find(":");
    key = key.substr(0, index);
    return key;
}

void MainWindow::on_list_itemClicked() {
    ui->DeleteButton->setEnabled(true);
}

void MainWindow::on_keyLineEdit_textChanged() {
    ui->checkButton->setEnabled(true);
    if (ui->keyLineEdit->text() == "") {
        ui->checkButton->setEnabled(false);
    }
}
