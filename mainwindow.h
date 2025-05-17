#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <bits/stdc++.h>
#include <QFileDialog>
#include <QStandardPaths>
#include <openssl/rand.h>
#include <openssl/evp.h>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class FileCrypt;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_browseBotten_clicked();

    void on_pushButton_clicked();

private:
    Ui::FileCrypt *ui;
};
#endif // MAINWINDOW_H
