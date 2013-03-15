/********************************************************************************
** Form generated from reading UI file 'grouplist.ui'
**
** Created: Thu Mar 14 17:07:52 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPLIST_H
#define UI_GROUPLIST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QListWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GroupList
{
public:
    QListWidget *GroupListWidget;

    void setupUi(QWidget *GroupList)
    {
        if (GroupList->objectName().isEmpty())
            GroupList->setObjectName(QString::fromUtf8("GroupList"));
        GroupList->resize(250, 480);
        GroupList->setStyleSheet(QString::fromUtf8("border-image: url(:/bg/content.png);\n"
"background-image: url(:/bg/content.png);"));
        GroupListWidget = new QListWidget(GroupList);
        GroupListWidget->setObjectName(QString::fromUtf8("GroupListWidget"));
        GroupListWidget->setGeometry(QRect(0, 0, 250, 480));
        GroupListWidget->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/editTextbg.png);"));

        retranslateUi(GroupList);

        QMetaObject::connectSlotsByName(GroupList);
    } // setupUi

    void retranslateUi(QWidget *GroupList)
    {
        GroupList->setWindowTitle(QApplication::translate("GroupList", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GroupList: public Ui_GroupList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPLIST_H
