#include "mainwindow.h"
#include <openssl/aes.h>
#include <QApplication>
#include <windows.h>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
