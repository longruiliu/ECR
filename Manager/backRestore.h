#ifndef __BACKRESTORE_H__
#define __BACKRESTORE_H__
#include"Database.h"i
#include<unistd.h>

#define UPDATE_FRE  10000

class Database;

void backup();
void restore(time_t delta);


#endif
