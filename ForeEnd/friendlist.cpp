﻿#include "friendlist.h"
#include "ui_friendlist.h"
#include "messagelistener.h"
#include "networkqueue.h"
#include "msgRecord.h"

extern messageListener ml;

QMap<int, QString> FriendList::nickNameList;
QMap<int, QString> FriendList::friendInfoList;

FriendList::FriendList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendList)
{
    ui->setupUi(this);


    //add friend to list
    ui->FriendListWidget->setViewMode(QListView::ListMode);

    //double click handle
    connect(ui->FriendListWidget,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(startChatWithSelectedFriend()));

    //Right click handle
    ui->FriendListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->FriendListWidget,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(onRightClick(QPoint)));

    //reveive Message signal
 //   connect(&ml,SIGNAL())
    getUserList();
    connect(&ml, SIGNAL(youHaveMessage()), this, SLOT(newMessage()));
}

FriendList::~FriendList()
{
    delete ui;
}

void FriendList::handleChatRoomClose(int friendID)
{
    delete chatRoomMap[friendID];
    chatRoomMap.remove(friendID);
}


void FriendList::addFriendToList(int friendID, QString nickName, QString friendInfo)
{
    friendIDList.push_back(friendID);
    nickNameList[friendID] = nickName;
    friendInfoList[friendID] = friendInfo;

    QListWidgetItem *friend1 = new QListWidgetItem(ui->FriendListWidget);
    friend1->setIcon(QIcon(":/header/1.png"));
    friend1->setText(nickName);

    friend1->setTextAlignment(Qt::AlignLeft);
    friend1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
}

void FriendList::startChatWithSelectedFriend(int currentFriendID)
{
    if(0==currentFriendID)
        currentFriendID= friendIDList[ui->FriendListWidget->currentRow()];

    if(chatRoomMap.contains(currentFriendID))
    {
        chatRoomMap[currentFriendID]->raiseChatDialog();
    }
    else
    {
        chatRoomMap[currentFriendID]=new chatRoom(currentFriendID);
        chatRoomMap[currentFriendID]->show();

        connect(chatRoomMap[currentFriendID],SIGNAL(closeDialog(int)),
                this,SLOT(handleChatRoomClose(int)));
    }
    qDebug()<<chatRoomMap[currentFriendID]->currentFriendID;
    //Chat
}

void FriendList::onRightClick(QPoint pos)
{
    //get the selected item
    QListWidgetItem *curitem = ui->FriendListWidget->itemAt(pos);
    //create menu
    QMenu *popMenu = new QMenu(ui->FriendListWidget);
    popMenu->setStyleSheet("background-color: rgba(255, 178, 102, 255)");
    if(curitem == NULL)
    {
        //if selected nothing
        popMenu->addAction(tr("Refresh Friend List"),this,SLOT(refreshFriendList()));
    }
    else
    {
        //if selected an item
        popMenu->addAction(tr("View Friend Info"),this,SLOT(refreshFriendList()));
        popMenu->addAction(tr("Talk With Friend"),this,SLOT(startChatWithSelectedFriend()));
        popMenu->addAction(tr("Refresh Friend List"),this,SLOT(refreshFriendList()));
    }
    popMenu->exec(QCursor::pos());//然后运行弹出菜单
}

void FriendList::refreshFriendList()
{
    getUserList();
}

void FriendList::viewFriendInfo()
{
    //View Friend Info
}


void FriendList::receiveResponse(Response resp)
{

}

QString& FriendList::getNickname(int userID)
{
    return nickNameList[userID];
}

void FriendList::newMessage(){
    Nevent ev;
    std::string str;

    str.clear();
    str.insert(0,"regular");
    ev.req.setType(str);

    str.clear();
    str.insert(0,"fetchmsg");
    ev.req.setMethod(str);

    ev.callee = this;
    strcpy(ev.signal, SLOT(newMessaveResponse(Response)));

    nq.pushEvent(ev);

}

void FriendList::newMessaveResponse(Response resp){
    std::vector<msgRecord> rec;
    std::vector<msgRecord>::iterator i;

    resp.getMsgList(rec);
    for(i = rec.begin(); i != rec.end(); i++){
        qDebug() << i->srcID;
        int srcID = i->srcID;
        startChatWithSelectedFriend(srcID);

        chatRoomMap[srcID]->AddMessageToList(QString(i->msgText.c_str()),
                                                    getNickname(srcID), false);
        chatRoomMap[srcID]->timeStamp = i->postTime;
    }
}


void FriendList::getUserList(){
    Nevent ev;
    std::string str;

    ui->FriendListWidget->clear();
    userInfoRequestQueue.clear();
    userIDList.clear();
    nickNameList.clear();
    friendIDList.clear();
    friendInfoList.clear();
    //chatRoomMap.clear();

    str.clear();
    str.insert(0, "regular");
    ev.req.setType(str);

    str.clear();
    str.insert(0, "userlist");
    ev.req.setMethod(str);
    ev.callee = this;
    strcpy(ev.signal, SLOT(getUserListResponse(Response)));

    nq.pushEvent(ev);
}

void FriendList::getUserListResponse(Response resp){
    std::vector<int>::iterator iter;
    UserList ul;
    resp.getUserList(ul);
    std::string str;

    for(iter = ul.begin(); iter != ul.end(); iter++){
        userIDList.push_back(*iter);
        userInfoRequestQueue.push_back(*iter);
        Nevent ev;

        str.clear();
        str.insert(0,"regular");
        ev.req.setType(str);

        str.clear();
        str.insert(0,"userinfo");
        ev.req.setMethod(str);

        ev.req.addParams(*iter);

        ev.callee = this;
        strcpy(ev.signal, SLOT(receiveUserInfoResponse(Response)));

        nq.pushEvent(ev);
    }
}

void FriendList::receiveUserInfoResponse(Response resp)
{
    int id;

    id = userInfoRequestQueue.front();
    userInfoRequestQueue.pop_front();
    UserInfo _ui;
    std::string name;
    resp.getUserInfo(_ui);
    resp.getUserName(name);

    addFriendToList(id, QString(name.c_str()), QString(_ui.c_str()));

}
