/***********************************************************************
 * Module:  user.h
 * Author:  Ronald
 * Modified: Tuesday, February 26, 2013 2:52:10 PM
 * Purpose: Declaration of the class user
 ***********************************************************************/

#if !defined(__ServerLogic_user_h)
#define __ServerLogic_user_h

class user
{
public:
	int userID;
	int privMask;
	int IP;
#ifdef DEBUG
	void printUser();
#endif
};

user& findUser(int userID);

#endif
