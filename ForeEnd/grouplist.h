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
    ~GroupList();

private:
    Ui::GroupList *ui;

private slots:
    void startGroupChat() ;
};

#endif // GROUPLIST_H
