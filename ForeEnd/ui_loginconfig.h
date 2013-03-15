/********************************************************************************
** Form generated from reading UI file 'loginconfig.ui'
**
** Created: Thu Mar 14 17:07:52 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINCONFIG_H
#define UI_LOGINCONFIG_H

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

class Ui_LoginConfig
{
public:
    QWidget *widget;
    QToolButton *CloseWinBtn;
    QPushButton *okBtn;
    QLineEdit *serverIPText;
    QLineEdit *serverPortText;

    void setupUi(QDialog *LoginConfig)
    {
        if (LoginConfig->objectName().isEmpty())
            LoginConfig->setObjectName(QString::fromUtf8("LoginConfig"));
        LoginConfig->resize(400, 300);
        widget = new QWidget(LoginConfig);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 400, 300));
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/loginConfigDialogBg.png);"));
        CloseWinBtn = new QToolButton(widget);
        CloseWinBtn->setObjectName(QString::fromUtf8("CloseWinBtn"));
        CloseWinBtn->setGeometry(QRect(360, 50, 31, 31));
        CloseWinBtn->setCursor(QCursor(Qt::PointingHandCursor));
        CloseWinBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/bg/closeBtn.png);\n"
"background-image: url(:/bg/content.png);"));
        okBtn = new QPushButton(widget);
        okBtn->setObjectName(QString::fromUtf8("okBtn"));
        okBtn->setGeometry(QRect(115, 220, 180, 32));
        okBtn->setCursor(QCursor(Qt::PointingHandCursor));
        okBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content_0.png);\n"
"border-image: url(:/bg/confirmBtnBg.png);\n"
""));
        serverIPText = new QLineEdit(widget);
        serverIPText->setObjectName(QString::fromUtf8("serverIPText"));
        serverIPText->setGeometry(QRect(110, 125, 191, 31));
        serverIPText->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/content.png);"));
        serverPortText = new QLineEdit(widget);
        serverPortText->setObjectName(QString::fromUtf8("serverPortText"));
        serverPortText->setGeometry(QRect(110, 170, 191, 31));
        serverPortText->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/content.png);"));

        retranslateUi(LoginConfig);

        QMetaObject::connectSlotsByName(LoginConfig);
    } // setupUi

    void retranslateUi(QDialog *LoginConfig)
    {
        LoginConfig->setWindowTitle(QApplication::translate("LoginConfig", "Dialog", 0, QApplication::UnicodeUTF8));
        CloseWinBtn->setText(QString());
        okBtn->setText(QString());
        serverIPText->setPlaceholderText(QApplication::translate("LoginConfig", "\346\234\215\345\212\241\345\231\250IP\345\234\260\345\235\200", 0, QApplication::UnicodeUTF8));
        serverPortText->setPlaceholderText(QApplication::translate("LoginConfig", "\346\234\215\345\212\241\345\231\250\347\253\257\345\217\243\345\217\267", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class LoginConfig: public Ui_LoginConfig {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINCONFIG_H
