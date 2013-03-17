#include"Database.h"
#include<QDebug>
std::vector<user> userList;
std::vector<group> groupList;
Database::Database(const std::string& filename)
{
        if (open(filename) == false)
	{
                printf("Open database error!\n");
	}
}

Database::~Database()
{
	close();
}

bool Database::open(const std::string& filename)
{
        if (sqlite3_open(filename.c_str(),&_database) == SQLITE_OK)
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
                        sprintf(sqlBuf,sql2,(*it).userID,(*it).userName.c_str(),(*it).pwd.c_str(),(*it).privilege,(*it).info.c_str());
			query(sqlBuf);
		}
		else
		{
			//update the information of this user
			char *sql2 = "update User set u_name='%s',pwd='%s',previlege=%d,info='%s' where user_id=%d";
                        sprintf(sqlBuf,sql2,(*it).userName.c_str(),(*it).pwd.c_str(),(*it).privilege,(*it).info.c_str(),(*it).userID);
			query(sqlBuf);
		}
        }
}	

void Database::saveGrouplist()
{
        char sqlBuf[1024];
	for (std::vector<group>::iterator it = groupList.begin();it < groupList.end();it++)
	{
		//judge whether the group exist before
		char *sql = "select * from Group_list where g_name='%s'";
		sprintf(sqlBuf,sql,(*it).groupName.c_str());
		if (!query(sqlBuf).size())
		{
			//insert the group to DB
                        char *sql2 = "insert into Group_list(group_id, creator_id,g_name) values(%d, %d,'%s')";
                        sprintf(sqlBuf,sql2,it->groupID, (*it).creatorID,(*it).groupName.c_str());
                        qDebug()<< sqlBuf;
			query(sqlBuf);
		}
		else
		{
			//update the information of this group
			//but just group name and information can be updated
                        char *sql2 = "update Group_list set g_name='%s' where group_id=%d";
                        sprintf(sqlBuf,sql2,(*it).groupName.c_str(),(*it).groupID);
			query(sqlBuf);
		}
        }
}


void Database::clearDatabase()
{
    query("delete from User_Group");
    query("delete from user");
    query("delete from Group_list");
}


void Database::restoreUserlist()
{
        userList.clear();
	char *sql = "select * from User";
        std::vector<std::vector<std::string> > results = query(sql);
        for (std::vector<std::vector<std::string> >::iterator it = results.begin();it < results.end();it++ )
	{
		user tmp;
		tmp.userID = atoi(((*it).at(0)).c_str()); //change class string to int
		tmp.userName = ((*it).at(1)).c_str();
		tmp.pwd = ((*it).at(2)).c_str();
                tmp.privilege =  atoi(((*it).at(3)).c_str());
		tmp.info = ((*it).at(4)).c_str();
		userList.push_back(tmp);
        }
}

void Database::restoreGrouplist()
{
    groupList.clear();
	char *sql = "select * from Group_list";
        std::vector<std::vector<std::string> > results = query(sql);

        for (std::vector<std::vector<std::string> >::iterator it = results.begin();it < results.end();it++ )
	{
		group tmp;
		tmp.groupID = atoi(((*it).at(0)).c_str()); //change class string to int
		tmp.creatorID = atoi(((*it).at(1)).c_str());
                tmp.groupName = ((*it).at(2)).c_str();
		groupList.push_back(tmp);
        }
}

void Database::saveGroupMember()
{
        char sqlBuf[1024];
        //save group members
        for (std::vector<group>::iterator it = groupList.begin();it < groupList.end();it++)
        {
                std::vector<int> tmp = (*it).groupMember;
                for (std::vector<int>::iterator p = tmp.begin(); p != tmp.end();p++)
                {
                        char *sql2 = "insert into User_Group(user_id,group_id) values(%d,%d)";
                        sprintf(sqlBuf,sql2,*p,(*it).groupID);
                        query(sqlBuf);
                }
        }
}

void Database::restoreGroupMember()
{

        char *sql2 = "select * from User_Group";
        std::vector<std::vector<std::string> > results2 = query(sql2);

        for (std::vector<std::vector<std::string> >::iterator it = results2.begin();it < results2.end();it++ )
        {
                for (std::vector<group>::iterator p = groupList.begin();p < groupList.end();p++)
                        if ((*p).groupID == atoi((*it).at(2).c_str()))
                                ((*p).groupMember).push_back(atoi((*it).at(1).c_str()));
        }
}

void Database::close()
{
    sqlite3_close(_database);  
}
