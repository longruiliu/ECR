﻿#include "grouplist.h"
#include "ui_grouplist.h"

GroupList::GroupList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupList)
{
    ui->setupUi(this);

    ui->GroupListWidget->setViewMode(QListView::IconMode);

    connect(ui->GroupListWidget,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(startGroupChat()));
    setWindowOpacity(0.5);

}

GroupList::~GroupList()
{
    delete ui;
}


void GroupList::startGroupChat()
{
    int currentGroupID = groupIDList[ui->GroupListWidget->currentRow()];
    GroupChatDialog *gcd = new GroupChatDialog(currentGroupID);
    gcd->show();
}


void GroupList::receiveResponse(Response resp)
{
}

void GroupList::addGroupToList(int groupID, QString groupName)
{
    groupIDList.push_back(groupID);
    QListWidgetItem *group = new QListWidgetItem(ui->GroupListWidget);
    group->setIcon(QIcon(":/header/3.png"));
    group->setText(groupName);
    group->setTextAlignment(Qt::AlignLeft);
    group->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

void GroupList::resetGroudList()
{
    ui->GroupListWidget->clear();
    groupIDList.clear();
}
