#include "grouplist.h"
#include "ui_grouplist.h"
#include "messagelistener.h"

GroupList::GroupList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupList)
{
    ui->setupUi(this);

    ui->GroupListWidget->setViewMode(QListView::IconMode);

    connect(ui->GroupListWidget,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(startChatWithSelectGroup()));
    setWindowOpacity(0.5);
    connect(&ml, SIGNAL(youHaveGroupMessage(int)),this, SLOT(newNotify(int)));
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
