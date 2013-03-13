/***************************************
 * Module:Database.h
 * Author:longruiliu
 * Modified:Tuesday,March 10,2013
 * Purpose:create a clsass Database
 * *************************************/
#ifndef __DATABASE_H__
#define __DATABASE_H__

#include<vector>
#include<sqlite3.h>
#include<cstdio>
#include<iostream>
#include<time.h>
#include<cstdlib>
#include"../src-srv/user/userMgm.h"
#include"../src-srv/group/group.h"
#include"../src-srv/group/groupManager.h"

class user;
class group;
class groupMsg;

extern std::vector<user> userList;
extern std::vector<group> groupList;

class Database
{
	private:
		sqlite3 *_database;
	public:
		Database();
		bool open();
		std::vector<std::vector<std::string> > query(char *query);

		void saveUserlist();
		void saveGrouplist();
		void saveMsgMem();

		void restoreUserlist();
		void restoreGrouplist();
		void restoreMsgMem(time_t delta);


		void close();
		~Database();
};

#endif
