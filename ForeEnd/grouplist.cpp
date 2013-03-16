#include "grouplist.h"
#include "ui_grouplist.h"
#include "messagelistener.h"
#include "networkqueue.h"

GroupList::GroupList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupList)
{
    ui->setupUi(this);

    ui->GroupListWidget->setViewMode(QListView::IconMode);

    connect(ui->GroupListWidget,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(startChatWithSelectGroup()));
    setWindowOpacity(0.5);
    getGroupList();
    connect(&ml, SIGNAL(youHaveGroupMessage(int)),this, SLOT(newNotify(int)), Qt::QueuedConnection);
}

GroupList::~GroupList()
{
    delete ui;
}

void GroupList::handleGroupChatDialogClose(int groupid)
{
    delete groupChatDialogMap[groupid];
    groupChatDialogMap.remove(groupid);
}

void GroupList::startChatWithSelectGroup(int groupid)
{
    if(0==groupid)
    {
        groupid = groupIDList[ui->GroupListWidget->currentRow()];
    }

    if(groupChatDialogMap.contains(groupid))
    {
        groupChatDialogMap[groupid]->raiseChatDialog();
    }
    else
    {
        groupChatDialogMap[groupid]=new GroupChatDialog(groupid);
        groupChatDialogMap[groupid]->show();

        connect(groupChatDialogMap[groupid],SIGNAL(closeDialog(int)),
                this,SLOT(handleGroupChatDialogClose(int)));
    }
}


void GroupList::receiveResponse(Response resp)
{
}

void GroupList::addGroupToList(int groupID, QString groupName)
{
    qDebug() << "add group to list" << groupName << endl;
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

void GroupList::newNotify(int groupID)
{
    if (!groupChatDialogMap.contains(groupID))
        startChatWithSelectGroup(groupID);

    QObject::connect(this,SIGNAL(doFetchGroupMsg()), groupChatDialogMap[groupID],SLOT(getGroupMsg()));
    emit doFetchGroupMsg();
    QObject::disconnect(this,SIGNAL(doFetchGroupMsg()), groupChatDialogMap[groupID],SLOT(getGroupMsg()));

}


void GroupList::getGroupList(){
    Nevent ev;
    std::string str;

    ui->GroupListWidget->clear();
    groupIDList.clear();

    str.clear();
    str.insert(0, "group");
    ev.req.setType(str);

    str.clear();
    str.insert(0, "fetchgrp");
    ev.req.setMethod(str);
    ev.callee = this;
    strcpy(ev.signal, SLOT(getGroupListResponse(Response)));

    nq.pushEvent(ev);
}



void GroupList::getGroupListResponse(Response resp){
    qDebug() << "get Group List response" << endl;
    std::vector<std::pair<int, std::string> > gl;
    std::vector<std::pair<int, std::string> >::iterator iter;

    resp.getGroupList(gl);

    for(iter = gl.begin(); iter != gl.end(); iter++)
    {
        addGroupToList(iter->first,QString(iter->second.c_str()));
    }
}
