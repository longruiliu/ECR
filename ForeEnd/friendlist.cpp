#include "friendlist.h"
#include "ui_friendlist.h"

FriendList::FriendList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FriendList)
{
    ui->setupUi(this);


    //添加好友在列表上
    //设置列表显示风格
 //   ui->FriendListWidget->setViewMode(QListView::IconMode);
    ui->FriendListWidget->setViewMode(QListView::ListMode);
    QListWidgetItem *friend1 = new QListWidgetItem(ui->FriendListWidget);
    friend1->setIcon(QIcon(":/header/1.png"));
    friend1->setText(tr("孤舟一叶"));
    friend1->setTextAlignment(Qt::AlignLeft);
    friend1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *friend2 = new QListWidgetItem(ui->FriendListWidget);
    friend2->setIcon(QIcon(":/header/2.png"));
    friend2->setText(tr("孤舟一叶"));
    friend2->setTextAlignment(Qt::AlignLeft);
    friend2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    //添加双击列表项的事件处理
    connect(ui->FriendListWidget,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(startChatWithSelectedFriend()));


    //右键列表项弹出菜单
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
    //取得当前被点击的item
    QListWidgetItem *curitem = ui->FriendListWidget->itemAt(pos);
    //建立菜单
    QMenu *popMenu = new QMenu(ui->FriendListWidget);
    popMenu->setStyleSheet("background-color: rgba(255, 178, 102, 255)");
    if(curitem == NULL)
    {
        //如果是在item以外进行的点击
        popMenu->addAction(tr("刷新好友列表"),this,SLOT(refreshFriendList()));
    }
    else
    {
        //如果是在item上进行的点击，就加入删除和播放功能
        popMenu->addAction(tr("查看好友信息"),this,SLOT(refreshFriendList()));
        popMenu->addAction(tr("与该好友对话"),this,SLOT(startChatWithSelectedFriend()));
        popMenu->addAction(tr("刷新好友列表"),this,SLOT(refreshFriendList()));
    }
    popMenu->exec(QCursor::pos());//然后运行弹出菜单
}

void FriendList::refreshFriendList()
{
    //刷新好友列表
}

void FriendList::viewFriendInfo()
{
    //查看好友信息
}
