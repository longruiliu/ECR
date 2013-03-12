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
}

bool Database::open()
{
	if (sqlite3_open("ECR.db",_database) == SQLITE_OK)
		return true;
	return false;
}

vector<vector<string> > Database::query(char* query)
{
    sqlite3_stmt *statement;
    std::vector<vector<string> > results;
 
    if(sqlite3_prepare_v2(_database, query, -1, &statement, 0) == SQLITE_OK)
    {
        int cols = sqlite3_column_count(statement);
        int result = 0;
        while(true)
        {
            result = sqlite3_step(statement);
             
            if(result == SQLITE_ROW)
            {
	        std::vector<string> values;
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
     
    string error = sqlite3_errmsg(_database);
    if(error != "not an error") 
	    std::cout << query << " " << error << endl;
     
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
		char *sql = "select * from User where id=%d";
		sprintf(sqlBuf,sql,(*it).userID);
		if (!query(sqlBuf).size())
		{
			//insert the user to DB
			char *sql2 = "insert into User values(%d,%s,%s,%d,%s)";
			sprintf(sqlBuf,sql2,(*it).userID,(*it).userName,(*it).pwd,(*it).previlege,(*it).info);
			query(sqlBuf);
		}
		else
		{
			//update the information of this user
			char *sql2 = "update User set u_name=%s,pwd=%s,previlege=%d,info=%s where user_id=%d";
			sprintf(sqlBuf,sql2,(*it).userName,(*it).pwd,(*it).previlege,(*it).info,(*it).user_ID);
			query(sqlBuf);
		}
	}
	releaseUserlist();
}	
 
void Database::close()
{
    sqlite3_close(_database);  
}

