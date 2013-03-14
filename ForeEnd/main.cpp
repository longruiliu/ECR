#include <QtGui/QApplication>
#include "chatroom.h"
#include "chatroompanel.h"
#include "logindialog.h"
#include "groupchatdialog.h"
#include "messagelistener.h"
#include "networkqueue.h"

int main(int argc, char *argv[])
{

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication::setStyle("cleanlooks");
    QApplication a(argc, argv);

    /*don't run it cause we don't have IP and port*/
    networkQueue nq;
    messageListener ml;

    loginDialog ld;
    ld.show();

    return a.exec();
}
