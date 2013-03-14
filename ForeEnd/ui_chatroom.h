/********************************************************************************
** Form generated from reading UI file 'chatroom.ui'
**
** Created: Thu Mar 14 17:07:52 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATROOM_H
#define UI_CHATROOM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>
#include <QtWebKit/QWebView>

QT_BEGIN_NAMESPACE

class Ui_chatRoom
{
public:
    QWidget *widget;
    QTextEdit *SendTextEdit;
    QPushButton *SendButton;
    QToolButton *CloseWinBtn;
    QToolButton *MinWinBtn;
    QPushButton *fontBtn;
    QPushButton *cutPhoto;
    QPushButton *faceBtn;
    QPushButton *shakeBtn;
    QPushButton *scrawlBtn;
    QPushButton *senImageBtn;
    QPushButton *messageHistoryBtn;
    QPushButton *blankBtn;
    QWebView *messageListWebView;

    void setupUi(QDialog *chatRoom)
    {
        if (chatRoom->objectName().isEmpty())
            chatRoom->setObjectName(QString::fromUtf8("chatRoom"));
        chatRoom->resize(600, 600);
        chatRoom->setMinimumSize(QSize(600, 600));
        chatRoom->setMaximumSize(QSize(600, 600));
        widget = new QWidget(chatRoom);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 600, 600));
        widget->setMinimumSize(QSize(600, 600));
        widget->setMaximumSize(QSize(600, 600));
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/talk.png);"));
        SendTextEdit = new QTextEdit(widget);
        SendTextEdit->setObjectName(QString::fromUtf8("SendTextEdit"));
        SendTextEdit->setGeometry(QRect(130, 450, 401, 81));
        QFont font;
        font.setPointSize(12);
        SendTextEdit->setFont(font);
        SendTextEdit->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/editTextbg.png);"));
        SendButton = new QPushButton(widget);
        SendButton->setObjectName(QString::fromUtf8("SendButton"));
        SendButton->setGeometry(QRect(450, 540, 81, 23));
        QPalette palette;
        QBrush brush(QColor(170, 170, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        SendButton->setPalette(palette);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        font1.setKerning(true);
        SendButton->setFont(font1);
        SendButton->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(170, 170, 255);\n"
"font: 9pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        CloseWinBtn = new QToolButton(widget);
        CloseWinBtn->setObjectName(QString::fromUtf8("CloseWinBtn"));
        CloseWinBtn->setGeometry(QRect(540, 30, 30, 30));
        QFont font2;
        font2.setPointSize(14);
        CloseWinBtn->setFont(font2);
        CloseWinBtn->setCursor(QCursor(Qt::PointingHandCursor));
        CloseWinBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/closeBtn.png);"));
        MinWinBtn = new QToolButton(widget);
        MinWinBtn->setObjectName(QString::fromUtf8("MinWinBtn"));
        MinWinBtn->setGeometry(QRect(510, 30, 30, 30));
        MinWinBtn->setFont(font2);
        MinWinBtn->setCursor(QCursor(Qt::PointingHandCursor));
        MinWinBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/minBtn.png);"));
        fontBtn = new QPushButton(widget);
        fontBtn->setObjectName(QString::fromUtf8("fontBtn"));
        fontBtn->setGeometry(QRect(130, 420, 27, 27));
        fontBtn->setCursor(QCursor(Qt::PointingHandCursor));
        fontBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/font.png);"));
        cutPhoto = new QPushButton(widget);
        cutPhoto->setObjectName(QString::fromUtf8("cutPhoto"));
        cutPhoto->setGeometry(QRect(211, 420, 27, 27));
        cutPhoto->setCursor(QCursor(Qt::PointingHandCursor));
        cutPhoto->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/cutPhoto.png);"));
        faceBtn = new QPushButton(widget);
        faceBtn->setObjectName(QString::fromUtf8("faceBtn"));
        faceBtn->setGeometry(QRect(157, 420, 27, 27));
        faceBtn->setCursor(QCursor(Qt::PointingHandCursor));
        faceBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/face.png);"));
        shakeBtn = new QPushButton(widget);
        shakeBtn->setObjectName(QString::fromUtf8("shakeBtn"));
        shakeBtn->setGeometry(QRect(184, 420, 27, 27));
        shakeBtn->setCursor(QCursor(Qt::PointingHandCursor));
        shakeBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/shake.png);"));
        scrawlBtn = new QPushButton(widget);
        scrawlBtn->setObjectName(QString::fromUtf8("scrawlBtn"));
        scrawlBtn->setGeometry(QRect(238, 420, 27, 27));
        scrawlBtn->setCursor(QCursor(Qt::PointingHandCursor));
        scrawlBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/scrawl.png);"));
        senImageBtn = new QPushButton(widget);
        senImageBtn->setObjectName(QString::fromUtf8("senImageBtn"));
        senImageBtn->setGeometry(QRect(265, 420, 27, 27));
        senImageBtn->setCursor(QCursor(Qt::PointingHandCursor));
        senImageBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/sendImage.png);"));
        messageHistoryBtn = new QPushButton(widget);
        messageHistoryBtn->setObjectName(QString::fromUtf8("messageHistoryBtn"));
        messageHistoryBtn->setGeometry(QRect(460, 420, 70, 27));
        messageHistoryBtn->setCursor(QCursor(Qt::PointingHandCursor));
        messageHistoryBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/chatHistory.png);"));
        blankBtn = new QPushButton(widget);
        blankBtn->setObjectName(QString::fromUtf8("blankBtn"));
        blankBtn->setGeometry(QRect(292, 420, 168, 27));
        blankBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/chatBlank.png);"));
        messageListWebView = new QWebView(widget);
        messageListWebView->setObjectName(QString::fromUtf8("messageListWebView"));
        messageListWebView->setGeometry(QRect(70, 100, 450, 260));
        messageListWebView->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/content.png);"));
        messageListWebView->setUrl(QUrl(QString::fromUtf8("about:blank")));

        retranslateUi(chatRoom);
        QObject::connect(MinWinBtn, SIGNAL(clicked()), chatRoom, SLOT(showMinimized()));

        QMetaObject::connectSlotsByName(chatRoom);
    } // setupUi

    void retranslateUi(QDialog *chatRoom)
    {
        chatRoom->setWindowTitle(QApplication::translate("chatRoom", "Dialog", 0, QApplication::UnicodeUTF8));
        SendButton->setText(QApplication::translate("chatRoom", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        CloseWinBtn->setText(QString());
        MinWinBtn->setText(QString());
        fontBtn->setText(QString());
        cutPhoto->setText(QString());
        faceBtn->setText(QString());
        shakeBtn->setText(QString());
        scrawlBtn->setText(QString());
        senImageBtn->setText(QString());
        messageHistoryBtn->setText(QString());
        blankBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class chatRoom: public Ui_chatRoom {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATROOM_H
