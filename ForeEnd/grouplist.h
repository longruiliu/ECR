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

    QVector<int> groupIDList;

private slots:
    void startGroupChat() ;
    void receiveResponse(Response resp);
};

#endif // GROUPLIST_H
