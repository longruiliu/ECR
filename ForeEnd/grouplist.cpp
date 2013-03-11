#include "grouplist.h"
#include "ui_grouplist.h"

GroupList::GroupList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GroupList)
{
    ui->setupUi(this);

    ui->GroupListWidget->setViewMode(QListView::IconMode);

    QListWidgetItem *configButton = new QListWidgetItem(ui->GroupListWidget);
    configButton->setIcon(QIcon(":/header/1.png"));
    configButton->setText(tr("孤舟一叶粉丝群1"));
    configButton->setTextAlignment(Qt::AlignLeft);
    configButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *updateButton = new QListWidgetItem(ui->GroupListWidget);
    updateButton->setIcon(QIcon(":/header/2.png"));
    updateButton->setText(tr("孤舟一叶粉丝群2"));
    updateButton->setTextAlignment(Qt::AlignLeft);
    updateButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    QListWidgetItem *queryButton = new QListWidgetItem(ui->GroupListWidget);
    queryButton->setIcon(QIcon(":/header/3.png"));
    queryButton->setText(tr("孤舟一叶粉丝群3"));
    queryButton->setTextAlignment(Qt::AlignLeft);
    queryButton->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);


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
    GroupChatDialog *gcd = new GroupChatDialog();
    gcd->show();
}
