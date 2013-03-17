#include"user.h"
#include <QDebug>
#include "Database.h"

bool user::canGroupMg()
{
    qDebug()<< (privilege & PRIVILEGE_MASK_GROUPMG);
    return ((privilege & PRIVILEGE_MASK_GROUPMG) != 0);
}


bool user::canUserMg()
{
    qDebug()<< (privilege & PRIVILEGE_MASK_USERMG);
    return ((privilege & PRIVILEGE_MASK_USERMG) != 0);
}

bool user::isRoot()
{
    qDebug()<< (privilege & PRIVILEGE_MASK_ROOT);
    return ((privilege & PRIVILEGE_MASK_ROOT) != 0);
}

int setBit(int vo, int mask, bool newv)
{
    return (vo & ~mask) | (newv?mask:0);
}

void user::setGroupMg(bool v)
{
    privilege = setBit(privilege, PRIVILEGE_MASK_GROUPMG, v);
}
void user::setRoot(bool v)
{
    privilege = setBit(privilege, PRIVILEGE_MASK_ROOT, v);
}
void user::setUserMg(bool v)
{
    privilege = setBit(privilege, PRIVILEGE_MASK_USERMG, v);
}

std::string user::getUserName(int uid)
{
    for (ulit i  = userList.begin(); i!=userList.end(); i++)
        if (i->userID == uid)
            return i->userName;
    return std::string("");
}

bool user::hasUser(int uid)
{
    for (ulit i  = userList.begin(); i!=userList.end(); i++)
        if (i->userID == uid)
            return true;
    return false;
}
