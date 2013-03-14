/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created: Thu Mar 14 17:07:52 2013
**      by: Qt User Interface Compiler version 4.8.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QToolButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginDialog
{
public:
    QWidget *widget;
    QLineEdit *NamelineEdit;
    QLineEdit *PswlineEdit;
    QToolButton *CloseWinBtn;
    QToolButton *MinWinBtn;
    QPushButton *LoginBtn;
    QPushButton *configBtn;
    QPushButton *registerBtn;
    QPushButton *getPswBtn;
    QLabel *messageLabel;

    void setupUi(QDialog *loginDialog)
    {
        if (loginDialog->objectName().isEmpty())
            loginDialog->setObjectName(QString::fromUtf8("loginDialog"));
        loginDialog->resize(400, 341);
        loginDialog->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);"));
        widget = new QWidget(loginDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 0, 400, 300));
        widget->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/loginDialogbg.png);"));
        NamelineEdit = new QLineEdit(widget);
        NamelineEdit->setObjectName(QString::fromUtf8("NamelineEdit"));
        NamelineEdit->setGeometry(QRect(68, 122, 186, 31));
        NamelineEdit->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/content.png);"));
        PswlineEdit = new QLineEdit(widget);
        PswlineEdit->setObjectName(QString::fromUtf8("PswlineEdit"));
        PswlineEdit->setGeometry(QRect(68, 174, 186, 31));
        PswlineEdit->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/content.png);"));
        PswlineEdit->setEchoMode(QLineEdit::Password);
        PswlineEdit->setReadOnly(false);
        CloseWinBtn = new QToolButton(widget);
        CloseWinBtn->setObjectName(QString::fromUtf8("CloseWinBtn"));
        CloseWinBtn->setGeometry(QRect(356, 50, 30, 30));
        CloseWinBtn->setCursor(QCursor(Qt::PointingHandCursor));
        CloseWinBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/bg/closeBtn.png);"));
        MinWinBtn = new QToolButton(widget);
        MinWinBtn->setObjectName(QString::fromUtf8("MinWinBtn"));
        MinWinBtn->setGeometry(QRect(330, 50, 30, 30));
        MinWinBtn->setCursor(QCursor(Qt::PointingHandCursor));
        MinWinBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/bg/minBtn.png);"));
        LoginBtn = new QPushButton(widget);
        LoginBtn->setObjectName(QString::fromUtf8("LoginBtn"));
        LoginBtn->setGeometry(QRect(80, 220, 180, 32));
        LoginBtn->setCursor(QCursor(Qt::PointingHandCursor));
        LoginBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content.png);\n"
"border-image: url(:/bg/loginBtnBg.png);"));
        configBtn = new QPushButton(widget);
        configBtn->setObjectName(QString::fromUtf8("configBtn"));
        configBtn->setGeometry(QRect(275, 225, 41, 21));
        configBtn->setCursor(QCursor(Qt::PointingHandCursor));
        configBtn->setStyleSheet(QString::fromUtf8("background-image: url(:/bg/content_0.png);\n"
"border-image: url(:/bg/configBtn.png);"));
        registerBtn = new QPushButton(widget);
        registerBtn->setObjectName(QString::fromUtf8("registerBtn"));
        registerBtn->setGeometry(QRect(270, 125, 75, 23));
        registerBtn->setCursor(QCursor(Qt::PointingHandCursor));
        registerBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/bg/registerBg.png);\n"
"background-image: url(:/bg/content_0.png);"));
        getPswBtn = new QPushButton(widget);
        getPswBtn->setObjectName(QString::fromUtf8("getPswBtn"));
        getPswBtn->setGeometry(QRect(270, 175, 75, 23));
        getPswBtn->setCursor(QCursor(Qt::PointingHandCursor));
        getPswBtn->setStyleSheet(QString::fromUtf8("border-image: url(:/bg/getpasswordBg.png);\n"
"background-image: url(:/bg/content_0.png);"));
        messageLabel = new QLabel(loginDialog);
        messageLabel->setObjectName(QString::fromUtf8("messageLabel"));
        messageLabel->setGeometry(QRect(80, 310, 241, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        messageLabel->setFont(font);
        messageLabel->setAlignment(Qt::AlignCenter);

        retranslateUi(loginDialog);
        QObject::connect(MinWinBtn, SIGNAL(clicked()), loginDialog, SLOT(showMinimized()));

        QMetaObject::connectSlotsByName(loginDialog);
    } // setupUi

    void retranslateUi(QDialog *loginDialog)
    {
        loginDialog->setWindowTitle(QApplication::translate("loginDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        NamelineEdit->setPlaceholderText(QApplication::translate("loginDialog", "\347\224\250\346\210\267\345\220\215", 0, QApplication::UnicodeUTF8));
        PswlineEdit->setPlaceholderText(QApplication::translate("loginDialog", "\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        CloseWinBtn->setText(QString());
        MinWinBtn->setText(QString());
        LoginBtn->setText(QString());
        configBtn->setText(QString());
        registerBtn->setText(QString());
        getPswBtn->setText(QString());
        messageLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class loginDialog: public Ui_loginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
