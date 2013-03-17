/***********************************************************************
 * Module:  user.h
 * Author:  Ronald
 * Modified: Tuesday, February 26, 2013 2:52:10 PM
 * Purpose: Declaration of the class user
 ***********************************************************************/

#if !defined(__ServerLogic_user_h)
#define __ServerLogic_user_h

#include<string>

#define PRIVILEGE_MASK_GROUPMG 0x1
#define PRIVILEGE_MASK_USERMG 0x2
#define PRIVILEGE_MASK_ROOT 0x4

struct user
{
	int userID;
	std::string userName;
	std::string pwd;
        int privilege;
        std::string info;
        bool canUserMg();
        bool canGroupMg();
        bool isRoot();

        void setUserMg(bool);
        void setGroupMg(bool);
        void setRoot(bool);
};


#endif
