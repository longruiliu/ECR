#include "groupchatdialog.h"
#include "ui_groupchatdialog.h"

GroupChatDialog::GroupChatDialog(int groupID,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupChatDialog),
    fadeEffect(this)
{
    currentGroupID=groupID;

    ui->setupUi(this);

    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);

    fadeEffect.startFadeInOut(FADEIN);

    QListWidgetItem *configButton = new QListWidgetItem(ui->FriendListWidget);
    configButton->setIcon(QIcon(":/header/1.png"));
    configButton->setText(tr("Nick Name"));
    configButton->setTextAlignment(Qt::AlignLeft);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *updateButton = new QListWidgetItem(ui->FriendListWidget);
    updateButton->setIcon(QIcon(":/header/2.png"));
    updateButton->setText(tr("Nick Name"));
    updateButton->setTextAlignment(Qt::AlignLeft);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    connect(ui->FriendListWidget,SIGNAL(doubleClicked(QModelIndex)),
            this,SLOT(startChatWithSelectedFriend()));
}

GroupChatDialog::~GroupChatDialog()
{
    delete ui;
}

void GroupChatDialog::mousePressEvent(QMouseEvent *event)
{
   this->windowPos = this->pos();
   this->mousePos = event->globalPos();
   this->dPos = mousePos - windowPos;
}
void GroupChatDialog::mouseMoveEvent(QMouseEvent *event)
{
   this->move(event->globalPos() - this->dPos);
}


void GroupChatDialog::on_CloseWinBtn_clicked()
{
    fadeEffect.startFadeInOut(FADEOUT_EXIT);
}

void GroupChatDialog::startChatWithSelectedFriend()
{
    chatRoom *cr = new chatRoom();
    cr->show();
}

void GroupChatDialog::on_SendMessageBtn_clicked()
{
    sendText=ui->SendMessageText->toPlainText();
}

void GroupChatDialog::receiveResponse(Response resp)
{

}
