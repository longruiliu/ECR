#include<iostream>
#include<vector>
#include"groupMsg.h"

void retMsgList(const std::vector<groupMsg>& g)
{
	for(auto i = g.begin(); i!=g.end();i++)
		i->printMsg();
}

void sendNotify(int a, int b)
{
	
}
