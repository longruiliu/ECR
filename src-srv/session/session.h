/*
 * Author: HD
 * Time: 2013/3/13
 * Name: session.h
 */

#ifndef __SESSION_H_
#define __SESSION_H_
#include <map>
#include <string>
typedef struct Tuple{
	int sessionID;
	int IP;
	time_t SECONDS;	
}Tuple;
typedef std::map<int, Tuple> dict;
extern dict sessionList_uk;
extern std::map<int, int> sessionList_sk;
extern dict::iterator iter_uk;
extern std::map<int, int>::iterator iter_sk;
extern const time_t KAI;

void renewUser(int userID);
void cleanDeadUser();
int registerSession(int userID, int IP);
int getUserIP(int userID);
int getUserIDBySession(int sessionID);
void deregisterSession(int sessionID);

#endif //__SESSION_H_
