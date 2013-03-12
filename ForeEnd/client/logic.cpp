/*
 *	Author: HD
 *	Name: logic.cpp
 *	Time: 2013/3/11
 */

#include "logic.h"
#include "../protol/protocol.h"


/* All the function's return value need to be talk */

int login(string userID, string passwd){
	val = 0;
	type = "regular";
	method = "login";	

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	/* Params must be ordered as protocol defines */
	req->addParams(userID);
	req->addParams(passwd); 

	ret = sendRequest(req, res);
	/* 
	 * if response ok, show on UI -- userlist | grouplist | userinfo  
	 * res->
	 * int getUserInfo(UserInfo &) const;
	 * int getSessionID() const;
	 * int getUserList(UserList &) const;
	 * int getGroupName(std::string &) const;
	 * int getGroupID() const;
	 *
	 */

	return ret;
}

int logout(){
	val = 0;
	type = "regular";
	method = "logout";	

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	ret = sendRequest(req, res);

	return ret; 
}

int sendmsg(std::string userID, std::string Text){
	val = 0;
	type = "regular";
	method = "sendmsg";	

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(userID);
	req->addParams(Text); 

	ret = sendRequest(req, res);

	return ret; 	
}

int getuserlist(std::string userID){
	val = 0;
	type = "regular";
	method = "userlist";

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(userID);

	ret = sendRequest(req, res);

	return ret;
}

int getuserinfo(std::string userID){
	val = 0;
	type = "regular";
	method = "userinfo";

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(userID);

	ret = sendRequest(req, res);

	return ret;
}

int addUser(std::string username, std::string passwd, UserInfo userinfo){
	val = 0;
	type = "regular";
	method = "add";

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(username);
	req->addParams(passwd);
	req->addParams(userinfo);

	ret = sendRequest(req, res);

	return ret;
}

int modify(std::string userID, std::string newName, std::string newPhone, UserInfo userinfo){
	val = 0;
	type = "regular";
	method = "modify";

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(userID);
	req->addParams(newName);
	req->addParams(newPhone);
	req->addParams(userinfo);

	ret = sendRequest(req, res);

	return ret;
}


int delUser(std::string userID){
	val = 0;
	type = "regular";
	method = "del";

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(userID);

	ret = sendRequst(req, res);
	
	return ret;
}

/*
int fetchmsg(timestamp){
	val = 0;
	type = "regular";
	method = "fetchmsg";

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(timestamp);

	ret = sendRequest(req, res);

	return ret;
}
*/	

int addGroup(std::string groupName){
	val = 0;
	type = "group";
	method = "add";

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(groupName);

	ret = sendRequest(req, res);

	return ret;
}

int delGroup(std::string groupName){
	val = 0;
	type = "group";
	method = "del";

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(groupName);

	ret = sendRequest(req, res);

	return ret;
}

int sendGmsg(std::string groupID, std::string Text){
	val = 0;
	type = "group";
	method = "sendmsg";

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(req, res);

	ret = sendRequst(req, res);

	return ret;
}

int joinreq(std::string userID, std::string groupID, std::string Text){
	val = 0;
	type = "group";
	method = "joinreq";

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(userID);
	req->addParams(groupID);
	req->addParams(Text);

	ret = sendRequest(req, res);

	return ret;
}

int quitreq(std::string userID, std::string groupID){
	val = 0;
	type = "group";
	method = "quitreq";

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(userID);
	req->addParams(groupID);

	ret = sendRequest(req, res);

	return ret;
}

int userlistGroup(std::string groupID){
	val = 0;
	type = "group";
	method = "userlist";

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(groupID);

	ret = sendRequest(req, res);

	return ret;
}
int redmsg(std::string groupID, std::string message){
	val = 0;
	type = "group";
	method = "redmsg";

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(groupID);
	req->addParams(message);

	ret = sendRequest(req, res);

	return ret;
}

/*
 int fetGchmsg(std::string groupID, timestamp){
	val = 0;
	type = "group";
	method = "fechmsg";

	req->setSessionID(val);
	req->setType(type);
	req->setMethod(method);

	req->addParams(groupID);
	req->addParams(timestamp);

	ret = sendRequest(req, res);

	return ret;
}
*/

