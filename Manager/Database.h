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
#include"user.h"
#include"group.h"

class user;
class group;
class groupMsg;

typedef std::vector<user>::iterator ulit;
typedef std::vector<group>::iterator glit;

extern std::vector<user> userList;
extern std::vector<group> groupList;

class Database
{
	private:
		sqlite3 *_database;
	public:
                Database(const std::string&);
                bool open(const std::string&);
		std::vector<std::vector<std::string> > query(char *query);

		void saveUserlist();
		void saveGrouplist();
                void saveGroupMember();

		void restoreUserlist();
                void restoreGrouplist();
                void restoreGroupMember();

		void close();
		~Database();
};

#endif
