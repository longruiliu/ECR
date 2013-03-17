#include "managerwindow.h"
#include "ui_managerwindow.h"
#include "ctime"
#include"Database.h"
#include "user.h"
#include "group.h"
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
    connect(this,SIGNAL(clearLists()),ui->groupMemberList, SLOT(clear()));
    restoreFromDB();
}

managerWindow::~managerWindow()
{
    delete ui;
}

void managerWindow::selectGroupItem()
{
    if (ui->groupListWidget->currentRow()<0)
            return;
    ui->groupMemberList->clear();
    group gp = groupList.at(ui->groupListWidget->currentIndex().row());
    ui->groupNameBox->setText(gp.groupName.c_str());
    for (std::vector<int>::iterator i = gp.groupMember.begin(); i!=gp.groupMember.end();i++)
        ui->groupMemberList->addItem(user::getUserName(*i).c_str());
}

void managerWindow::selectUserItem()
{
    if (ui->userListWidget->currentRow()<0)
    {
        ui->modifyUser->setEnabled(false);
        ui->deleteUser->setEnabled(false);
        return;
    }
    else
    {
        ui->modifyUser->setEnabled(true);
        ui->deleteUser->setEnabled(true);
    }
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
    db.restoreGroupMember();
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
    db.clearDatabase();
    db.saveGrouplist();
    db.saveUserlist();
    db.saveGroupMember();
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

void managerWindow::on_addUser_clicked()
{
    user ur;
    int uid = rand()%10000;
    while (user::hasUser(uid))
        uid = rand()%10000;
    ur.userID = uid;
    ur.userName = ui->usernameBox->text().toStdString();
    ur.pwd = ui->passwdBox->text().toStdString();
    ur.info = ui->userInfoBox->toPlainText().toStdString();
    ur.setRoot(ui->cbIsRoot->isChecked());
    ur.setUserMg(ui->cbCanUserMg->isChecked());
    ur.setGroupMg(ui->cbCanGroupMG->isChecked());
    userList.push_back(ur);
    saveToDB();
    restoreFromDB();
}

void managerWindow::on_deleteUser_clicked()
{
    userList.erase(userList.begin()+ui->userListWidget->currentIndex().row());
    saveToDB();
    restoreFromDB();
}

void managerWindow::on_addGroupMember_clicked()
{
    if (ui->userListWidget->currentRow()<0 ||ui->groupListWidget->currentRow()<0)
        return;
    group& gp = groupList[ui->groupListWidget->currentRow()];
    user& ur = userList[ui->userListWidget->currentRow()];
    gp.groupMember.push_back(ur.userID);
    saveToDB();
    restoreFromDB();
}

void managerWindow::on_addGroup_clicked()
{
    int currentRow = ui->userListWidget->currentRow();
    if (currentRow<0)
        return;
    user& ur = userList[currentRow];
    group gp(ui->groupNameBox->text().toStdString(), ur.userID);
    groupList.push_back(gp);
    saveToDB();
    restoreFromDB();
}

void managerWindow::on_delGroup_clicked()
{
    int currentRow = ui->groupListWidget->currentRow();
    if (currentRow<0)
        return;
    groupList.erase(groupList.begin()+ currentRow);
    saveToDB();
    restoreFromDB();
}

void managerWindow::on_deleteMember_clicked()
{
    int memberIndex = ui->groupMemberList->currentRow();
    int groupIndex = ui->groupListWidget->currentRow();
    if (memberIndex<0 || groupIndex < 0)
        return;
    group& gp = groupList[groupIndex];
    gp.groupMember.erase(gp.groupMember.begin()+memberIndex);
    saveToDB();
    restoreFromDB();
}
