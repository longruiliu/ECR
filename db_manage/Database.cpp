#include"Database.h"

Database::Database()
{
	if (open() == false)
	{
		printf("Open database error!\n");
		exit(0);
	}
}

Database::~Database()
{
	close();
}

bool Database::open()
{
	if (sqlite3_open("ECR.db",&_database) == SQLITE_OK)
		return true;
	return false;
}

std::vector<std::vector<std::string> > Database::query(char* query)
{
    sqlite3_stmt *statement;
    std::vector<std::vector<std::string> > results;
 
    if(sqlite3_prepare_v2(_database, query, -1, &statement, 0) == SQLITE_OK)
    {
        int cols = sqlite3_column_count(statement);
        int result = 0;
        while(true)
        {
            result = sqlite3_step(statement);
             
            if(result == SQLITE_ROW)
            {
	        std::vector<std::string> values;
                for(int col = 0; col < cols; col++)
                {
                    values.push_back((char*)sqlite3_column_text(statement, col));
                }
                results.push_back(values);
            }
            else
            {
                break;  
            }
        }
        
        sqlite3_finalize(statement);
    }
     
    std::string error = sqlite3_errmsg(_database);
    if(error != "not an error") 
	    std::cout << query << " " << error << std::endl;
    return results; 
}

//There are the save functions

void Database::saveUserlist()
{
	char sqlBuf[1024];
	lockUserlist();
	for (std::vector<user>::iterator it = userList.begin();it < userList.end();it++)
	{
		//judge whether the user exist before
		char *sql = "select * from User where user_id=%d";
		sprintf(sqlBuf,sql,(*it).userID);
		if (!query(sqlBuf).size())
		{
			//insert the user to DB
			char *sql2 = "insert into User values(%d,'%s','%s',%d,'%s')";
			//string.c_str() is a function to change class string to c string
			sprintf(sqlBuf,sql2,(*it).userID,(*it).userName.c_str(),(*it).pwd.c_str(),(*it).previlege,(*it).info.c_str());
			query(sqlBuf);
		}
		else
		{
			//update the information of this user
			char *sql2 = "update User set u_name='%s',pwd='%s',previlege=%d,info='%s' where user_id=%d";
			sprintf(sqlBuf,sql2,(*it).userName.c_str(),(*it).pwd.c_str(),(*it).previlege,(*it).info.c_str(),(*it).userID);
			query(sqlBuf);
		}
	}
	releaseUserlist();
}	

void Database::saveGrouplist()
{
	char sqlBuf[1024];
	group *lock = new group();
	(*lock).lockGroup();
	for (std::vector<group>::iterator it = groupList.begin();it < groupList.end();it++)
	{
		//judge whether the group exist before
		char *sql = "select * from Group_list where g_name='%s'";
		sprintf(sqlBuf,sql,(*it).groupName.c_str());
		if (!query(sqlBuf).size())
		{
			//insert the group to DB
			char *sql2 = "insert into Group_list(creator_id,g_name,g_info) values(%d,'%s','%s')";
			sprintf(sqlBuf,sql2,(*it).creatorID,(*it).groupName.c_str(),(*it).groupInfo.c_str());
			query(sqlBuf);
		}
		else
		{
			//update the information of this group
			//but just group name and information can be updated
			char *sql2 = "update Group_list set g_name='%s',g_info='%s' where group_id=%d";
			sprintf(sqlBuf,sql2,(*it).groupName.c_str(),(*it).groupInfo.c_str(),(*it).groupID);
			query(sqlBuf);
		}
	}
	(*lock).releaseGroup();
	delete lock;
}

void Database::saveMsgMem()
{
	char sqlBuf[1024];
	group *lock = new group();
	(*lock).lockGroup();

	//save group messages
	for (std::vector<group>::iterator it = groupList.begin();it < groupList.end();it++)
	{
		std::vector<groupMsg> tmp = (*it).msgList;
		for (std::vector<groupMsg>::iterator p = tmp.begin();it < tmp.end();p++)
		{
			char *sql = "insert into Message(group_id,user_id,send_time,m_type,content) values(%d,%d,'%s',%d,'%s')";
			//asctime((gmtime(time_t))) is change time to normal type
			sprintf(sqlBuf,sql,(*p).targetID,(*p).srcID,asctime(gmtime((*p).postTime)),(*p).msgType,(*p).msgText.c_str());
			query(sqlBuf);
		}
	}

	//save group members
	for (std::vector<group>::iterator it = groupList.begin();it < groupList.end();it++)
	{
		std::vector<int> tmp = (*it).groupMember;
		for (std::vector<int>::iterator p = tmp.begin();it < tmp.end();p++)
		{
			char *sql2 = "insert into User_Group(user_id,group_id) values(%d,%d)";
			sprintf(sqlBuf,sql2,*p,(*it).groupID);
			query(sqlBuf);
		}
	}

	(*lock).releaseGroup();
	delete lock;
}

void Database::close()
{
    sqlite3_close(_database);  
}
