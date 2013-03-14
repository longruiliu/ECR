/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created: Thu Mar 14 17:07:52 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QWidget *widget;
    QLineEdit *userNameEdit;
    QLineEdit *userPsw1Edit;
    QLineEdit *userPsw2Edit;
    QLineEdit *userNickNameEdit;
    QPushButton *OkBtn;
    QToolButton *CloseWinBtn;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName(QString::fromUtf8("RegisterDialog"));
        RegisterDialog->resize(400, 399);
        widget = new QWidget(RegisterDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 400, 399));
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/registerDialogBg.png);"));
        userNameEdit = new QLineEdit(widget);
        userNameEdit->setObjectName(QString::fromUtf8("userNameEdit"));
        userNameEdit->setGeometry(QRect(90, 130, 221, 31));
        userNameEdit->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/content.png);"));
        userPsw1Edit = new QLineEdit(widget);
        userPsw1Edit->setObjectName(QString::fromUtf8("userPsw1Edit"));
        userPsw1Edit->setGeometry(QRect(90, 170, 221, 31));
        userPsw1Edit->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/content.png);"));
        userPsw1Edit->setEchoMode(QLineEdit::Password);
        userPsw1Edit->setDragEnabled(false);
        userPsw2Edit = new QLineEdit(widget);
        userPsw2Edit->setObjectName(QString::fromUtf8("userPsw2Edit"));
        userPsw2Edit->setGeometry(QRect(90, 210, 221, 31));
        userPsw2Edit->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/content.png);"));
        userPsw2Edit->setEchoMode(QLineEdit::Password);
        userNickNameEdit = new QLineEdit(widget);
        userNickNameEdit->setObjectName(QString::fromUtf8("userNickNameEdit"));
        userNickNameEdit->setGeometry(QRect(90, 252, 221, 31));
        userNickNameEdit->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/content.png);"));
        OkBtn = new QPushButton(widget);
        OkBtn->setObjectName(QString::fromUtf8("OkBtn"));
        OkBtn->setGeometry(QRect(120, 300, 161, 31));
        OkBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/confirmBtnBg.png);"));
        CloseWinBtn = new QToolButton(widget);
        CloseWinBtn->setObjectName(QString::fromUtf8("CloseWinBtn"));
        CloseWinBtn->setGeometry(QRect(360, 40, 31, 31));
        CloseWinBtn->setCursor(QCursor(Qt::PointingHandCursor));
        CloseWinBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/bg/closeBtn.png);\n"
"background-image: url(:/bg/content.png);"));

        retranslateUi(RegisterDialog);

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QApplication::translate("RegisterDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        userNameEdit->setPlaceholderText(QApplication::translate("RegisterDialog", "\347\224\250\346\210\267\345\220\215", 0, QApplication::UnicodeUTF8));
        userPsw1Edit->setPlaceholderText(QApplication::translate("RegisterDialog", "\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        userPsw2Edit->setPlaceholderText(QApplication::translate("RegisterDialog", "\347\241\256\350\256\244\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        userNickNameEdit->setPlaceholderText(QApplication::translate("RegisterDialog", "\346\230\276\347\244\272\346\230\265\347\247\260", 0, QApplication::UnicodeUTF8));
        OkBtn->setText(QString());
        CloseWinBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
