#include"user.h"

bool user::canGroupMg()
{
    return (privilege & PRIVILEGE_MASK_GROUPMG != 0);
}


bool user::canUserMg()
{
    return (privilege & PRIVILEGE_MASK_USERMG != 0);
}

bool user::isRoot()
{
    return (privilege & PRIVILEGE_MASK_ROOT != 0);
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
