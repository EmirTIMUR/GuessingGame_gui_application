#include "mainwindow.h"
#include <QApplication>
#include<cstdlib> // for rand() and srand()
#include<ctime> // for time()

int main(int argc, char *argv[])
{
    srand(static_cast<unsigned int> (time(nullptr)));

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
