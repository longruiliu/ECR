#ifndef GROUPLIST_H
#define GROUPLIST_H

#include <QWidget>
#include "groupchatdialog.h"

namespace Ui {
    class GroupList;
}

class GroupList : public QWidget
{
    Q_OBJECT

public:
    explicit GroupList(QWidget *parent = 0);

    void addGroupToList(int groupID,QString groupName);
    void resetGroudList();
    ~GroupList();

private:
    Ui::GroupList *ui;

    QVector<int> groupIDList;//维护了组ID的列表
    QMap<int,GroupChatDialog*> groupChatDialogMap;//维护了组聊天对话框的列表

private slots:
    void startChatWithSelectGroup(int groupid=0) ;
    void receiveResponse(Response resp);
    void handleGroupChatDialogClose(int);
};

#endif // GROUPLIST_H
