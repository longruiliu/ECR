/*********************************
 * This is the test file to test whether the functions work well
 * version:0.0.0
 * test function saveUserlist(),and it work well
 * ******************************/
#include"Database.h"
#include"../src-srv/user/user.h"

std::vector<user> userList;


int main()
{
	user tmp(1,"liurui","234567",2,"This is me",1010101010);
	userList.push_back(tmp);

	Database db;
	db.saveUserlist();

	return 0;
}
