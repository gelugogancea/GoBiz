#include "include/sqlfunction.h"
extern int SQLExec(int,MYSQL*,char*,SQL_EXEC_OPTIONS);
void F_SQLInsertPartenerGeneral(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *uniqreg=NULL;
	char *commreg=NULL;
	char *codpart=NULL;
	char *partname=NULL;
	char *accpart=NULL;
	char *accpartincome=NULL;
	char *accpartcost=NULL;
	char *islogcenter=NULL;
	char *parttype=NULL;
	char *partstatus=NULL;
	char *soldinitdebit=NULL;
	char *soldinitcredit=NULL;
	char *vfrom=NULL;
	char *vto=NULL;
	char *muser=NULL;

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			uniqreg=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			commreg=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			codpart=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			partname=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			accpart=(char*)listpointer->MyItem;
			if(strncmp(accpart,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(accpart,(const char*)"");
			}
		}
		else if(enumargv==5)
		{
			accpartincome=(char*)listpointer->MyItem;
			if(strncmp(accpartincome,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(accpartincome,(const char*)"");
			}
		}
		else if(enumargv==6)
		{
			accpartcost=(char*)listpointer->MyItem;
			if(strncmp(accpartcost,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(accpartcost,(const char*)"");
			}
		}
		else if(enumargv==7)
		{
			islogcenter=(char*)listpointer->MyItem;
		}
		else if(enumargv==8)
		{
			parttype=(char*)listpointer->MyItem;
		}
		else if(enumargv==9)
		{
			partstatus=(char*)listpointer->MyItem;
		}
		else if(enumargv==10)
		{
			soldinitdebit=(char*)listpointer->MyItem;
		}
		else if(enumargv==11)
		{
			soldinitcredit=(char*)listpointer->MyItem;
		}
		else if(enumargv==12)
		{
			vfrom=(char*)listpointer->MyItem;
		}
		else if(enumargv==13)
		{
			vto=(char*)listpointer->MyItem;
		}
		else if(enumargv==14)
		{
			muser=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;//urmatorul pointer 	
	}	
	sprintf(ExecStatement,"insert into part_general (UNIQREG,COMMREG,CODPART,PARTNAME,PARTACC,PARTACCINCOME,PARTACCCOST,IsLogisticCenter,PARTTYPE,STATUSPART,SOLD_INIT_IN,SOLD_INIT_OUT,ValidFrom,ValidTo,Created,CreatedBy) VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s',%s,%s,'%s','%s',NOW(),'%s');",uniqreg,commreg,codpart,partname,accpart,accpartincome,accpartcost,islogcenter,parttype,partstatus,soldinitdebit,soldinitcredit,vfrom,vto,muser); 

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	uniqreg=NULL;
	commreg=NULL;
	codpart=NULL;
	partname=NULL;
	accpart=NULL;
	accpartincome=NULL;
	accpartcost=NULL;
	islogcenter=NULL;
	parttype=NULL;
	partstatus=NULL;
	soldinitdebit=NULL;
	soldinitcredit=NULL;
	vfrom=NULL;
	vto=NULL;
	muser=NULL;

}
void F_SQLGetPartenerGeneral(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
		
	int enumargv=0;
	char *option=NULL;
	char *margv=NULL;
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			option=(char*)listpointer->MyItem;
		}
		else if(enumargv==1)
		{
			margv=(char*)listpointer->MyItem;
		}
		
		listpointer=listpointer -> NextArgv;
	}
     	if(strncmp(option,"NONE",strlen("NONE"))==0)	
	{	
		sprintf(ExecStatement,"select * from part_general where NOW() between ValidFrom and ValidTo;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select * from part_general where UNIQREG='%s' and NOW() between ValidFrom and ValidTo;",margv);
	}
	else if (strncmp(option,"LIKE",strlen("LIKE"))==0)	
	{
		sprintf(ExecStatement,"select * from part_general where PARTNAME LIKE '%s%%' and NOW() between ValidFrom and ValidTo;",margv);
	
	}
	else if (strncmp(option,"LH",strlen("LH"))==0)	
	{
		sprintf(ExecStatement,"select UNIQREG,PARTNAME from part_general where PARTTYPE='%s' and STATUSPART='FREE' and NOW() between ValidFrom and ValidTo;",margv);
	
	}
	else if (strncmp(option,"LCMB",strlen("LCMB"))==0)	
	{
		sprintf(ExecStatement,"select UNIQREG,PARTNAME from part_general where PARTTYPE='INOUT' and STATUSPART='FREE' and NOW() between ValidFrom and ValidTo;");
	
	}
	else if (strncmp(option,"LALL",strlen("LALL"))==0)
	{
		sprintf(ExecStatement,"select UNIQREG,CONCAT(PARTNAME,' - ','TYPE : ',PARTTYPE) from part_general where STATUSPART='FREE' and NOW() between ValidFrom and ValidTo;");

	}

	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLUpdatePartenerGeneral(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *uniqreg=NULL;
	char *commreg=NULL;
	char *codpart=NULL;
	char *partname=NULL;
	char *accpart=NULL;
	char *accpartincome=NULL;
	char *accpartcost=NULL;
	char *islogcenter=NULL;
	char *parttype=NULL;
	char *partstatus=NULL;
	char *soldinitdebit=NULL;
	char *soldinitcredit=NULL;
	char *vfrom=NULL;
	char *vto=NULL;
	char *muser=NULL;
	char *delete=NULL;

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			uniqreg=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			commreg=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			codpart=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			partname=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			accpart=(char*)listpointer->MyItem;
			if(strncmp(accpart,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(accpart,(const char*)"");
			}
		}
		else if(enumargv==5)
		{
			accpartincome=(char*)listpointer->MyItem;
			if(strncmp(accpartincome,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(accpartincome,(const char*)"");
			}
		}
		else if(enumargv==6)
		{
			accpartcost=(char*)listpointer->MyItem;
			if(strncmp(accpartcost,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(accpartcost,(const char*)"");
			}
		}
		else if(enumargv==7)
		{
			islogcenter=(char*)listpointer->MyItem;
		}
		else if(enumargv==8)
		{
			parttype=(char*)listpointer->MyItem;
		}
		else if(enumargv==9)
		{
			partstatus=(char*)listpointer->MyItem;
		}
		else if(enumargv==10)
		{
			soldinitdebit=(char*)listpointer->MyItem;
		}
		else if(enumargv==11)
		{
			soldinitcredit=(char*)listpointer->MyItem;
		}
		else if(enumargv==12)
		{
			vfrom=(char*)listpointer->MyItem;
		}
		else if(enumargv==13)
		{
			vto=(char*)listpointer->MyItem;
		}
		else if(enumargv==14)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if(enumargv==15)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv; 	
	}	
	
	if(strncmp(delete,"0",strlen("0"))==0)
	{	
		sprintf(ExecStatement,"delete from part_general where UNIQREG='%s';",uniqreg);
	}
	else
	{
		sprintf(ExecStatement,"update part_general SET COMMREG='%s',CODPART='%s',PARTNAME='%s',PARTACC='%s',PARTACCINCOME='%s',PARTACCCOST='%s',IsLogisticCenter='%s',PARTTYPE='%s',STATUSPART='%s',SOLD_INIT_IN=%s,SOLD_INIT_OUT=%s,ValidFrom='%s',ValidTo='%s',LastUpdate=NOW(),LastUpdateBy='%s' where UNIQREG='%s';",commreg,codpart,partname,accpart,accpartincome,accpartcost,islogcenter,parttype,partstatus,soldinitdebit,soldinitcredit,vfrom,vto,muser,uniqreg);
	}
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	uniqreg=NULL;
	commreg=NULL;
	codpart=NULL;
	partname=NULL;
	accpart=NULL;
	accpartincome=NULL;
	accpartcost=NULL;
	islogcenter=NULL;
	parttype=NULL;
	partstatus=NULL;
	soldinitdebit=NULL;
	soldinitcredit=NULL;
	vfrom=NULL;
	vto=NULL;
	muser=NULL;
	delete=NULL;
}
void F_SQLInsertPartenerBank(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *uniqreg=NULL;
	char *iban=NULL;
	char *name=NULL;
	char *symcur=NULL;
	
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			uniqreg=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			iban=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			name=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			symcur=(char*)listpointer->MyItem;
			if(strncmp(symcur,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(symcur,(const char*)"");
			}
		}
		
		listpointer=listpointer -> NextArgv;	
	}	
	sprintf(ExecStatement,"insert into part_bank(UNIQREG,IBAN,BANKNAME,SYM_CUR) VALUES('%s','%s','%s','%s');",uniqreg,iban,name,symcur); 

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	uniqreg=NULL;
	iban=NULL;
	name=NULL;
	symcur=NULL;

}
void F_SQLGetPartenerBank(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
		
	int enumargv=0;
	char *option=NULL;
	char *margv=NULL;
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			option=(char*)listpointer->MyItem;
		}
		else if(enumargv==1)
		{
			margv=(char*)listpointer->MyItem;
		}
		
		listpointer=listpointer -> NextArgv; 
	}
     	if(strncmp(option,"NONE",strlen("NONE"))==0)	
	{	
		sprintf(ExecStatement,"select IBAN,BANKNAME,SYM_CUR from part_bank;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select IBAN,BANKNAME,SYM_CUR from part_bank where UNIQREG='%s';",margv);
	}

	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLUpdatePartenerBank(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *uniqreg=NULL;
	char *iban=NULL;
	char *name=NULL;
	char *symcur=NULL;
	char *delete=NULL;	

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			uniqreg=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			iban=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			name=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			symcur=(char*)listpointer->MyItem;
			if(strncmp(symcur,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(symcur,(const char*)"");
			}
		}
		else if(enumargv==4)
		{
			delete=(char*)listpointer->MyItem;
		}
		
		listpointer=listpointer -> NextArgv;	
	}	
	if(strncmp(delete,"0",strlen("0"))==0)
	{	
		sprintf(ExecStatement,"delete from part_bank where UNIQREG='%s' and IBAN='%s';",uniqreg,iban);
	}
	else
	{
		sprintf(ExecStatement,"update part_bank SET BANKNAME='%s',SYM_CUR='%s' where UNIQREG='%s' and IBAN='%s';",name,symcur,uniqreg,iban); 
	}
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	uniqreg=NULL;
	iban=NULL;
	name=NULL;
	symcur=NULL;
	delete=NULL;

}
void F_SQLInsertPartenerAddr(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *uniqreg=NULL;
	char *addr=NULL;
	char *zip=NULL;
	char *city=NULL;
	char *region=NULL;
	char *country=NULL;
	char *IsHQ=NULL;
	
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			uniqreg=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			addr=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			zip=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			city=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==4)
		{
			region=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==5)
		{
			country=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==6)
		{
			IsHQ=(char*)listpointer->MyItem;
			
		}
		listpointer=listpointer -> NextArgv;	
	}	
	sprintf(ExecStatement,"insert into part_address(UNIQREG,ADDRESS,ZIP,CITY,REGION,COUNTRY,IsHeadQuarter) VALUES('%s','%s','%s','%s','%s','%s','%s');",uniqreg,addr,zip,city,region,country,IsHQ); 

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	uniqreg=NULL;
	addr=NULL;
	zip=NULL;
	city=NULL;
	region=NULL;
	country=NULL;
	IsHQ=NULL;

}
void F_SQLGetPartenerAddr(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
		
	int enumargv=0;
	char *option=NULL;
	char *margv=NULL;
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			option=(char*)listpointer->MyItem;
		}
		else if(enumargv==1)
		{
			margv=(char*)listpointer->MyItem;
		}
		
		listpointer=listpointer -> NextArgv;
	}
     	if(strncmp(option,"NONE",strlen("NONE"))==0)	
	{	
		sprintf(ExecStatement,"select ADDRESS,ZIP,CITY,REGION,COUNTRY,IsHeadQuarter from part_address;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select ADDRESS,ZIP,CITY,REGION,COUNTRY,IsHeadQuarter from part_address where UNIQREG='%s';",margv);
	}
	
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLUpdatetPartenerAddr(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *uniqreg=NULL;
	char *addr=NULL;
	char *zip=NULL;
	char *city=NULL;
	char *region=NULL;
	char *country=NULL;
	char *IsHQ=NULL;
	char *delete=NULL;
	
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			uniqreg=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			addr=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			zip=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			city=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==4)
		{
			region=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==5)
		{
			country=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==6)
		{
			IsHQ=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==7)
		{
			delete=(char*)listpointer->MyItem;
			
		}
		listpointer=listpointer -> NextArgv;	
	}	
	if(strncmp(delete,"0",strlen("0"))==0)
	{	
		sprintf(ExecStatement,"delete from part_address where UNIQREG='%s' and ADDRESS='%s';",uniqreg,addr);
	}
	else
	{
		sprintf(ExecStatement,"update part_address SET ZIP='%s',CITY='%s',REGION='%s',COUNTRY='%s',IsHeadQuarter='%s' where UNIQREG='%s' and ADDRESS='%s';",zip,city,region,country,IsHQ,uniqreg,addr); 
	}
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	uniqreg=NULL;
	addr=NULL;
	zip=NULL;
	city=NULL;
	region=NULL;
	country=NULL;
	IsHQ=NULL;
	delete=NULL;

}
void F_SQLInsertPartenerContact(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *uniqreg=NULL;
	char *name=NULL;
	char *sname=NULL;
	char *phone=NULL;
	char *e_mail=NULL;
	
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			uniqreg=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			name=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			sname=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			phone=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==4)
		{
			e_mail=(char*)listpointer->MyItem;
			
		}
		
		listpointer=listpointer -> NextArgv;//urmatorul pointer 	
	}	
	sprintf(ExecStatement,"insert into part_contact(UNIQREG,CNAME,CSURNAME,PHONE,E_MAIL) VALUES('%s','%s','%s','%s','%s');",uniqreg,name,sname,phone,e_mail); 

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	uniqreg=NULL;
	name=NULL;
	sname=NULL;
	phone=NULL;
	e_mail=NULL;

}
void F_SQLGetPartenerContact(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
		
	int enumargv=0;
	char *option=NULL;
	char *margv=NULL;
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			option=(char*)listpointer->MyItem;
		}
		else if(enumargv==1)
		{
			margv=(char*)listpointer->MyItem;
		}
		
		listpointer=listpointer -> NextArgv; 
	}
     	if(strncmp(option,"NONE",strlen("NONE"))==0)	
	{	
		sprintf(ExecStatement,"select IDREC,CNAME,CSURNAME,PHONE,E_MAIL from part_contact;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select IDREC,CNAME,CSURNAME,PHONE,E_MAIL from part_contact where UNIQREG='%s';",margv);
	}
	
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLUpdatePartenerContact(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *idrec=NULL;
	char *name=NULL;
	char *sname=NULL;
	char *phone=NULL;
	char *e_mail=NULL;
	char *delete=NULL;
	
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			idrec=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			name=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			sname=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			phone=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==4)
		{
			e_mail=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==5)
		{
			delete=(char*)listpointer->MyItem;
			
		}
		listpointer=listpointer -> NextArgv;	
	}	
	if(strncmp(delete,"0",strlen("0"))==0)
	{	
		sprintf(ExecStatement,"delete from part_contact where IDREC=%s;",idrec);
	}
	else
	{
		sprintf(ExecStatement,"update part_contact SET CNAME='%s',CSURNAME='%s',PHONE='%s',E_MAIL='%s' where IDREC=%s;",name,sname,phone,e_mail,idrec); 
	}
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	idrec=NULL;
	name=NULL;
	sname=NULL;
	phone=NULL;
	e_mail=NULL;
	delete=NULL;
}
