#include "friendlist.h"
#include "ui_friendlist.h"

FriendList::FriendList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendList)
{
    ui->setupUi(this);


    //add friend to list
    ui->FriendListWidget->setViewMode(QListView::ListMode);


    QListWidgetItem *friend1 = new QListWidgetItem(ui->FriendListWidget);
    friend1->setIcon(QIcon(":/header/1.png"));
    friend1->setText(tr("Nick Name 1"));
    friend1->setTextAlignment(Qt::AlignLeft);
    friend1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *friend2 = new QListWidgetItem(ui->FriendListWidget);
    friend2->setIcon(QIcon(":/header/2.png"));
    friend2->setText(tr("Nick Name 2"));
    friend2->setTextAlignment(Qt::AlignLeft);
    friend2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    //double click handle
    connect(ui->FriendListWidget,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(startChatWithSelectedFriend()));


    //Right click handle
    ui->FriendListWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->FriendListWidget,SIGNAL(customContextMenuRequested(QPoint)),
            this,SLOT(onRightClick(QPoint)));

}

FriendList::~FriendList()
{
    delete ui;
}

void FriendList::startChatWithSelectedFriend()
{
    chatRoom *cr = new chatRoom();
    cr->show();
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
    //Refresh Friend List
}

void FriendList::viewFriendInfo()
{
    //View Friend Info
}


void FriendList::receiveResponse(Response resp)
{

}
