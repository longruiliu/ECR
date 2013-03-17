#include"backRestore.h"

void backup()
{
	Database tmp();
	while (1)
	{
		tmp.saveUserlist();
		tmp.saveGrouplist();
		tmp.saveMsgMem();
		sleep(UPDATE_FRE);
	}
}

void restore(time_t delta)
{
	Database tmp();
	tmp.restoreUserlist();
	tmp.restoreGrouplist();
	tmp.restoreMsgMem(delta);
}
