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

    networkQueue nq;
    messageListener ml;
    nq.start();
    ml.start();

    loginDialog ld;
    ld.nq = &nq;
    ld.ml = &ml;

    ld.show();

    return a.exec();
}
