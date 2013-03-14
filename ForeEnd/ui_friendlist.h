/********************************************************************************
** Form generated from reading UI file 'friendlist.ui'
**
** Created: Thu Mar 14 17:07:52 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRIENDLIST_H
#define UI_FRIENDLIST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FriendList
{
public:
    QListWidget *FriendListWidget;

    void setupUi(QWidget *FriendList)
    {
        if (FriendList->objectName().isEmpty())
            FriendList->setObjectName(QString::fromUtf8("FriendList"));
        FriendList->resize(250, 480);
        FriendList->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/content.png);"));
        FriendListWidget = new QListWidget(FriendList);
        FriendListWidget->setObjectName(QString::fromUtf8("FriendListWidget"));
        FriendListWidget->setGeometry(QRect(0, 0, 250, 480));
        FriendListWidget->setStyleSheet(QString::fromUtf8("border-image: url(:/bg/content.png);\n"
"background-image: url(:/bg/content.png);"));

        retranslateUi(FriendList);

        QMetaObject::connectSlotsByName(FriendList);
    } // setupUi

    void retranslateUi(QWidget *FriendList)
    {
        FriendList->setWindowTitle(QApplication::translate("FriendList", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FriendList: public Ui_FriendList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRIENDLIST_H
