#include <QApplication>
#include <QObject>
#include "src/qt/ui/MainWindow/mainwindow.h"
#include "defines.cpp"


int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
