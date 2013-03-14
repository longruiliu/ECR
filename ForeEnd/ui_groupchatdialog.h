/********************************************************************************
** Form generated from reading UI file 'groupchatdialog.ui'
**
** Created: Thu Mar 14 17:07:52 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPCHATDIALOG_H
#define UI_GROUPCHATDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GroupChatDialog
{
public:
    QWidget *widget;
    QTextEdit *SendMessageText;
    QListWidget *MessageListWidget;
    QListWidget *FriendListWidget;
    QToolButton *CloseWinBtn;
    QToolButton *MinWinBtn;
    QPushButton *SendMessageBtn;
    QPushButton *messageHistoryBtn;
    QPushButton *shakeBtn;
    QPushButton *fontBtn;
    QPushButton *faceBtn;
    QPushButton *cutPhoto;
    QPushButton *senImageBtn;
    QPushButton *blankBtn;
    QPushButton *scrawlBtn;

    void setupUi(QDialog *GroupChatDialog)
    {
        if (GroupChatDialog->objectName().isEmpty())
            GroupChatDialog->setObjectName(QString::fromUtf8("GroupChatDialog"));
        GroupChatDialog->resize(800, 600);
        widget = new QWidget(GroupChatDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 800, 600));
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/groupChatDialogBg.png);"));
        SendMessageText = new QTextEdit(widget);
        SendMessageText->setObjectName(QString::fromUtf8("SendMessageText"));
        SendMessageText->setGeometry(QRect(110, 440, 401, 81));
        SendMessageText->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);"));
        MessageListWidget = new QListWidget(widget);
        MessageListWidget->setObjectName(QString::fromUtf8("MessageListWidget"));
        MessageListWidget->setGeometry(QRect(50, 100, 461, 251));
        MessageListWidget->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);"));
        FriendListWidget = new QListWidget(widget);
        FriendListWidget->setObjectName(QString::fromUtf8("FriendListWidget"));
        FriendListWidget->setGeometry(QRect(570, 90, 201, 471));
        FriendListWidget->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);"));
        CloseWinBtn = new QToolButton(widget);
        CloseWinBtn->setObjectName(QString::fromUtf8("CloseWinBtn"));
        CloseWinBtn->setGeometry(QRect(750, 30, 30, 30));
        QFont font;
        font.setPointSize(14);
        CloseWinBtn->setFont(font);
        CloseWinBtn->setCursor(QCursor(Qt::PointingHandCursor));
        CloseWinBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/closeBtn.png);"));
        MinWinBtn = new QToolButton(widget);
        MinWinBtn->setObjectName(QString::fromUtf8("MinWinBtn"));
        MinWinBtn->setGeometry(QRect(720, 30, 30, 30));
        MinWinBtn->setFont(font);
        MinWinBtn->setCursor(QCursor(Qt::PointingHandCursor));
        MinWinBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/minBtn.png);"));
        SendMessageBtn = new QPushButton(widget);
        SendMessageBtn->setObjectName(QString::fromUtf8("SendMessageBtn"));
        SendMessageBtn->setGeometry(QRect(430, 530, 75, 23));
        messageHistoryBtn = new QPushButton(widget);
        messageHistoryBtn->setObjectName(QString::fromUtf8("messageHistoryBtn"));
        messageHistoryBtn->setGeometry(QRect(440, 410, 70, 27));
        messageHistoryBtn->setCursor(QCursor(Qt::PointingHandCursor));
        messageHistoryBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/chatHistory.png);"));
        shakeBtn = new QPushButton(widget);
        shakeBtn->setObjectName(QString::fromUtf8("shakeBtn"));
        shakeBtn->setGeometry(QRect(164, 410, 27, 27));
        shakeBtn->setCursor(QCursor(Qt::PointingHandCursor));
        shakeBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/shake.png);"));
        fontBtn = new QPushButton(widget);
        fontBtn->setObjectName(QString::fromUtf8("fontBtn"));
        fontBtn->setGeometry(QRect(110, 410, 27, 27));
        fontBtn->setCursor(QCursor(Qt::PointingHandCursor));
        fontBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/font.png);"));
        faceBtn = new QPushButton(widget);
        faceBtn->setObjectName(QString::fromUtf8("faceBtn"));
        faceBtn->setGeometry(QRect(137, 410, 27, 27));
        faceBtn->setCursor(QCursor(Qt::PointingHandCursor));
        faceBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/face.png);"));
        cutPhoto = new QPushButton(widget);
        cutPhoto->setObjectName(QString::fromUtf8("cutPhoto"));
        cutPhoto->setGeometry(QRect(191, 410, 27, 27));
        cutPhoto->setCursor(QCursor(Qt::PointingHandCursor));
        cutPhoto->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/cutPhoto.png);"));
        senImageBtn = new QPushButton(widget);
        senImageBtn->setObjectName(QString::fromUtf8("senImageBtn"));
        senImageBtn->setGeometry(QRect(245, 410, 27, 27));
        senImageBtn->setCursor(QCursor(Qt::PointingHandCursor));
        senImageBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/sendImage.png);"));
        blankBtn = new QPushButton(widget);
        blankBtn->setObjectName(QString::fromUtf8("blankBtn"));
        blankBtn->setGeometry(QRect(272, 410, 168, 27));
        blankBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/chatBlank.png);"));
        scrawlBtn = new QPushButton(widget);
        scrawlBtn->setObjectName(QString::fromUtf8("scrawlBtn"));
        scrawlBtn->setGeometry(QRect(214, 410, 31, 27));
        scrawlBtn->setCursor(QCursor(Qt::PointingHandCursor));
        scrawlBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/btn/scrawl.png);"));

        retranslateUi(GroupChatDialog);
        QObject::connect(MinWinBtn, SIGNAL(clicked()), widget, SLOT(showMinimized()));

        QMetaObject::connectSlotsByName(GroupChatDialog);
    } // setupUi

    void retranslateUi(QDialog *GroupChatDialog)
    {
        GroupChatDialog->setWindowTitle(QApplication::translate("GroupChatDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        CloseWinBtn->setText(QString());
        MinWinBtn->setText(QString());
        SendMessageBtn->setText(QApplication::translate("GroupChatDialog", "\345\217\221\351\200\201", 0, QApplication::UnicodeUTF8));
        messageHistoryBtn->setText(QString());
        shakeBtn->setText(QString());
        fontBtn->setText(QString());
        faceBtn->setText(QString());
        cutPhoto->setText(QString());
        senImageBtn->setText(QString());
        blankBtn->setText(QString());
        scrawlBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GroupChatDialog: public Ui_GroupChatDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPCHATDIALOG_H
