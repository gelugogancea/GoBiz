#include "include/sqlfunction.h"
extern int SQLExec(int,MYSQL*,char*,SQL_EXEC_OPTIONS);
void F_SQLInsertHeaderAccScheme(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *name=NULL;	
	char *symbol=NULL;
	char *scop=NULL;
	char *sgroup=NULL;
	char *ngroup=NULL;
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
			name=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			symbol=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			scop=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			sgroup=(char*)listpointer->MyItem;
			if(strncmp(sgroup,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(sgroup,(const char*)"");
			}
		}
		else if(enumargv==4)
		{
			ngroup=(char*)listpointer->MyItem;
			if(strncmp(ngroup,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(ngroup,(const char*)"");
			}
		}
		else if(enumargv==5)
		{
			vfrom=(char*)listpointer->MyItem;
		}
		else if(enumargv==6)
		{
			vto=(char*)listpointer->MyItem;
		}
		else if(enumargv==7)
		{
			muser=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;//urmatorul pointer 	
	}	
	
	sprintf(ExecStatement,"insert into ac_scheme_h_account (SCHEME_NAME,SCHEME_SYMBOL,PURPOSE,S_GROUP,N_GROUP,ValidFrom,ValidTo,Created,CreatedBy) VALUES('%s','%s','%s','%s','%s','%s','%s',NOW(),'%s');",name,symbol,scop,sgroup,ngroup,vfrom,vto,muser); 

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	name=NULL;	
	symbol=NULL;
	scop=NULL;
	sgroup=NULL;
	ngroup=NULL;
	vfrom=NULL;
	vto=NULL;
	muser=NULL;
}
void F_SQLGetHeaderSchAccount(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select * from ac_scheme_h_account order by IDHS;");
	}
	else if (strncmp(option,"=",strlen("="))==0)
	{
		sprintf(ExecStatement,"select * from ac_scheme_h_account where SCHEME_SYMBOL='%s' and NOW() between ValidFrom and ValidTo order by IDHS;",margv);
	}
	else if (strncmp(option,"LIKE",strlen("LIKE"))==0)	
	{
		sprintf(ExecStatement,"select * from ac_scheme_h_account where SCHEME_NAME LIKE '%s%%' and NOW() between ValidFrom and ValidTo order by IDHS;",margv);
	}
	
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLUpdateHeaderAccScheme(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *idscheme=NULL;
	char *name=NULL;	
	char *symbol=NULL;
	char *scop=NULL;
	char *sgroup=NULL;
	char *ngroup=NULL;
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
			idscheme=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			name=(char*)listpointer->MyItem;
		}	
		else if(enumargv==2)
		{
			symbol=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			scop=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			sgroup=(char*)listpointer->MyItem;
			if(strncmp(sgroup,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(sgroup,(const char*)"");
			}
		}
		else if(enumargv==5)
		{
			ngroup=(char*)listpointer->MyItem;
			if(strncmp(ngroup,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(ngroup,(const char*)"");
			}
		}
		else if(enumargv==6)
		{
			vfrom=(char*)listpointer->MyItem;
		}
		else if(enumargv==7)
		{
			vto=(char*)listpointer->MyItem;
		}
		else if(enumargv==8)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if(enumargv==9)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;//urmatorul pointer 	
	}	
	if(strncmp(delete,"0",strlen("0"))==0)
	{
		sprintf(ExecStatement,"delete from ac_scheme_h_account where IDHS=%s;",idscheme); 
	}
	else
	{
		sprintf(ExecStatement,"update ac_scheme_h_account SET SCHEME_NAME='%s',SCHEME_SYMBOL='%s',PURPOSE='%s',S_GROUP='%s',N_GROUP='%s',ValidFrom='%s',ValidTo='%s',LastUpdate=NOW(),LastUpdateBy='%s' where IDHS=%s;",name,symbol,scop,sgroup,ngroup,vfrom,vto,muser,idscheme); 
	}
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	idscheme=NULL;
	name=NULL;	
	symbol=NULL;
	scop=NULL;
	sgroup=NULL;
	ngroup=NULL;
	vfrom=NULL;
	vto=NULL;
	muser=NULL;
	delete=NULL;
}

void F_SQLInsertAccScheme(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *symscheme=NULL;
	char *descracc=NULL;	
	char *operno=NULL;
	char *cont=NULL;
	char *debit=NULL;
	char *credit=NULL;
	char *myval=NULL;
	char *muser=NULL;
	
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			symscheme=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			descracc=(char*)listpointer->MyItem;
			if(strncmp(descracc,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(descracc,(const char*)"");
			}
		}
		else if(enumargv==2)
		{
			operno=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			cont=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			debit=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==5)
		{
			credit=(char*)listpointer->MyItem;
		
		}
		else if(enumargv==6)
		{
			myval=(char*)listpointer->MyItem;
		}
		else if(enumargv==7)
		{
			muser=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	
	sprintf(ExecStatement,"insert into ac_scheme_account (SCHEME_SYMBOL,DescriptionACCNote,OperationNo,SYM_COUNT,Debit,Credit,MyFormula,Created,CreatedBy) VALUES('%s','%s','%s','%s','%s','%s','%s',NOW(),'%s');",symscheme,descracc,operno,cont,debit,credit,myval,muser); 

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	symscheme=NULL;
	descracc=NULL;	
	operno=NULL;
	cont=NULL;
	debit=NULL;
	credit=NULL;
	myval=NULL;
	muser=NULL;
	
}

void F_SQLGetSchAccount(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select * from ac_scheme_account order by IDScheme;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select * from ac_scheme_account where SCHEME_SYMBOL='%s' order by IDScheme;",margv);
	}
	else if (strncmp(option,"LIKE",strlen("LIKE"))==0)	
	{
		sprintf(ExecStatement,"select * from ac_scheme_account where SCHEME_SYMBOL LIKE '%s%%' order by IDScheme;",margv);
	}
	
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLUpdateAccScheme(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *iddb=NULL;
	char *symscheme=NULL;
	char *descracc=NULL;	
	char *operno=NULL;
	char *cont=NULL;
	char *debit=NULL;
	char *credit=NULL;
	char *myval=NULL;
	char *muser=NULL;
	char *delete=NULL;

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			iddb=(char*)listpointer->MyItem;
		}
		else if(enumargv==1)
		{
			symscheme=(char*)listpointer->MyItem;
		}	
		else if(enumargv==2)
		{
			descracc=(char*)listpointer->MyItem;
			if(strncmp(descracc,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(descracc,(const char*)"0");
			}
		}
		else if(enumargv==3)
		{
			operno=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			cont=(char*)listpointer->MyItem;
		}
		else if(enumargv==5)
		{
			debit=(char*)listpointer->MyItem;
			if(strncmp(debit,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(debit,(const char*)"0");
			}
		}
		else if(enumargv==6)
		{
			credit=(char*)listpointer->MyItem;
			if(strncmp(credit,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(credit,(const char*)"0");
			}
		}
		else if(enumargv==7)
		{
			myval=(char*)listpointer->MyItem;
		}
		else if(enumargv==8)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if(enumargv==9)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv; 	
	}	
	if(strncmp(delete,"0",strlen("0"))==0)
	{
		sprintf(ExecStatement,"delete from ac_scheme_account where IDScheme=%s;",iddb); 
	}
	else
	{
		sprintf(ExecStatement,"update ac_scheme_account SET  SCHEME_SYMBOL='%s',DescriptionACCNote='%s',OperationNo=%s,SYM_COUNT='%s',Debit='%s',Credit='%s',MyFormula='%s',LastUpdate=NOW(),LastUpdateBy='%s' where IDScheme=%s; ",symscheme,descracc,operno,cont,debit,credit,myval,muser,iddb); 
	}
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	iddb=NULL;
	symscheme=NULL;
	descracc=NULL;	
	operno=NULL;
	cont=NULL;
	debit=NULL;
	credit=NULL;
	myval=NULL;
	muser=NULL;
	delete=NULL;

}
void F_SQLGetResponsablePerson(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select ID,RealName,RealSurname from sys_user order by ID;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select ID,RealName,RealSurname from sys_user where ID='%s' order by ID;",margv);
	}
	else if (strncmp(option,"LIKE",strlen("LIKE"))==0)	
	{
		sprintf(ExecStatement,"select ID,RealName,RealSurname from sys_user where RealName LIKE '%s%%' order by ID;",margv);
	}
	
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLInsertWH(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *whname=NULL;
	char *whcode=NULL;
	char *idresp=NULL;
	char *logcenter=NULL;
	char *whacc=NULL;
	char *costacc=NULL;
	char *incomeacc=NULL;
	char *isresponsable=NULL;
	char *isableforsale=NULL;
	char *serialdoc=NULL;
	char *invoicemin=NULL;
	char *invoicemax=NULL;
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
			whname=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			whcode=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			idresp=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			logcenter=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			whacc=(char*)listpointer->MyItem;
			if(strncmp(whacc,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(whacc,(const char*)"0");
			}
		}
		else if(enumargv==5)
		{
			costacc=(char*)listpointer->MyItem;
			if(strncmp(costacc,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(costacc,(const char*)"0");
			}
		}
		else if(enumargv==6)
		{
			incomeacc=(char*)listpointer->MyItem;
			if(strncmp(incomeacc,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(incomeacc,(const char*)"0");
			}
		}
		else if(enumargv==7)
		{
			isresponsable=(char*)listpointer->MyItem;
		}
		else if(enumargv==8)
		{
			isableforsale=(char*)listpointer->MyItem;
		}
		else if(enumargv==9)
		{
			serialdoc=(char*)listpointer->MyItem;
			if(strncmp(serialdoc,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(serialdoc,(const char*)"");
			}
		}
		else if(enumargv==10)
		{
			invoicemin=(char*)listpointer->MyItem;
		}
		else if(enumargv==11)
		{
			invoicemax=(char*)listpointer->MyItem;
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
	
	sprintf(ExecStatement,"insert into wh_warehouse (WHNAME,WHCODE,IDRESPONSABLE,CodeLC,WH_ACCOUNT,COST_ACCOUNT,INCOMMING_ACCOUNT,WorkOnlyResponsable,IsAbleToSale,InvoiceSerial,InvoiceNoMIN,InvoiceNoMAX,ValidFrom,ValidTo,Created,CreatedBy) VALUES('%s','%s',%s,'%s','%s','%s','%s','%s','%s','%s',%s,%s,'%s','%s',NOW(),'%s');",whname,whcode,idresp,logcenter,whacc,costacc,incomeacc,isresponsable,isableforsale,serialdoc,invoicemin,invoicemax,vfrom,vto,muser); 
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	whname=NULL;
	whcode=NULL;
	idresp=NULL;
	logcenter=NULL;
	whacc=NULL;
	costacc=NULL;
	incomeacc=NULL;
	isresponsable=NULL;
	isableforsale=NULL;
	serialdoc=NULL;
	invoicemin=NULL;
	invoicemax=NULL;
	vfrom=NULL;
	vto=NULL;
	muser=NULL;
}
void F_SQLGetWH(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
			sprintf(ExecStatement,"select wh_warehouse.IDWH,wh_warehouse.WHNAME,wh_warehouse.WHCODE,CONCAT(sys_user.ID,' - ',sys_user.RealName,'  ',sys_user.RealSurname),wh_warehouse.CodeLC,wh_warehouse.WH_ACCOUNT,wh_warehouse.COST_ACCOUNT,wh_warehouse.INCOMMING_ACCOUNT,wh_warehouse.WorkOnlyResponsable,wh_warehouse.IsAbleToSale,wh_warehouse.InvoiceSerial,wh_warehouse.InvoiceNoMIN,wh_warehouse.InvoiceNoMAx,wh_warehouse.ValidFrom,wh_warehouse.ValidTo,wh_warehouse.Created,wh_warehouse.CreatedBy,wh_warehouse.LastUpdate,wh_warehouse.LastUpdateBy from wh_warehouse,sys_user where wh_warehouse.IDRESPONSABLE=sys_user.ID order by wh_warehouse.IDWH;");
		}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select wh_warehouse.IDWH,wh_warehouse.WHNAME,wh_warehouse.WHCODE,CONCAT(sys_user.ID,' - ',sys_user.RealName,'  ',sys_user.RealSurname),wh_warehouse.CodeLC,wh_warehouse.WH_ACCOUNT,wh_warehouse.COST_ACCOUNT,wh_warehouse.INCOMMING_ACCOUNT,wh_warehouse.WorkOnlyResponsable,wh_warehouse.IsAbleToSale,wh_warehouse.InvoiceSerial,wh_warehouse.InvoiceNoMIN,wh_warehouse.InvoiceNoMAx,wh_warehouse.ValidFrom,wh_warehouse.ValidTo,wh_warehouse.Created,wh_warehouse.CreatedBy,wh_warehouse.LastUpdate,wh_warehouse.LastUpdateBy from wh_warehouse,sys_user where wh_warehouse.IDRESPONSABLE=sys_user.ID and wh_warehouse.WHCODE='%s' order by wh_warehouse.IDWH;",margv);
	}
	else if (strncmp(option,"LIKE",strlen("LIKE"))==0)	
	{
		sprintf(ExecStatement,"select wh_warehouse.IDWH,wh_warehouse.WHNAME,wh_warehouse.WHCODE,CONCAT(sys_user.ID,' - ',sys_user.RealName,'  ',sys_user.RealSurname),wh_warehouse.CodeLC,wh_warehouse.WH_ACCOUNT,wh_warehouse.COST_ACCOUNT,wh_warehouse.INCOMMING_ACCOUNT,wh_warehouse.WorkOnlyResponsable,wh_warehouse.IsAbleToSale,wh_warehouse.InvoiceSerial,wh_warehouse.InvoiceNoMIN,wh_warehouse.InvoiceNoMAx,wh_warehouse.ValidFrom,wh_warehouse.ValidTo,wh_warehouse.Created,wh_warehouse.CreatedBy,wh_warehouse.LastUpdate,wh_warehouse.LastUpdateBy from wh_warehouse,sys_user where wh_warehouse.IDRESPONSABLE=sys_user.ID and wh_warehouse.WHNAME LIKE '%s%%' order by wh_warehouse.IDWH;",margv);
		//printf("Q :\n %s\n",ExecStatement);
	}
	else if (strncmp(option,"LV",strlen("LV"))==0)	
	{
		sprintf(ExecStatement,"select IDWH,WHCODE,WHNAME from wh_warehouse where NOW() between ValidFrom and ValidTo group by wh_warehouse.WHCODE order by wh_warehouse.IDWH;");
		
	}
	else if (strncmp(option,"LR",strlen("LR"))==0)	
	{
		sprintf(ExecStatement,"select wh_warehouse.WHCODE,CONCAT(sys_user.RealName,'  ',sys_user.RealSurname) from wh_warehouse,sys_user where  wh_warehouse.IDRESPONSABLE=sys_user.ID and NOW() between wh_warehouse.ValidFrom and wh_warehouse.ValidTo order by wh_warehouse.IDWH;");
	}	
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLUpdateWH(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *whname=NULL;
	char *whcode=NULL;
	char *idresp=NULL;
	char *logcenter=NULL;
	char *whacc=NULL;
	char *costacc=NULL;
	char *incomeacc=NULL;
	char *vfrom=NULL;
	char *isresponsable=NULL;
	char *isableforsale=NULL;
	char *serialdoc=NULL;
	char *invoicemin=NULL;
	char *invoicemax=NULL;
	char *vto=NULL;
	char *muser=NULL;
	char *idwh=NULL;
	char *delete=NULL;	

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			whname=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			whcode=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			idresp=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			logcenter=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			whacc=(char*)listpointer->MyItem;
			if(strncmp(whacc,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(whacc,(const char*)"0");
			}
		}
		else if(enumargv==5)
		{
			costacc=(char*)listpointer->MyItem;
			if(strncmp(costacc,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(costacc,(const char*)"0");
			}
		}
		else if(enumargv==6)
		{
			incomeacc=(char*)listpointer->MyItem;
			if(strncmp(incomeacc,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(incomeacc,(const char*)"0");
			}
		}
		else if(enumargv==7)
		{
			isresponsable=(char*)listpointer->MyItem;
		}
		else if(enumargv==8)
		{
			isableforsale=(char*)listpointer->MyItem;
		}
		else if(enumargv==9)
		{
			serialdoc=(char*)listpointer->MyItem;
			if(strncmp(serialdoc,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(serialdoc,(const char*)"");
			}
		}
		else if(enumargv==10)
		{
			invoicemin=(char*)listpointer->MyItem;
		}
		else if(enumargv==11)
		{
			invoicemax=(char*)listpointer->MyItem;
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
			idwh=(char*)listpointer->MyItem;
		}
		else if(enumargv==16)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	if(strncmp(delete,"0",strlen("0"))==0)
	{
		sprintf(ExecStatement,"delete from wh_warehouse where IDWH=%s;",idwh); 
	}
	else
	{
		sprintf(ExecStatement,"update wh_warehouse SET WHNAME='%s',WHCODE='%s',IDRESPONSABLE=%s,CodeLC='%s',WH_ACCOUNT='%s',COST_ACCOUNT='%s',INCOMMING_ACCOUNT='%s',WorkOnlyResponsable='%s',IsAbleToSale='%s',InvoiceSerial='%s',InvoiceNoMIN=%s,InvoiceNoMAX=%s,ValidFrom='%s',ValidTo='%s',LastUpdate=NOW(),LastUpdateBy='%s' where IDWH=%s;",whname,whcode,idresp,logcenter,whacc,costacc,incomeacc,isresponsable,isableforsale,serialdoc,invoicemin,invoicemax,vfrom,vto,muser,idwh); 
	}
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	whname=NULL;
	whcode=NULL;
	idresp=NULL;
	logcenter=NULL;
	whacc=NULL;
	costacc=NULL;
	incomeacc=NULL;
	isresponsable=NULL;
	isableforsale=NULL;
	serialdoc=NULL;
	invoicemin=NULL;
	invoicemax=NULL;
	vfrom=NULL;
	vto=NULL;
	muser=NULL;
	idwh=NULL;
	delete=NULL;
}
void F_SQLInsertWHLocator(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *idwh=NULL;
	char *description=NULL;
	char *cx=NULL;
	char *cz=NULL;
	char *cy=NULL;
	char *width=NULL;
	char *height=NULL;
	char *length=NULL;
	char *grosswght=NULL;
	char *smin=NULL;
	char *smax=NULL;
	char *alloctype=NULL;
	char *idproduct=NULL;
	char *loadpriority=NULL;
	char *unloadpriority=NULL;
	char *muser=NULL;	

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			idwh=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			description=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			cx=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			cy=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==4)
		{
			cz=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==5)
		{
			width=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==6)
		{
			height=(char*)listpointer->MyItem;
		}
		else if(enumargv==7)
		{
			length=(char*)listpointer->MyItem;
		}
		else if(enumargv==8)
		{
			grosswght=(char*)listpointer->MyItem;
		}
		else if(enumargv==9)
		{
			smin=(char*)listpointer->MyItem;
		}
		else if(enumargv==10)
		{
			smax=(char*)listpointer->MyItem;
		}
		else if(enumargv==11)
		{
			alloctype=(char*)listpointer->MyItem;
		}
		else if(enumargv==12)
		{
			idproduct=(char*)listpointer->MyItem;
		}
		else if(enumargv==13)
		{
			loadpriority=(char*)listpointer->MyItem;
		}
		else if(enumargv==14)
		{
			unloadpriority=(char*)listpointer->MyItem;
		}
		else if(enumargv==15)
		{
			muser=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;//urmatorul pointer 	
	}	

	sprintf(ExecStatement,"insert into wh_locators(WHCODE,Description,CX,CY,CZ,mWidth,mHeight,mLength,GrossWght,SMIN,SMAX,AllocType,IDProduct,LoadPriority,UnLoadPriority,Created,CreatedBy) VALUES('%s','%s','%s','%s','%s',%s,%s,%s,%s,%s,%s,'%s',%s,'%s','%s',NOW(),'%s');",idwh,description,cx,cy,cz,width,height,length,grosswght,smin,smax,alloctype,idproduct,loadpriority,unloadpriority,muser); 
	
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	idwh=NULL;
	description=NULL;
	cx=NULL;
	cz=NULL;
	cy=NULL;
	width=NULL;
	height=NULL;
	length=NULL;
	grosswght=NULL;
	smin=NULL;
	smax=NULL;
	alloctype=NULL;
	idproduct=NULL;
	loadpriority=NULL;
	unloadpriority=NULL;
	muser=NULL;	
}
void F_SQLGetWHLocator(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select * from wh_locators order by IDL;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select * from wh_locators order where IDL=%s by IDL;",margv);
	}
	else if (strncmp(option,"LIKE",strlen("LIKE"))==0)
	{
		sprintf(ExecStatement,"select * from wh_locators where Description LIKE '%s%%' order by IDL;",margv);
		//printf("Q :\n %s\n",ExecStatement);
	}
	else if (strncmp(option,"LWH",strlen("LWH"))==0)	
	{
		sprintf(ExecStatement,"select wh_locators.IDL,wh_locators.WHCODE,wh_locators.Description,wh_locators.CX,wh_locators.CY,wh_locators.CZ,wh_locators.mWidth,wh_locators.mHeight,wh_locators.mLength,wh_locators.GrossWght,wh_locators.SMIN,wh_locators.SMAX,wh_locators.AllocType,wh_locators.IDProduct,wh_locators.LoadPriority,wh_locators.UnLoadPriority,wh_locators.Created,wh_locators.CreatedBy,wh_locators.LastUpdate,wh_locators.LastUpdateBy from wh_warehouse,wh_locators where wh_warehouse.WHCODE='%s' and wh_locators.IDWH=wh_warehouse.IDWH  order by IDL;",margv);
		
	}
	else if (strncmp(option,"LW3D",strlen("LW3D"))==0)	
	{
		sprintf(ExecStatement,"select * from wh_locators where CX=MID('%s',1,3) and CY=MID('%s',4,3) and CZ=MID('%s',7,3) order by IDL;",margv,margv,margv);
		
	}
	else if (strncmp(option,"LV",strlen("LV"))==0)	
	{
		sprintf(ExecStatement,"select IDL,CONCAT(CX,CY,CZ),Description from wh_locators where IDWH=%s order by IDL;",margv);
		
	}	
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLUpdateWHLocator(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *idlocator=NULL;
	char *idwh=NULL;
	char *description=NULL;
	char *cx=NULL;
	char *cz=NULL;
	char *cy=NULL;
	char *width=NULL;
	char *height=NULL;
	char *length=NULL;
	char *grosswght=NULL;
	char *smin=NULL;
	char *smax=NULL;
	char *alloctype=NULL;
	char *idproduct=NULL;
	char *loadpriority=NULL;
	char *unloadpriority=NULL;
	char *muser=NULL;
	char *delete=NULL;	

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			idwh=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			description=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			cx=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			cy=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==4)
		{
			cz=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==5)
		{
			width=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==6)
		{
			height=(char*)listpointer->MyItem;
		}
		else if(enumargv==7)
		{
			length=(char*)listpointer->MyItem;
		}
		else if(enumargv==8)
		{
			grosswght=(char*)listpointer->MyItem;
		}
		else if(enumargv==9)
		{
			smin=(char*)listpointer->MyItem;
		}
		else if(enumargv==10)
		{
			smax=(char*)listpointer->MyItem;
		}
		else if(enumargv==11)
		{
			alloctype=(char*)listpointer->MyItem;
		}
		else if(enumargv==12)
		{
			idproduct=(char*)listpointer->MyItem;
		}
		else if(enumargv==13)
		{
			loadpriority=(char*)listpointer->MyItem;
		}
		else if(enumargv==14)
		{
			unloadpriority=(char*)listpointer->MyItem;
		}
		else if(enumargv==15)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if(enumargv==16)
		{
			idlocator=(char*)listpointer->MyItem;
		}
		else if(enumargv==17)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(delete,"0",strlen("0"))==0)
	{
		sprintf(ExecStatement,"delete from wh_locators where IDL=%s;",idlocator); 
	}
	else
	{	
		sprintf(ExecStatement,"update  wh_locators SET WHCODE='%s',Description='%s',CX='%s',CY='%s',CZ='%s',mWidth=%s,mHeight=%s,mLength=%s,GrossWght=%s,SMIN=%s,SMAX=%s,AllocType='%s',IDProduct=%s,LoadPriority='%s',UnLoadPriority='%s',LastUpdate=NOW(),LastUpdateBy='%s' where IDL=%s;",idwh,description,cx,cy,cz,width,height,length,grosswght,smin,smax,alloctype,idproduct,loadpriority,unloadpriority,muser,idlocator); 
	}
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	idlocator=NULL;
	idwh=NULL;
	description=NULL;
	cx=NULL;
	cz=NULL;
	cy=NULL;
	width=NULL;
	height=NULL;
	length=NULL;
	grosswght=NULL;
	smin=NULL;
	smax=NULL;
	alloctype=NULL;
	idproduct=NULL;
	loadpriority=NULL;
	unloadpriority=NULL;
	muser=NULL;	
	delete=NULL;	
}
void F_SQLInUpWHCenterCost(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *isinsert=NULL;
	char *idwh=NULL;	
	char *code=NULL;
	char *description=NULL;
	char *acc_count=NULL;
	char *acc_income=NULL;
	char *acc_cost=NULL;
	char *vfrom=NULL;
	char *vto=NULL;
	char *idcc=NULL;
	char *muser=NULL;
	char *delete=NULL;

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			isinsert=(char*)listpointer->MyItem;
		}
		else if(enumargv==1)
		{
			idwh=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			code=(char*)listpointer->MyItem;
		}	
		else if(enumargv==3)
		{
			description=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			acc_count=(char*)listpointer->MyItem;
			if(strncmp(acc_count,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(acc_count,(const char*)"");
			}
		}
		else if(enumargv==5)
		{
			acc_income=(char*)listpointer->MyItem;
			if(strncmp(acc_income,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(acc_income,(const char*)"");
			}
		}
		else if(enumargv==6)
		{
			acc_cost=(char*)listpointer->MyItem;
			if(strncmp(acc_cost,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(acc_cost,(const char*)"");
			}
		}
		else if(enumargv==7)
		{
			vfrom=(char*)listpointer->MyItem;
		}
		else if(enumargv==8)
		{
			vto=(char*)listpointer->MyItem;
		}
		
		else if(enumargv==9)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if(enumargv==10)
		{
			idcc=(char*)listpointer->MyItem;
		}
		else if(enumargv==11)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;//urmatorul pointer 	
	}	
	
	if(strncmp(isinsert,"1",strlen("1"))==0)	
	{
		sprintf(ExecStatement,"insert into wh_centercost (WHCODE,CODE,DESCRIPTION,ACC_COUNT,ACC_INCOME,ACC_COST,ValidFrom,ValidTo,Created,CreatedBy) VALUES('%s','%s','%s','%s','%s','%s','%s','%s',NOW(),'%s');",idwh,code,description,acc_count,acc_income,acc_cost,vfrom,vto,muser); 

	}
	else
	{
		if(strncmp(delete,"0",strlen("0"))==0)
		{
			sprintf(ExecStatement,"delete from wh_centercost where IDWCC=%s;",idcc); 
		}
		else
		{
			sprintf(ExecStatement,"update wh_centercost SET WHCODE='%s',CODE='%s',DESCRIPTION='%s',ACC_COUNT='%s',ACC_INCOME='%s',ACC_COST='%s',ValidFrom='%s',ValidTo='%s',LastUpdate=NOW(),LastUpdateBy='%s' where IDWCC=%s;",idwh,code,description,acc_count,acc_income,acc_cost,vfrom,vto,muser,idcc); 
	 
		}	
	}
			
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);

	isinsert=NULL;
	idwh=NULL;
	code=NULL;
	description=NULL;
	acc_count=NULL;
	acc_income=NULL;
	acc_cost=NULL;
	vfrom=NULL;
	vto=NULL;
	idcc=NULL;
	muser=NULL;
	delete=NULL;

}
void F_SQLGetWHCenterCost(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select * from wh_centercost order by IDWCC;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select * from wh_centercost order where CODE=%s order by IDWCC;",margv);
	}
	else if (strncmp(option,"LIKE",strlen("LIKE"))==0)	
	{
		sprintf(ExecStatement,"select * from wh_centercost where Description LIKE '%s%%' order by IDWCC;",margv);
		//printf("Q :\n %s\n",ExecStatement);
	}
	else if (strncmp(option,"LWC",strlen("LWC"))==0)	
	{
		sprintf(ExecStatement,"select * from wh_centercost where WHCODE='%s' order by IDWCC;",margv);
	}
	else if (strncmp(option,"LDET",strlen("LDET"))==0)	
	{
		sprintf(ExecStatement,"select CODE,Description from wh_centercost where WHCODE='%s' and NOW() between ValidFrom and ValidTo order by IDWCC;",margv);
	}	
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLInUpInventoryHeader(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *isinsert=NULL;
	char *idih=NULL;	
	char *whcode=NULL;
	char *whcount=NULL;
	char *description=NULL;
	char *idpers=NULL;
	char *status=NULL;
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
			isinsert=(char*)listpointer->MyItem;
		}
		else if(enumargv==1)
		{
			whcode=(char*)listpointer->MyItem;
			if(strncmp(whcode,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(whcode,(const char*)"");
			}
		}
		else if(enumargv==2)
		{
			whcount=(char*)listpointer->MyItem;
			if(strncmp(whcount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(whcount,(const char*)"");
			}
		}	
		else if(enumargv==3)
		{
			description=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			idpers=(char*)listpointer->MyItem;
		}
		else if(enumargv==5)
		{
			status=(char*)listpointer->MyItem;
		}
		else if(enumargv==6)
		{
			vfrom=(char*)listpointer->MyItem;
		}
		else if(enumargv==7)
		{
			vto=(char*)listpointer->MyItem;
		}
		else if(enumargv==8)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if(enumargv==9)
		{
			idih=(char*)listpointer->MyItem;
		}
		else if(enumargv==10)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(isinsert,"1",strlen("1"))==0)
	{
		sprintf(ExecStatement,"insert into acc_h_inventory (WHCODE,ACC_WH,DESCRIPTION,IDRESPUSER,Status,ValidFrom,ValidTo,Created,CreatedBy) VALUES('%s','%s','%s',%s,'%s','%s','%s',NOW(),'%s');",whcode,whcount,description,idpers,status,vfrom,vto,muser); 

	}
	else
	{
		if(strncmp(delete,"0",strlen("0"))==0)
		{
			sprintf(ExecStatement,"delete from acc_h_inventory where IDIV=%s;",idih); 
		}
		else
		{
			sprintf(ExecStatement,"update acc_h_inventory SET WHCODE='%s',ACC_WH='%s',DESCRIPTION='%s',IDRESPUSER=%s,Status='%s',ValidFrom='%s',ValidTo='%s' where IDIV=%s;",whcode,whcount,description,idpers,status,vfrom,vto,idih);
		}	
	}
			
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);

	isinsert=NULL;
	idih=NULL;	
	whcode=NULL;
	whcount=NULL;
	description=NULL;
	idpers=NULL;
	status=NULL;
	vfrom=NULL;
	vto=NULL;
	muser=NULL;
	delete=NULL;

}
void F_SQLGetInventoryHeader(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select acc_h_inventory.IDIV,acc_h_inventory.WHCODE,acc_h_inventory.ACC_WH,acc_h_inventory.DESCRIPTION,CONCAT(sys_user.ID,' - ',sys_user.RealName,' ',sys_user.RealSurname),acc_h_inventory.Status,acc_h_inventory.ValidFrom,acc_h_inventory.ValidTo,acc_h_inventory.Created,acc_h_inventory.CreatedBy from acc_h_inventory,sys_user where acc_h_inventory.IDRESPUSER=sys_user.ID order by acc_h_inventory.IDIV;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select acc_h_inventory.IDIV,acc_h_inventory.WHCODE,acc_h_inventory.ACC_WH,acc_h_inventory.DESCRIPTION,CONCAT(sys_user.ID,' - ',sys_user.RealName,' ',sys_user.RealSurname),acc_h_inventory.Status,acc_h_inventory.ValidFrom,acc_h_inventory.ValidTo,acc_h_inventory.Created,acc_h_inventory.CreatedBy from acc_h_inventory,sys_user where acc_h_inventory.IDIV=%s and acc_h_inventory.IDRESPUSER=sys_user.ID order by acc_h_inventory.IDIV;",margv);
	}
	else if (strncmp(option,"LD",strlen("LD"))==0)
	{
		sprintf(ExecStatement,"select acc_h_inventory.IDIV,acc_h_inventory.WHCODE,acc_h_inventory.ACC_WH,acc_h_inventory.DESCRIPTION,CONCAT(sys_user.ID,' - ',sys_user.RealName,' ',sys_user.RealSurname),acc_h_inventory.Status,acc_h_inventory.ValidFrom,acc_h_inventory.ValidTo,acc_h_inventory.Created,acc_h_inventory.CreatedBy from acc_h_inventory,sys_user where acc_h_inventory.IDRESPUSER=sys_user.ID and '%s' between DATE_FORMAT(acc_h_inventory.ValidFrom,'%%Y-%%m-%%d') and DATE_FORMAT(acc_h_inventory.ValidTo,'%%Y-%%m-%%d') order by acc_h_inventory.IDIV;",margv);
	}

	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLInUpInventoryCommittee(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *isinsert=NULL;
	char *idinv=NULL;	
	char *name=NULL;
	char *surname=NULL;
	char *persid=NULL;
	char *orgrole=NULL;
	char *memonote=NULL;
	char *muser=NULL;
	char *idrec=NULL;
	char *delete=NULL;

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			isinsert=(char*)listpointer->MyItem;
		}
		else if(enumargv==1)
		{
			idinv=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			name=(char*)listpointer->MyItem;
		}	
		else if(enumargv==3)
		{
			surname=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			persid=(char*)listpointer->MyItem;
		}
		else if(enumargv==5)
		{
			orgrole=(char*)listpointer->MyItem;
		}
		else if(enumargv==6)
		{
			memonote=(char*)listpointer->MyItem;
			if(strncmp(memonote,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(memonote,(const char*)"");
			}
		}
		else if(enumargv==7)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if(enumargv==8)
		{
			idrec=(char*)listpointer->MyItem;
		}
		else if(enumargv==9)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(isinsert,"1",strlen("1"))==0)	
	{
		sprintf(ExecStatement,"insert into acc_inventory_commit (IDIV,RealName,RealSurname,PersonalID,OrgRole,MemoNote,Created,CreatedBy) VALUES(%s,'%s','%s','%s','%s','%s',NOW(),'%s');",idinv,name,surname,persid,orgrole,memonote,muser); 

	}
	else
	{
		if(strncmp(delete,"0",strlen("0"))==0)
		{
			sprintf(ExecStatement,"delete from acc_inventory_commit where IDIVC=%s;",idrec); 
		}
		else
		{
			sprintf(ExecStatement,"update acc_inventory_commit SET IDIV=%s,RealName='%s',RealSurname='%s',PersonalID='%s',OrgRole='%s',MemoNote='%s',LastUpdate=NOW(),LastUpdateBy='%s' where IDIVC=%s;",idinv,name,surname,persid,orgrole,memonote,muser,idrec);
		}	
	}
	printf("SQL : \n %s \n",ExecStatement);		
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);

	isinsert=NULL;
	idinv=NULL;	
	name=NULL;
	surname=NULL;
	persid=NULL;
	orgrole=NULL;
	memonote=NULL;
	muser=NULL;
	idrec=NULL;
	delete=NULL;

}
void F_SQLGetInventoryCommittee(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
     	if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select * from acc_inventory_commit where IDIV=%s;",margv);
	}
	
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}

