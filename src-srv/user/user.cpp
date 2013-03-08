#include "user.h"

#ifdef DEBUG
#include <iostream>
void user::printUser()
{
	cout << "  " << userID << std::endl;
}
#endif
