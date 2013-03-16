#ifndef MANAGERWINDOW_H
#define MANAGERWINDOW_H

#include <QDialog>
#include "protocol.h"

namespace Ui {
    class managerWindow;
}

class managerWindow : public QDialog
{
    Q_OBJECT

public:
    explicit managerWindow(QWidget *parent = 0);
    ~managerWindow();

private:
    Ui::managerWindow *ui;
    void refreshData();
    std::map<int, std::string> userList;
    std::map<int, std::string> groupList;
private slots:
    /*void actionFinish(Response);
    void getUserInfoFinish(Response);
    void getMemberListFinish(Response);
    void getUserListFinish(Response);
    void getGroupListFinish(Response);*/
};

#endif // MANAGERWINDOW_H
