#ifndef _USERMGM_H_
#define _USERMGM_H_ 
#include<vector>
#include<string>

void lockUserlist();
void releaseUserlist();
std::vector<user> userList;

#endif /* _USERMGM_H_ */
