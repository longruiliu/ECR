/*
 *	Author: HD
 *	Name: logic.h
 *	Time: 2013/3/11
 */

#ifndef _LOGIC_H_
#define _LOGIC_H_

/* 
 *All the function's return value need to be talk 
 *
 */


Request *req = new Requst();
Response *res = new Responese();

/* Params  */
int val = 0;
std::string type = "";
std::string method = "";

int ret;	
// reqular
int login(string userID,string passwd);

int logout();	

int sendmsg(std::string userID, std::string Text)

int getuserlist(std::string userID);

int getuserinfo(std::string userID);

int addUser(std::string username, std::string passwd,UserInfo userinfo);

int modify(std::string userID, std::string newName, std::string newPhone, UserInfo userinfo);

int delUser(std:: string userID);

//int fetchmsg(timestamp);


// group 
int addGroup(std::string groupName); 

int delGroup(std::string groupName);

int sendGmsg(std::string groupID, std::string Text);

int joinreq(std::string userID, std::string groupID, std::string Text);

int quitreq(std::string userID, std::string groupID);

int userlistGroup(std::string groupID);

int redmsg(std::string groupID, std::string message);

//int fetGchmsg(std::string groupID, timestamp);
#endif //_LOGIC_H_
