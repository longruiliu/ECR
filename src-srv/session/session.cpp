/*
 * Author: HD
 * Time: 2013/3/13
 * Name: session.cpp
 */
 
#include "session.h"
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <climits>

dict sessionList_uk;
std::map<int, int> sessionList_sk;
dict::iterator iter_uk;
std::map<int, int>::iterator iter_sk;
const time_t KAI = 4;

void renewUser(int userID){
	iter_uk = sessionList_uk.find(userID);
	if(iter_uk != sessionList_uk.end())
		(iter_uk->second).SECONDS = time(NULL);
	else
		printf("Not found!\n");
}

void cleanDeadUser(){
	int deadline = time(NULL) - KAI;
	iter_uk = sessionList_uk.begin();
	while(iter_uk != sessionList_uk.end())	{
		if((iter_uk->second).SECONDS < deadline)
			deregisterSession((iter_uk->second).sessionID);
		iter_uk++;
	}
}

int registerSession(int userID, int IP){
	iter_uk = sessionList_uk.find(userID);
	if(iter_uk != sessionList_uk.end())
		deregisterSession((iter_uk->second).sessionID);
	int sessionID;
	srand(time(NULL));
	while(1){
		sessionID = rand()%ULONG_MAX;
		iter_sk = sessionList_sk.find(sessionID);
		if(iter_sk != sessionList_sk.end())
			break;
	}
	sessionList_sk[sessionID] = userID;
	
	sessionList_uk[userID].sessionID = sessionID;
	sessionList_uk[userID].IP = IP;
	sessionList_uk[userID].SECONDS = time(NULL);

	return sessionID;
}

int getUserIP(int userID){
	return sessionList_uk[userID].IP;
}

int getUserBySession(int sessionID){
	iter_sk = sessionList_sk.find(sessionID);
	if(iter_sk != sessionList_sk.end())
		return iter_sk->second;
	else{
		printf("None\n");
		return -1;
	}
}

void deregisterSession(int sessionID){
	iter_sk = sessionList_sk.find(sessionID);
	if(iter_sk != sessionList_sk.end()){
		iter_uk = sessionList_uk.find(iter_sk->first);
		sessionList_sk.erase(iter_sk);
		sessionList_uk.erase(iter_uk);
	}
	else{
		printf("There is no this sessionID\n");
		return;
	}
}
