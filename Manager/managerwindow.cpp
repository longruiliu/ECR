#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "ctime"
#include"Database.h"
#include<QDebug>

managerWindow::managerWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::managerWindow)
{
    ui->setupUi(this);
    connect(ui->userListWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this,SLOT(selectUserItem()));
    connect(ui->groupListWidget, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this,SLOT(selectGroupItem()));
    connect(this,SIGNAL(clearLists()),ui->userListWidget, SLOT(clear()));
    connect(this,SIGNAL(clearLists()),ui->groupListWidget, SLOT(clear()));
    restoreFromDB();
}

managerWindow::~managerWindow()
{
    delete ui;
}

void managerWindow::selectGroupItem()
{
    group gp = groupList.at(ui->groupListWidget->currentIndex().row());
    ui->groupNameBox->setText(gp.groupName.c_str());
}

void managerWindow::selectUserItem()
{
    if (ui->userListWidget->currentRow()<0)
            return;
    user ur = userList.at(ui->userListWidget->currentIndex().row());
    ui->usernameBox->setText(QString(ur.userName.c_str()));
    ui->passwdBox->setText(QString(ur.pwd.c_str()));
    ui->userInfoBox->setHtml(ur.info.c_str());
    ui->cbIsRoot->setChecked(ur.isRoot());
    ui->cbCanUserMg->setChecked(ur.canUserMg());
    ui->cbCanGroupMG->setChecked(ur.canGroupMg());
}


void managerWindow::selectMemberItem()
{

}


void managerWindow::restoreFromDB()
{
    Database db(std::string("ECR.db"));
    db.restoreGrouplist();
    db.restoreUserlist();
    db.close();
    emit clearLists();
    for (ulit i = userList.begin(); i!=userList.end(); i++)
        ui->userListWidget->addItem(QString(i->userName.c_str())+ ":" + QString::number(i->userID));

    for (glit i = groupList.begin(); i!=groupList.end(); i++)
        ui->groupListWidget->addItem(QString(i->groupName.c_str())+":"+QString::number(i->groupID));
}

void managerWindow::saveToDB()
{
    Database db(std::string("ECR.db"));
    db.saveGrouplist();
    db.saveUserlist();
    db.close();
}

void managerWindow::on_modifyUser_clicked()
{
    user& ur = userList.at(ui->userListWidget->currentIndex().row());
    ur.userName = ui->usernameBox->text().toStdString();
    ur.pwd = ui->passwdBox->text().toStdString();
    ur.info = ui->userInfoBox->toPlainText().toStdString();
    ur.setRoot(ui->cbIsRoot->isChecked());
    ur.setUserMg(ui->cbCanUserMg->isChecked());
    ur.setGroupMg(ui->cbCanGroupMG->isChecked());
    saveToDB();
    restoreFromDB();
}
