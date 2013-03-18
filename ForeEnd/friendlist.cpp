#include "friendlist.h"
#include "ui_friendlist.h"
#include "messagelistener.h"
#include "networkqueue.h"
#include "msgRecord.h"
#include "viewfriendinfo.h"
#include <QDebug>
extern messageListener ml;
extern int myUserID;

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

    //向服务器拉取消息
    timerRefresh = new QTimer(this);
    connect(timerRefresh,SIGNAL(timeout()),this,SLOT(RefreshFromServer()));
    timerRefresh->start(FreshRate);
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
    if(friendID==myUserID)
    {
        emit getMyInfo(nickName,friendInfo);
    }

    QListWidgetItem *friend1 = new QListWidgetItem(ui->FriendListWidget);
    if(nickName.at(0)=='_')
    {
        friend1->setIcon(QIcon(":/header/1off.png"));
     //   nickName=nickName.right(nickName.size()-1);
        friend1->setText(nickName.right(nickName.size()-1));
    }
    else
    {
        friend1->setIcon(QIcon(":/header/1on.png"));
        friend1->setText(nickName);
    }

    friend1->setTextAlignment(Qt::AlignLeft);
    friend1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    friendIDList.push_back(friendID);
    friendInfoList[friendID] = friendInfo;
    nickNameList[friendID] = nickName;

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
    //qDebug()<<chatRoomMap[currentFriendID]->currentFriendID;
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
        popMenu->addAction(tr("刷新好友列表"),this,SLOT(refreshFriendList()));
    }
    else
    {
        //if selected an item
        popMenu->addAction(tr("查看好友信息"),this,SLOT(viewFriendInfo()));
        popMenu->addAction(tr("与该好友聊天"),this,SLOT(startChatWithSelectedFriend()));
        popMenu->addAction(tr("刷新好友列表"),this,SLOT(refreshFriendList()));
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
    int currentFriendID= friendIDList[ui->FriendListWidget->currentRow()];
    ViewFriendInfo *vfi = new ViewFriendInfo(nickNameList[currentFriendID],
                                             friendInfoList[currentFriendID]);
    vfi->show();

}


void FriendList::receiveResponse(Response resp)
{

}

QString& FriendList::getNickname(int userID)
{
    return nickNameList[userID];
}

QString& FriendList::getFriendInfo(int userID)
{
    return friendInfoList[userID];
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
        //qDebug() << i->srcID;
        int srcID = i->srcID;
        startChatWithSelectedFriend(srcID);
        qDebug()<<"MsgSize" << i->msgText.size();

        chatRoomMap[srcID]->AddMessageToList(QString(i->msgText.c_str()),
                                                    getNickname(srcID), 1);
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

void FriendList::KeepAliveResponse(Response resp)
{

}

void FriendList::pullMessageFromServer()
{
    newMessage();
}

void FriendList::sendKeepAliveToServer()
{
    Nevent ev;
    std::string str;

    str.clear();
    str.insert(0,"regular");
    ev.req.setType(str);

    str.clear();
    str.insert(0,"keepalive");
    ev.req.setMethod(str);

    ev.callee = this;
    strcpy(ev.signal, SLOT(keepAliveResponse(Response)));

    nq.pushEvent(ev);
}

void FriendList::RefreshFromServer()
{
    static int flag;
    flag++;

    //刷新列表,30S刷新一次
    if(0==flag%10)
        getUserList();

    //获取消息
    if(0==flag%10)
    pullMessageFromServer();

    //告诉服务器我还在线 60S刷新一次
    if(0==flag%20)
        sendKeepAliveToServer();
}
