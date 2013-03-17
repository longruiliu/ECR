#include <QtGui/QApplication>
#include "managerwindow.h"
#include <QTextCodec>
#include <cstdlib>
#include <ctime>
int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QApplication a(argc, argv);
    managerWindow w;
    w.show();

    srand(time(NULL));
    return a.exec();
}
