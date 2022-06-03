#include "include/sqlfunction.h"

int ExecStoreProc(MYSQL* myData,char* myQuery){
	
	MYSQL_RES *mRes;
	unsigned long zz=0;	
	
	if((mysql_real_query(myData,myQuery,strlen(myQuery)))<0)
	{
		return(-1);
	}
	do{
		mRes=mysql_store_result(myData);
		if(mRes) //exista rezultate deci se pot extrage
		{
			
			mysql_free_result(mRes);
		}
		else	
		{
			if(mysql_field_count(myData)==0)
			{
				zz=mysql_affected_rows(myData);
			}
			else
			{
				
			}	
		}
	} while (!mysql_next_result(myData));
	
	return 0;
}
