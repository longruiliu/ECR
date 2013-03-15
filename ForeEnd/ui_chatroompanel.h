/********************************************************************************
** Form generated from reading UI file 'chatroompanel.ui'
**
** Created: Thu Mar 14 17:07:52 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATROOMPANEL_H
#define UI_CHATROOMPANEL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChatRoomPanel
{
public:
    QWidget *widget;
    QTabWidget *tabWidget;
    QToolButton *CloseWinBtn;
    QPushButton *headerImage;
    QToolButton *MiniButton;
    QLineEdit *nameLineEdit;
    QFrame *line;

    void setupUi(QDialog *ChatRoomPanel)
    {
        if (ChatRoomPanel->objectName().isEmpty())
            ChatRoomPanel->setObjectName(QString::fromUtf8("ChatRoomPanel"));
        ChatRoomPanel->resize(300, 700);
        widget = new QWidget(ChatRoomPanel);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 300, 700));
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/chatpanel.png);"));
        tabWidget = new QTabWidget(widget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(25, 195, 250, 480));
        tabWidget->setCursor(QCursor(Qt::PointingHandCursor));
        tabWidget->setAcceptDrops(false);
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setAutoFillBackground(false);
        tabWidget->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);"));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tabWidget->setMovable(false);
        CloseWinBtn = new QToolButton(widget);
        CloseWinBtn->setObjectName(QString::fromUtf8("CloseWinBtn"));
        CloseWinBtn->setGeometry(QRect(260, 30, 30, 30));
        QFont font;
        font.setPointSize(14);
        CloseWinBtn->setFont(font);
        CloseWinBtn->setCursor(QCursor(Qt::PointingHandCursor));
        CloseWinBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/closeBtn.png);"));
        headerImage = new QPushButton(widget);
        headerImage->setObjectName(QString::fromUtf8("headerImage"));
        headerImage->setGeometry(QRect(40, 80, 71, 71));
        headerImage->setCursor(QCursor(Qt::PointingHandCursor));
        headerImage->setStyleSheet(QString::fromUtf8("background-image: url(null);\n"
"border-image: url(:/header/logo.png);"));
        MiniButton = new QToolButton(widget);
        MiniButton->setObjectName(QString::fromUtf8("MiniButton"));
        MiniButton->setGeometry(QRect(230, 30, 30, 30));
        MiniButton->setFont(font);
        MiniButton->setCursor(QCursor(Qt::PointingHandCursor));
        MiniButton->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/minBtn.png);"));
        nameLineEdit = new QLineEdit(widget);
        nameLineEdit->setObjectName(QString::fromUtf8("nameLineEdit"));
        nameLineEdit->setGeometry(QRect(120, 90, 120, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(16);
        nameLineEdit->setFont(font1);
        nameLineEdit->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/content.png);"));
        nameLineEdit->setReadOnly(true);
        line = new QFrame(widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(115, 80, 2, 75));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(ChatRoomPanel);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(ChatRoomPanel);
    } // setupUi

    void retranslateUi(QDialog *ChatRoomPanel)
    {
        ChatRoomPanel->setWindowTitle(QApplication::translate("ChatRoomPanel", "Dialog", 0, QApplication::UnicodeUTF8));
        CloseWinBtn->setText(QString());
        headerImage->setText(QString());
        MiniButton->setText(QString());
        nameLineEdit->setText(QApplication::translate("ChatRoomPanel", "\345\255\244\350\210\237\344\270\200\345\217\266", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ChatRoomPanel: public Ui_ChatRoomPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATROOMPANEL_H
