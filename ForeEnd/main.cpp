#include <QtGui/QApplication>
#include "chatroom.h"
#include "chatroompanel.h"
#include "logindialog.h"
#include "groupchatdialog.h"

int main(int argc, char *argv[])
{

    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));

    QApplication::setStyle("cleanlooks");
    QApplication a(argc, argv);


    loginDialog ld;
    ld.show();


    return a.exec();
}
