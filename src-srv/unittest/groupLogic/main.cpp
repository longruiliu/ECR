#include "groupManager.h"
#include<string>
#include<iostream>
void testGroup()
{
	group a(std::string("wtf"), 0);
	a.addUser(0);
	a.addUser(1);
	a.printUserList();
	a.delUser(1);
	a.printUserList();
	std::cout << (a.isInGroup(1)?"Y":"N") << " " << (a.isInGroup(0)?"y":"n")<<std::endl;
	a.postMsg(0, std::string("What the fuck, man?"));
	a.printMsgList();
}

int main()
{
	testGroup();
	return 0;
}
