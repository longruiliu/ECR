#include <QtGui/QApplication>
#include "chatroom.h"
#include "chatroompanel.h"
#include "logindialog.h"
#include "groupchatdialog.h"
#include "messagelistener.h"
#include "networkqueue.h"
#include <QThread>


networkQueue nq;
messageListener ml;

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication::setStyle("cleanlooks");
    QApplication a(argc, argv);

    nq.start();
    ml.start();
    loginDialog ld;
    ld.show();

    return a.exec();
}
