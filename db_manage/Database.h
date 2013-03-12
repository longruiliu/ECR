/***************************************
 * Module:Database.h
 * Author:longruiliu
 * Modified:Tuesday,March 10,2013
 * Purpose:create a clsass Database
 * *************************************/
#ifndef __DATABASE_H__
#define __DATABASE_H__

#include<string>
#include<vector>
#include<sqlite3.h>
#include<cstdio>
#include<iostream>
#include<cstdlib>
#include"../src-srv/user/userMgm.h"
#include"../src-srv/group/group.h"
#include"../src-srv/group/groupManager.h"


class Database
{
	private:
		sqlite3 *_database;
	public:
		Database();
		bool open()
		std::vector<vector<string>> query(char *query)

		void saveUserlist();
		void saveGrouplist();
		void saveMsglist();
		void saveGroupmember();


		void close();
		～Database();
};

#endif
