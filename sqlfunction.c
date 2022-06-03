#include "include/sqlfunction.h"

//Global const
//char MY_PROTO_NULL[]={0x5C,0xD};

extern char* PrepareBuff2SendCMD(long,const char*,unsigned long,DATA_TYPE_TO_SEND);
extern char* PrepareBuff2SendData(long,char*,int*);

extern long recv_data(int,int,void*,int,short int,int);
extern int send_cmd(int,int,char*,long,SEND_OPTION);
extern int WaitReply(int,long,char*,char*);
extern ARGV_LIST * RemoveItem(FUNCTIONS_HANDLE*,long,...); 

extern void F_SQLInsertHeaderAccScheme(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetHeaderSchAccount(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLUpdateHeaderAccScheme(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLInsertAccScheme(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetSchAccount(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLUpdateAccScheme(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLInsertPartenerGeneral(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetPartenerGeneral(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLUpdatePartenerGeneral(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLInsertPartenerBank(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetPartenerBank(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLUpdatePartenerBank(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLInsertPartenerAddr(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetPartenerAddr(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLUpdatetPartenerAddr(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLInsertPartenerContact(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetPartenerContact(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLUpdatePartenerContact(int,MYSQL*,GOBIZ_SESSION*);

extern void F_SQLGetResponsablePerson(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLInsertWH(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetWH(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLUpdateWH(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLInsertWHLocator(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetWHLocator(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLUpdateWHLocator(int,MYSQL*,GOBIZ_SESSION*);

extern void F_SQLInsertMaterialPriceList(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetMaterialPriceList(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLUpdateMaterialPriceList(int,MYSQL*,GOBIZ_SESSION*);

extern void F_SQLInUpMaterialSuppCode(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetMaterialSuppCode(int,MYSQL*,GOBIZ_SESSION*);

extern void F_SQLInUpMaterialPF(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetMaterialPF(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLInUpWHCenterCost(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetWHCenterCost(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLInUpMaterialWH(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetMaterialWH(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLInUpMaterialSales(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetMaterialSale(int,MYSQL*,GOBIZ_SESSION*);

extern void F_SQLInUpInventoryHeader(int s,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetInventoryHeader(int s,MYSQL*,GOBIZ_SESSION*);

extern void F_SQLInUpInventoryCommittee(int,MYSQL*,GOBIZ_SESSION*);
extern void F_SQLGetInventoryCommittee(int,MYSQL*,GOBIZ_SESSION*);


int SQLExecDirect(MYSQL*,char*,char*,SQL_EXEC_OPTIONS);
int SQLExecPlus(MYSQL*,char*,SQL_EXEC_OPTIONS);


//-----------SQLFunction--------------------------------------------------

void ExecFunction(int s,MYSQL* mydata,GOBIZ_SESSION* msess){

	char *mbs=NULL;
	char MYErr[255];
	int zz=0;
	int mylen=0;
	memset(MYErr,'\0',255);


	if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLDirectExec,strlen(MY_SQLDirectExec))==0)
	{
		F_SQLExecDirect(s,mydata,msess);		
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUserFunctions,strlen(MY_SQLUserFunctions))==0)
	{
		F_SQLUserFunctions(s,mydata,msess);		
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertProfile,strlen(MY_SQLInsertProfile))==0)
	{
		F_SQLInsertUpdateProfile(s,mydata,msess);	
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetProfile,strlen(MY_SQLGetProfile))==0)
	{
		F_SQLGetProfile(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLOnlyUpdateProfile,strlen(MY_SQLOnlyUpdateProfile))==0)
	{
		F_SQLOnlyUpdateProfile(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertAcGeneralLedger,strlen(MY_SQLInsertAcGeneralLedger))==0)
	{
		F_SQLInsertAcGeneralLedger(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdateAcGeneralLedger,strlen(MY_SQLUpdateAcGeneralLedger))==0)
	{
		F_SQLUpdateAcGeneralLedger(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetGeneralLedger,strlen(MY_SQLGetGeneralLedger))==0)
	{
		F_SQLGetGeneralLedger(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertAcCurrency,strlen(MY_SQLInsertAcCurrency))==0)
	{
		F_SQLInsertAcCurrency(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetCurrency,strlen(MY_SQLGetCurrency))==0)
	{
		F_SQLGetCurrency(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdateAcCurrency,strlen(MY_SQLUpdateAcCurrency))==0)
	{
		F_SQLUpdateAcCurrency(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_PROC_Test,strlen(MY_PROC_Test))==0)
	{
		F_SPTest(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLLoadDefCurrency,strlen(MY_SQLLoadDefCurrency))==0)
	{
		F_SQLLoadDefaultCurrency(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertClassMaterial,strlen(MY_SQLInsertClassMaterial))==0)
	{
		F_SQLInsertClassMaterial(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetClassMaterial,strlen(MY_SQLGetClassMaterial))==0)
	{
		F_SQLGetClassMaterial(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdateClassMaterial,strlen(MY_SQLUpdateClassMaterial))==0)
	{
		F_SQLUpdateClassMaterial(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertCategoryMaterial,strlen(MY_SQLInsertCategoryMaterial))==0)
	{
		F_SQLInsertCategoryMaterial(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetCategoryMaterial,strlen(MY_SQLGetCategoryMaterial))==0)
	{
		F_SQLGetCategoryMaterial(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdateCategoryMaterial,strlen(MY_SQLUpdateCategoryMaterial))==0)
	{
		F_SQLUpdateCategoryMaterial(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertGroupMaterial,strlen(MY_SQLInsertGroupMaterial))==0)
	{
		F_SQLInsertGroupMaterial(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetGroupMaterial,strlen(MY_SQLGetGroupMaterial))==0)
	{
		F_SQLGetGroupMaterial(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdateGroupMaterial,strlen(MY_SQLUpdateGroupMaterial))==0)
	{
		F_SQLUpdateGroupMaterial(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertTypeMaterial,strlen(MY_SQLInsertTypeMaterial))==0)
	{
		F_SQLInsertTypeMaterial(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetTypeMaterial,strlen(MY_SQLGetTypeMaterial))==0)
	{
		F_SQLGetTypeMaterial(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdateTypeMaterial,strlen(MY_SQLUpdateTypeMaterial))==0)
	{
		F_SQLUpdateTypeMaterial(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertAccHeaderScheme,strlen(MY_SQLInsertAccHeaderScheme))==0)
	{
		F_SQLInsertHeaderAccScheme(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetHeaderSchAccount,strlen(MY_SQLGetHeaderSchAccount))==0)
	{
		F_SQLGetHeaderSchAccount(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdateAccHeaderScheme,strlen(MY_SQLUpdateAccHeaderScheme))==0)
	{
		F_SQLUpdateHeaderAccScheme(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertAccScheme,strlen(MY_SQLInsertAccScheme))==0)
	{
		F_SQLInsertAccScheme(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetAccScheme,strlen(MY_SQLGetAccScheme))==0)
	{
		F_SQLGetSchAccount(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdateAccScheme,strlen(MY_SQLUpdateAccScheme))==0)
	{
		F_SQLUpdateAccScheme(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertMaterialGen,strlen(MY_SQLInsertMaterialGen))==0)
	{
		F_SQLInsertMaterialGeneral(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetMaterialGen,strlen(MY_SQLGetMaterialGen))==0)
	{
		F_SQLGetMaterialGeneral(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdateMaterialGen,strlen(MY_SQLUpdateMaterialGen))==0)
	{
		F_SQLUpdateMaterialGeneral(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertPartenerGen,strlen(MY_SQLInsertPartenerGen))==0)
	{
		F_SQLInsertPartenerGeneral(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetPartenerGen,strlen(MY_SQLGetPartenerGen))==0)
	{
		F_SQLGetPartenerGeneral(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdatePartenerGen,strlen(MY_SQLUpdatePartenerGen))==0)
	{
		F_SQLUpdatePartenerGeneral(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertPartenerBank,strlen(MY_SQLInsertPartenerBank))==0)
	{
		F_SQLInsertPartenerBank(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetPartenerBank,strlen(MY_SQLGetPartenerBank))==0)
	{
		F_SQLGetPartenerBank(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdatePartenerBank,strlen(MY_SQLUpdatePartenerBank))==0)
	{
		F_SQLUpdatePartenerBank(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertPartenerAddr,strlen(MY_SQLInsertPartenerAddr))==0)
	{
		F_SQLInsertPartenerAddr(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetPartenerAddr,strlen(MY_SQLGetPartenerAddr))==0)
	{
		F_SQLGetPartenerAddr(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdatePartenerAddr,strlen(MY_SQLUpdatePartenerAddr))==0)
	{
		F_SQLUpdatetPartenerAddr(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertPartenerContact,strlen(MY_SQLInsertPartenerContact))==0)
	{
		F_SQLInsertPartenerContact(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetPartenerContact,strlen(MY_SQLGetPartenerContact))==0)
	{
		F_SQLGetPartenerContact(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdatePartenerContact,strlen(MY_SQLUpdatePartenerContact))==0)
	{
		F_SQLUpdatePartenerContact(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetResponsablePerson,strlen(MY_SQLGetResponsablePerson))==0)
	{
		F_SQLGetResponsablePerson(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertWH,strlen(MY_SQLInsertWH))==0)
	{
		F_SQLInsertWH(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetWH,strlen(MY_SQLGetWH))==0)
	{
		F_SQLGetWH(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdateWH,strlen(MY_SQLUpdateWH))==0)
	{
		F_SQLUpdateWH(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInsertWHLocator,strlen(MY_SQLInsertWHLocator))==0)
	{
		F_SQLInsertWHLocator(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetWHLocator,strlen(MY_SQLGetWHLocator))==0)
	{
		F_SQLGetWHLocator(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLUpdateWHLocator,strlen(MY_SQLUpdateWHLocator))==0)
	{
		F_SQLUpdateWHLocator(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLMaterialInPriceList,strlen(MY_SQLMaterialInPriceList))==0)
	{
		F_SQLInsertMaterialPriceList(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLMaterialGetPriceList,strlen(MY_SQLMaterialGetPriceList))==0)
	{
		F_SQLGetMaterialPriceList(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLMaterialUpPriceList,strlen(MY_SQLMaterialUpPriceList))==0)
	{
		F_SQLUpdateMaterialPriceList(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInUpMaterialSuppCode,strlen(MY_SQLInUpMaterialSuppCode))==0)
	{
		F_SQLInUpMaterialSuppCode(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetMaterialSuppCode,strlen(MY_SQLGetMaterialSuppCode))==0)
	{
		F_SQLGetMaterialSuppCode(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInUpMaterialFP,strlen(MY_SQLInUpMaterialFP))==0)
	{
		F_SQLInUpMaterialPF(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetMaterialFP,strlen(MY_SQLGetMaterialFP))==0)
	{
		F_SQLGetMaterialPF(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInUpWHCenterCost,strlen(MY_SQLInUpWHCenterCost))==0)
	{
		F_SQLInUpWHCenterCost(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetWHCenterCost,strlen(MY_SQLGetWHCenterCost))==0)
	{
		F_SQLGetWHCenterCost(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInUpMaterialWH,strlen(MY_SQLInUpMaterialWH))==0)
	{
		F_SQLInUpMaterialWH(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetMaterialWH,strlen(MY_SQLGetMaterialWH))==0)
	{
		F_SQLGetMaterialWH(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInUpMaterialSale,strlen(MY_SQLInUpMaterialSale))==0)
	{
		F_SQLInUpMaterialSales(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetpMaterialSale,strlen(MY_SQLGetpMaterialSale))==0)
	{
		F_SQLGetMaterialSale(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInUpInventoryHeader,strlen(MY_SQLInUpInventoryHeader))==0)
	{
		F_SQLInUpInventoryHeader(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetInventoryHeader,strlen(MY_SQLGetInventoryHeader))==0)
	{
		F_SQLGetInventoryHeader(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLInUpInventoryCommittee,strlen(MY_SQLInUpInventoryCommittee))==0)
	{
		F_SQLInUpInventoryCommittee(s,mydata,msess);
	}
	else if(strncmp(msess->FunctionToHandle->FunctionNameHandle,MY_SQLGetInventoryCommittee,strlen(MY_SQLGetInventoryCommittee))==0)
	{
		F_SQLGetInventoryCommittee(s,mydata,msess);
	}
	
	else
	{
		strcpy(MYErr,(const char*)"Functia ");
		strcat(MYErr,(const char*)msess->FunctionToHandle->FunctionNameHandle);
		strcat(MYErr,(const char*)" nu este implementata.");
		mbs=PrepareBuff2SendData(strlen(MYErr),MYErr,&mylen);
		zz=send_cmd(s,10,mbs,(long)mylen,MY_ASCII_DATA);
		free(mbs);
		mbs=NULL; 
	}
}
void F_SQLExecDirect(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;	
	char *ExecStatement=NULL;
		
	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		ExecStatement=(char*)listpointer->MyItem;
	
		listpointer=listpointer -> NextArgv;//urmatorul pointer 	
	}	

     	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	ExecStatement=NULL;
	
}
int SQLExecPlus(MYSQL *myData,char *myQuery,SQL_EXEC_OPTIONS mExecOption){
	
	MYSQL_RES *mRes;
	
	if((mysql_real_query(myData,myQuery,strlen(myQuery)))<0)
	{
		return 0;
	}

	if(mExecOption==INSERT_OR_UPDATE)
	{	
		
		return 1;
	}		
	else
	{
		mRes=mysql_use_result(myData);
		mysql_free_result(mRes);
		return 1;
	}
}
void F_SQLUserFunctions(int s,MYSQL* mydata,GOBIZ_SESSION* msess){
	int enumargv=0;
	char* muser=NULL;
	char* mpasswd=NULL;
	char* logcenter=NULL;
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if(enumargv==1)
		{
			mpasswd=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			logcenter=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;//urmatorul pointer 	
	}	
	
	sprintf(ExecStatement,"select sys_user.ID,sys_user.RealName,sys_user.RealSurname,sys_user.RoleInOrg,sys_functions.SYM_FUNC,sys_functions.FUNC_NAME,sys_functions.FUNC_DESCRIPTION,sys_functions.FUNC_GROUP,sys_functions_rights.FUNC_RIGHTS from sys_user,sys_functions,sys_functions_rights where sys_user.UserName='%s' and sys_user.Password=MD5('%s') and sys_user.LogisticCenter='%s' and sys_user.ID=sys_functions_rights.ID_USER AND  sys_functions.SYM_FUNC=sys_functions_rights.SYM_FUNC and sys_user.D=1 and sys_functions.D=1 and sys_functions_rights.D=1 and NOW() between sys_user.ValidFrom and sys_user.ValidTo order by sys_functions.FUNC_GROUP;",muser,mpasswd,logcenter);
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	memset(ExecStatement,'\0',1024);	
	muser=NULL;
	mpasswd=NULL;
	logcenter=NULL;
}

int SQLExecDirect(MYSQL* myData,char* myQuery,char * mResult,SQL_EXEC_OPTIONS mExecOption){

	MYSQL_RES *mRes;
	MYSQL_FIELD *mFields;
	MYSQL_ROW mRow;
	long nrRows=0,nrFields=0,i=0;
	long x=0;
	char *mBuff=NULL;
	char *tmpc=NULL;
	char *MYSQLerr=NULL;
	static char mbss[65052];
	
	unsigned long *lengths;
	long myaffrows=0;
	memset(mbss,'\0',65052);
	
	if((mysql_real_query(myData,myQuery,strlen(myQuery)))<0)
	{
		MYSQLerr=(char*)mysql_error(myData);
		return(-1);
	}
	
	if(mExecOption==INSERT_OR_UPDATE)
	{
		myaffrows=mysql_affected_rows(myData);
		return myaffrows;
	}

	mRes=mysql_store_result(myData);
	

	if(!mRes)
	{
		goto myEND;
	}
	nrRows=mysql_num_rows(mRes);
	if(nrRows==0)
	{
		goto myEND;
	}
	nrFields=mysql_num_fields(mRes);
	
	memset(mbss,'\0',65052);
		
	while ((mRow = mysql_fetch_row(mRes)))
	{

		if(!mRow)
		{
			goto myEND;
		}
		x++;
		lengths=mysql_fetch_lengths(mRes);

		for(i=0;i<nrFields;i++)
		{
			
			mBuff=mRow[i] ? mRow[i] : "NULL";
			if(i==nrFields-1)
			{
				tmpc=concat(mbss,mBuff,(char*)0);
			}
			else
			{
				tmpc=concat(mbss,mBuff,",",(char*)0);
			}
			
			strncpy(mbss,tmpc,strlen(tmpc));
			free(tmpc);
			mBuff='\0';
			
		}
		
		memset(mbss,'\0',65052);
		
	}

myEND:
	
	memset(mbss,'\0',65052);
	
	tmpc=NULL;
	mFields=NULL;
	mRow=NULL;
	mysql_free_result(mRes);
	return nrRows;

}
void F_SQLInsertUpdateProfile(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char* symcomp=NULL;
	char* namecomp=NULL;
	char* citycomp=NULL;
	char* streetcomp=NULL;
	char* fiscalreg=NULL;
	char* commercialreg=NULL;
	char* muser=NULL;
	char* iban=NULL;
	
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			symcomp=(char*)listpointer->MyItem;
		}
		else if (enumargv==1)
		{
			namecomp=(char*)listpointer->MyItem;
		}
		else if (enumargv==2)
		{
			citycomp=(char*)listpointer->MyItem;
		}
		else if (enumargv==3)
		{
			streetcomp=(char*)listpointer->MyItem;
		}
		else if (enumargv==4)
		{
			fiscalreg=(char*)listpointer->MyItem;
		}
		else if (enumargv==5)
		{
			commercialreg=(char*)listpointer->MyItem;
		}
		else if (enumargv==6)
		{
			iban=(char*)listpointer->MyItem;
		}
		else if (enumargv==7)
		{
			muser=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv; 	
	}	
	
	sprintf(ExecStatement,"insert into profile_company(SYM_COMP,NAME_COMP,CITY,STREET,FISCAL_REGISTRATION,COMERCIAL_REGISTRATION,IBAN,Created,CreatedBy) VALUES('%s','%s','%s','%s','%s','%s','%s',NOW(),'%s');",symcomp,namecomp,citycomp,streetcomp,fiscalreg,commercialreg,iban,muser );
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	symcomp=NULL;
	namecomp=NULL;
	citycomp=NULL;
	streetcomp=NULL;
	fiscalreg=NULL;
	commercialreg=NULL;
	muser=NULL;
	iban=NULL;	
}

void F_SQLOnlyUpdateProfile(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char* symcomp=NULL;
	char* namecomp=NULL;
	char* citycomp=NULL;
	char* streetcomp=NULL;
	char* fiscalreg=NULL;
	char* commercialreg=NULL;
	char* muser=NULL;
	char* iban=NULL;
	
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			symcomp=(char*)listpointer->MyItem;
		}
		else if (enumargv==1)
		{
			namecomp=(char*)listpointer->MyItem;
		}
		else if (enumargv==2)
		{
			citycomp=(char*)listpointer->MyItem;
		}
		else if (enumargv==3)
		{
			streetcomp=(char*)listpointer->MyItem;
		}
		else if (enumargv==4)
		{
			fiscalreg=(char*)listpointer->MyItem;
		}
		else if (enumargv==5)
		{
			commercialreg=(char*)listpointer->MyItem;
		}
		else if (enumargv==6)
		{
			iban=(char*)listpointer->MyItem;
		}
		else if (enumargv==7)
		{
			muser=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	
	sprintf(ExecStatement,"update profile_company SET SYM_COMP='%s',NAME_COMP='%s',CITY='%s',STREET='%s',FISCAL_REGISTRATION='%s',COMERCIAL_REGISTRATION='%s',IBAN='%s',LastUpdate=NOW(),UpdateBy='%s';",symcomp,namecomp,citycomp,streetcomp,fiscalreg,commercialreg,iban,muser );
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	symcomp=NULL;
	namecomp=NULL;
	citycomp=NULL;
	streetcomp=NULL;
	fiscalreg=NULL;
	commercialreg=NULL;
	muser=NULL;
	iban=NULL;	
}

void F_SQLGetProfile(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
		
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

    sprintf(ExecStatement,"select SYM_COMP,NAME_COMP,CITY,STREET,FISCAL_REGISTRATION,COMERCIAL_REGISTRATION,IBAN from  profile_company;");
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	
}



void F_SQLInsertAcGeneralLedger(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char* symcount=NULL;
	char* namecount=NULL;
	char* leninitcount=NULL;
	char* lenchildcount=NULL;
	char* soldinitin=NULL;
	char* soldinitout=NULL;
	char* typecount=NULL;
	char* rolecount=NULL;
	char* coefcalcul=NULL;
	char* arithmeticop=NULL;
	char* muser=NULL;
	
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			symcount=(char*)listpointer->MyItem;
		}
		else if (enumargv==1)
		{
			namecount=(char*)listpointer->MyItem;
		}
		else if (enumargv==2)
		{
			leninitcount=(char*)listpointer->MyItem;
		}
		else if (enumargv==3)
		{
			lenchildcount=(char*)listpointer->MyItem;
		}
		else if (enumargv==4)
		{
			soldinitin=(char*)listpointer->MyItem;
		}
		else if (enumargv==5)
		{
			soldinitout=(char*)listpointer->MyItem;
		}
		else if (enumargv==6)
		{
			typecount=(char*)listpointer->MyItem;
		}
		else if (enumargv==7)
		{
			rolecount=(char*)listpointer->MyItem;
		}
		else if (enumargv==8)
		{
			coefcalcul=(char*)listpointer->MyItem;
		}
		else if (enumargv==9)
		{
			arithmeticop=(char*)listpointer->MyItem;
		}
		else if (enumargv==10)
		{
			muser=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	
	sprintf(ExecStatement,"insert into ac_general_ledger (SYM_COUNT,NAME_COUNT,LEN_INIT_COUNT,LEN_CHILD_COUNT,SOLD_INIT_IN,SOLD_INIT_OUT,TYPE_COUNT,ROLE_COUNT,COEF_CALCUL,ARITHMETIC_OP,Created,CreatedBy,D) VALUES('%s','%s','%s','%s','%s','%s','%s','%s','%s','%s',NOW(),'%s',1);",symcount,namecount,leninitcount,lenchildcount,soldinitin,soldinitout,typecount,rolecount,coefcalcul,arithmeticop,muser);
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	symcount=NULL;
	namecount=NULL;
	leninitcount=NULL;
	lenchildcount=NULL;
	soldinitin=NULL;
	soldinitout=NULL;
	typecount=NULL;
	rolecount=NULL;
	coefcalcul=NULL;
	arithmeticop=NULL;
	muser=NULL;
}
void F_SQLUpdateAcGeneralLedger(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char* symcount=NULL;
	char* namecount=NULL;
	char* leninitcount=NULL;
	char* lenchildcount=NULL;
	char* soldinitin=NULL;
	char* soldinitout=NULL;
	char* typecount=NULL;
	char* rolecount=NULL;
	char* coefcalcul=NULL;
	char* arithmeticop=NULL;
	char* muser=NULL;
	char* delete=NULL;
	
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			symcount=(char*)listpointer->MyItem;
		}
		else if (enumargv==1)
		{
			namecount=(char*)listpointer->MyItem;
		}
		else if (enumargv==2)
		{
			leninitcount=(char*)listpointer->MyItem;
		}
		else if (enumargv==3)
		{
			lenchildcount=(char*)listpointer->MyItem;
		}
		else if (enumargv==4)
		{
			soldinitin=(char*)listpointer->MyItem;
		}
		else if (enumargv==5)
		{
			soldinitout=(char*)listpointer->MyItem;
		}
		else if (enumargv==6)
		{
			typecount=(char*)listpointer->MyItem;
		}
		else if (enumargv==7)
		{
			rolecount=(char*)listpointer->MyItem;
		}
		else if (enumargv==8)
		{
			coefcalcul=(char*)listpointer->MyItem;
		}
		else if (enumargv==9)
		{
			arithmeticop=(char*)listpointer->MyItem;
		}
		else if (enumargv==10)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if (enumargv==11)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(delete,"0",strlen("0"))==0)
	{
		sprintf(ExecStatement,"delete from ac_general_ledger where SYM_COUNT='%s';",symcount);
	}
	else
	{
		sprintf(ExecStatement,"update ac_general_ledger SET NAME_COUNT='%s',LEN_INIT_COUNT='%s',LEN_CHILD_COUNT='%s',SOLD_INIT_IN='%s',SOLD_INIT_OUT='%s',TYPE_COUNT='%s',ROLE_COUNT='%s',COEF_CALCUL='%s',ARITHMETIC_OP='%s',LastUpdate=NOW(),LastUpdateBy='%s',D='%s' where SYM_COUNT='%s';",namecount,leninitcount,lenchildcount,soldinitin,soldinitout,typecount,rolecount,coefcalcul,arithmeticop,muser,delete,symcount);
	}
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	symcount=NULL;
	namecount=NULL;
	leninitcount=NULL;
	lenchildcount=NULL;
	soldinitin=NULL;
	soldinitout=NULL;
	typecount=NULL;
	rolecount=NULL;
	coefcalcul=NULL;
	arithmeticop=NULL;
	muser=NULL;
	delete=NULL;
}
void F_SQLGetGeneralLedger(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select SYM_COUNT,NAME_COUNT,LEN_CHILD_COUNT,SOLD_INIT_IN,SOLD_INIT_OUT,TYPE_COUNT,ROLE_COUNT,COEF_CALCUL,ARITHMETIC_OP,Created,CreatedBy,LastUpdate,LastUpdateBy from ac_general_ledger where D=1 order by SYM_COUNT;");
	}
	else if (strncmp(option,"=",strlen("="))==0)
	{
		sprintf(ExecStatement,"select SYM_COUNT,NAME_COUNT,LEN_CHILD_COUNT,SOLD_INIT_IN,SOLD_INIT_OUT,TYPE_COUNT,ROLE_COUNT,COEF_CALCUL,ARITHMETIC_OP,Created,CreatedBy,LastUpdate,LastUpdateBy  from ac_general_ledger where SYM_COUNT='%s' and D=1 order by SYM_COUNT;",margv);
	}
	else if (strncmp(option,"LIKE",strlen("LIKE"))==0)	
	{
		sprintf(ExecStatement,"select SYM_COUNT,NAME_COUNT,LEN_CHILD_COUNT,SOLD_INIT_IN,SOLD_INIT_OUT,TYPE_COUNT,ROLE_COUNT,COEF_CALCUL,ARITHMETIC_OP,Created,CreatedBy,LastUpdate,LastUpdateBy  from ac_general_ledger where NAME_COUNT LIKE  '%s%%' and D=1 order by SYM_COUNT;",margv);

	}
	else if (strncmp(option,"LH",strlen("LH"))==0)	
	{
		sprintf(ExecStatement,"select SYM_COUNT,NAME_COUNT,TYPE_COUNT from ac_general_ledger where D=1 order by SYM_COUNT;");

	}
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLInsertAcCurrency(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char* symcurrency=NULL;
	char* namecurrency=NULL;
	char* calcefectiv=NULL;
	char* calcshow=NULL;
	char* unitbase=NULL;
	char* isdefault=NULL;
	char* validfrom=NULL;
	char* validto=NULL;
	char* muser=NULL;
	
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			symcurrency=(char*)listpointer->MyItem;
		}
		else if (enumargv==1)
		{
			namecurrency=(char*)listpointer->MyItem;
		}
		else if (enumargv==2)
		{
			calcefectiv=(char*)listpointer->MyItem;
		}
		else if (enumargv==3)
		{
			calcshow=(char*)listpointer->MyItem;
		}
		else if (enumargv==4)
		{
			unitbase=(char*)listpointer->MyItem;
		}
		else if (enumargv==5)
		{
			isdefault=(char*)listpointer->MyItem;
		}
		else if (enumargv==6)
		{
			validfrom=(char*)listpointer->MyItem;
		}
		else if (enumargv==7)
		{
			validto=(char*)listpointer->MyItem;
		}
		else if (enumargv==8)
		{
			muser=(char*)listpointer->MyItem;
		}
		
		listpointer=listpointer -> NextArgv; 	
	}	
	
	sprintf(ExecStatement,"insert into ac_currency (SYM_CUR,NAME_CUR,CALC_EFECTIV,CALC_SHOW,UNIT_BASE,IsDefault,ValidFrom,ValidTo,Created,CreatedBy) VALUES('%s','%s','%s','%s','%s','%s','%s','%s',NOW(),'%s');",symcurrency,namecurrency,calcefectiv,calcshow,unitbase,isdefault,validfrom,validto,muser);
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	symcurrency=NULL;
	namecurrency=NULL;
	calcefectiv=NULL;
	calcshow=NULL;
	unitbase=NULL;
	isdefault=NULL;
	validfrom=NULL;
	validto=NULL;
	muser=NULL;
}
void F_SQLGetCurrency(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select SYM_CUR,NAME_CUR,CALC_EFECTIV,CALC_SHOW,UNIT_BASE,IsDefault,ValidFrom,ValidTo,Created,CreatedBy,LastUpdate,LastUpdateBy from ac_currency where NOW() between ValidFrom and ValidTo order by SYM_CUR;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select SYM_CUR,NAME_CUR,CALC_EFECTIV,CALC_SHOW,UNIT_BASE,IsDefault,ValidFrom,ValidTo,Created,CreatedBy,LastUpdate,LastUpdateBy from ac_currency where SYM_CUR='%s' and NOW() between ValidFrom and ValidTo order by SYM_CUR;",margv);
	}
	else if (strncmp(option,"LIKE",strlen("LIKE"))==0)	
	{
		sprintf(ExecStatement,"select SYM_CUR,NAME_CUR,CALC_EFECTIV,CALC_SHOW,UNIT_BASE,IsDefault,ValidFrom,ValidTo,Created,CreatedBy,LastUpdate,LastUpdateBy from ac_currency where NAME_CUR LIKE '%s%%' and NOW() between ValidFrom and ValidTo order by SYM_CUR;",margv);
	}
	
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLLoadDefaultCurrency(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
		
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

	sprintf(ExecStatement,"select SYM_CUR,NAME_CUR,CALC_EFECTIV,CALC_SHOW from ac_currency where IsDefault='Yes' and NOW() between ValidFrom and ValidTo;");
	
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	
}
void F_SQLUpdateAcCurrency(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char* symcurrency=NULL;
	char* namecurrency=NULL;
	char* calcefectiv=NULL;
	char* calcshow=NULL;
	char* unitbase=NULL;
	char* isdefault=NULL;
	char* validfrom=NULL;
	char* validto=NULL;
	char* muser=NULL;
	char* delete=NULL;
	
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			symcurrency=(char*)listpointer->MyItem;
		}
		else if (enumargv==1)
		{
			namecurrency=(char*)listpointer->MyItem;
		}
		else if (enumargv==2)
		{
			calcefectiv=(char*)listpointer->MyItem;
		}
		else if (enumargv==3)
		{
			calcshow=(char*)listpointer->MyItem;
		}
		else if (enumargv==4)
		{
			unitbase=(char*)listpointer->MyItem;
		}
		else if (enumargv==5)
		{
			isdefault=(char*)listpointer->MyItem;
		}
		else if (enumargv==6)
		{
			validfrom=(char*)listpointer->MyItem;
		}
		else if (enumargv==7)
		{
			validto=(char*)listpointer->MyItem;
		}
		else if (enumargv==8)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if (enumargv==9)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(delete,"0",strlen("0"))==0)
	{
		sprintf(ExecStatement,"delete from ac_currency where SYM_CUR='%s';",symcurrency); 
	}
	else
	{
		sprintf(ExecStatement,"update ac_currency SET NAME_CUR='%s',CALC_EFECTIV='%s',CALC_SHOW='%s',UNIT_BASE='%s',IsDefault='%s',ValidFrom='%s',ValidTo='%s',LastUpdate=NOW(),LastUpdateBy='%s' where SYM_CUR='%s';",namecurrency,calcefectiv,calcshow,unitbase,isdefault,validfrom,validto,muser,symcurrency);
	}
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	symcurrency=NULL;
	namecurrency=NULL;
	calcefectiv=NULL;
	calcshow=NULL;
	unitbase=NULL;
	isdefault=NULL;
	validfrom=NULL;
	validto=NULL;
	muser=NULL;
	delete=NULL;
}
void F_SPTest(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char* symcurrency=NULL;
	char* namecurrency=NULL;
	char* calcefectiv=NULL;
	char* calcshow=NULL;
	char* unitbase=NULL;
	char* isdefault=NULL;
	char* validfrom=NULL;
	char* validto=NULL;
	char* muser=NULL;
	char* delete=NULL;
	
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			symcurrency=(char*)listpointer->MyItem;
		}
		else if (enumargv==1)
		{
			namecurrency=(char*)listpointer->MyItem;
		}
		else if (enumargv==2)
		{
			calcefectiv=(char*)listpointer->MyItem;
		}
		else if (enumargv==3)
		{
			calcshow=(char*)listpointer->MyItem;
		}
		else if (enumargv==4)
		{
			unitbase=(char*)listpointer->MyItem;
		}
		else if (enumargv==5)
		{
			isdefault=(char*)listpointer->MyItem;
		}
		else if (enumargv==6)
		{
			validfrom=(char*)listpointer->MyItem;
		}
		else if (enumargv==7)
		{
			validto=(char*)listpointer->MyItem;
		}
		else if (enumargv==8)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if (enumargv==9)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv; 	
	}	
	
	sprintf(ExecStatement,"call sp1 (1,'asd');"); 
	
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	symcurrency=NULL;
	namecurrency=NULL;
	calcefectiv=NULL;
	calcshow=NULL;
	unitbase=NULL;
	isdefault=NULL;
	validfrom=NULL;
	validto=NULL;
	muser=NULL;
	delete=NULL;
}
void F_SQLInsertClassMaterial(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;

	char* name=NULL;
	char* code=NULL;
	char* genaccount=NULL;
	char* costaccount=NULL;
	char* inaccount=NULL;
	char* whaccount=NULL;
	char* validfrom=NULL;
	char* validto=NULL;
	char* muser=NULL;
	char* firstrecflag=NULL;	

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			name=(char*)listpointer->MyItem;
		}
		else if (enumargv==1)
		{
			code=(char*)listpointer->MyItem;
		}
		else if (enumargv==2)
		{
			genaccount=(char*)listpointer->MyItem;
		}
		else if (enumargv==3)
		{
			costaccount=(char*)listpointer->MyItem;
		}
		else if (enumargv==4)
		{
			inaccount=(char*)listpointer->MyItem;
		}
		else if (enumargv==5)
		{
			whaccount=(char*)listpointer->MyItem;
		}
		else if (enumargv==6)
		{
			validfrom=(char*)listpointer->MyItem;
		}
		else if (enumargv==7)
		{
			validto=(char*)listpointer->MyItem;
		}
		else if (enumargv==8)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if (enumargv==9)
		{
			firstrecflag=(char*)listpointer->MyItem;
		}
		
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(firstrecflag,"1",strlen("1"))==0)
	{
		sprintf(ExecStatement,"insert into mm_class_material (IDCM,NAME,CODE,GEN_ACCOUNT,COST_ACCOUNT,INCOMMING_ACCOUNT,WH_ACCOUNT,ValidFrom,ValidTo,Created,CreatedBy) VALUES(100,'%s','%s','%s','%s','%s','%s','%s','%s',NOW(),'%s');",name,code,genaccount,costaccount,inaccount,whaccount,validfrom,validto,muser); 
	}
	else
	{
		sprintf(ExecStatement,"insert into mm_class_material (NAME,CODE,GEN_ACCOUNT,COST_ACCOUNT,INCOMMING_ACCOUNT,WH_ACCOUNT,ValidFrom,ValidTo,Created,CreatedBy) VALUES('%s','%s','%s','%s','%s','%s','%s','%s',NOW(),'%s');",name,code,genaccount,costaccount,inaccount,whaccount,validfrom,validto,muser); 
	}

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	name=NULL;
	code=NULL;
	genaccount=NULL;
	costaccount=NULL;
	inaccount=NULL;
	whaccount=NULL;
	validfrom=NULL;
	validto=NULL;
	muser=NULL;
	firstrecflag=NULL;	
}
void F_SQLGetClassMaterial(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select * from mm_class_material order by IDCM;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select * from mm_class_material where IDCM=%s and NOW() between ValidFrom and ValidTo order by IDCM;",margv);
	}
	else if (strncmp(option,"LIKE",strlen("LIKE"))==0)	
	{
		sprintf(ExecStatement,"select * from mm_class_material where NAME LIKE '%s%%' and NOW() between ValidFrom and ValidTo order by IDCM;",margv);
	}
	
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLUpdateClassMaterial(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;

	char* idclass=NULL;
	char* name=NULL;
	char* code=NULL;
	char* genaccount=NULL;
	char* costaccount=NULL;
	char* inaccount=NULL;
	char* whaccount=NULL;
	char* validfrom=NULL;
	char* validto=NULL;
	char* muser=NULL;
	char* delete=NULL;	

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if (enumargv==0)
		{
			idclass=(char*)listpointer->MyItem;
		}
		else if(enumargv==1)
		{
			name=(char*)listpointer->MyItem;
		}
		else if (enumargv==2)
		{
			code=(char*)listpointer->MyItem;
		}
		else if (enumargv==3)
		{
			genaccount=(char*)listpointer->MyItem;
		}
		else if (enumargv==4)
		{
			costaccount=(char*)listpointer->MyItem;
		}
		else if (enumargv==5)
		{
			inaccount=(char*)listpointer->MyItem;
		}
		else if (enumargv==6)
		{
			whaccount=(char*)listpointer->MyItem;
		}
		else if (enumargv==7)
		{
			validfrom=(char*)listpointer->MyItem;
		}
		else if (enumargv==8)
		{
			validto=(char*)listpointer->MyItem;
		}
		else if (enumargv==9)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if (enumargv==10)
		{
			delete=(char*)listpointer->MyItem;
		}
		
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(delete,"0",strlen("0"))==0)
	{
		sprintf(ExecStatement,"delete from mm_class_material where IDCM=%s;",idclass); 
	}
	else
	{
		sprintf(ExecStatement,"update mm_class_material SET NAME='%s',CODE='%s',GEN_ACCOUNT='%s',COST_ACCOUNT='%s',INCOMMING_ACCOUNT='%s',WH_ACCOUNT='%s',ValidFrom='%s',ValidTo='%s',LastUpdate=NOW(),LastUpdateBy='%s' where IDCM=%s;",name,code,genaccount,costaccount,inaccount,whaccount,validfrom,validto,muser,idclass); 
	}

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	idclass=NULL;
	name=NULL;
	code=NULL;
	genaccount=NULL;
	costaccount=NULL;
	inaccount=NULL;
	whaccount=NULL;
	validfrom=NULL;
	validto=NULL;
	muser=NULL;
	delete=NULL;	
}
void F_SQLInsertCategoryMaterial(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char* idclass=NULL;
	char* name=NULL;
	char* code=NULL;
	char* genaccount=NULL;
	char* costaccount=NULL;
	char* inaccount=NULL;
	char* whaccount=NULL;
	char* validfrom=NULL;
	char* validto=NULL;
	char* muser=NULL;
	char* firstrecflag=NULL;	
	char* sql1=NULL;

	int sql1len=strlen("select IF(MAX(IDCaM) IS NULL,@a:=100,@a:=MAX(IDCaM)+1) from mm_category_material where IDCLASSMAT=;")+4;
	
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			idclass=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			name=(char*)listpointer->MyItem;
		}
		else if (enumargv==2)
		{
			code=(char*)listpointer->MyItem;
			if(strncmp(code,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(code,(const char*)"");
			}
		}
		else if (enumargv==3)
		{
			genaccount=(char*)listpointer->MyItem;
			if(strncmp(genaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(genaccount,(const char*)"");
			}
		}
		else if (enumargv==4)
		{
			costaccount=(char*)listpointer->MyItem;
			if(strncmp(costaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(costaccount,(const char*)"");
			}
		}
		else if (enumargv==5)
		{
			inaccount=(char*)listpointer->MyItem;
			if(strncmp(inaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(inaccount,(const char*)"");
			}
		}
		else if (enumargv==6)
		{
			whaccount=(char*)listpointer->MyItem;
			if(strncmp(whaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(whaccount,(const char*)"");
			}
		}
		else if (enumargv==7)
		{
			validfrom=(char*)listpointer->MyItem;
		}
		else if (enumargv==8)
		{
			validto=(char*)listpointer->MyItem;
		}
		else if (enumargv==9)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if (enumargv==10)
		{
			firstrecflag=(char*)listpointer->MyItem;
		}
		
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(firstrecflag,"1",strlen("1"))==0)
	{
		sprintf(ExecStatement,"insert into mm_category_material (IDCaM,IDCLASSMAT,NAME,CODE,GEN_ACCOUNT,COST_ACCOUNT,INCOMMING_ACCOUNT,WH_ACCOUNT,ValidFrom,ValidTo,Created,CreatedBy) VALUES(100,'%s','%s','%s','%s','%s','%s','%s','%s','%s',NOW(),'%s');",idclass,name,code,genaccount,costaccount,inaccount,whaccount,validfrom,validto,muser); 
	}
	else
	{
		if(SQLExecPlus(mydata,(char*)"SET @a:=0;",INSERT_OR_UPDATE))
		{	
			sql1=(char*)malloc(sql1len);
			memset(sql1,'\0',sql1len);
			sprintf(sql1,"select IF(MAX(IDCaM) IS NULL,@a:=100,@a:=MAX(IDCaM)+1) from mm_category_material where IDCLASSMAT=%s;",idclass);
			if(SQLExecPlus(mydata,sql1,EXECUTE_STATEMENT))
			{
				sprintf(ExecStatement,"insert into mm_category_material (IDCaM,IDCLASSMAT,NAME,CODE,GEN_ACCOUNT,COST_ACCOUNT,INCOMMING_ACCOUNT,WH_ACCOUNT,ValidFrom,ValidTo,Created,CreatedBy) VALUES(@a,'%s','%s','%s','%s','%s','%s','%s','%s','%s',NOW(),'%s');",idclass,name,code,genaccount,costaccount,inaccount,whaccount,validfrom,validto,muser); 
				
			}
			else
			{

				strcpy(ExecStatement,"ERR: Procedura de Incrementare");
			}
			free(sql1);
			sql1=NULL;		
		}
		else
		{

			strcpy(ExecStatement,"ERR: SET @a:=0");
		}
	}

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
		
	memset(ExecStatement,'\0',1024);	
	idclass=NULL;
	name=NULL;
	code=NULL;
	genaccount=NULL;
	costaccount=NULL;
	inaccount=NULL;
	whaccount=NULL;
	validfrom=NULL;
	validto=NULL;
	muser=NULL;
	firstrecflag=NULL;	

}
void F_SQLGetCategoryMaterial(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select * from mm_category_material order by IDCaM;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select * from mm_category_material where IDCaM=%s and NOW() between ValidFrom and ValidTo order by IDCaM;",margv);
	}
	else if (strncmp(option,"LIKE",strlen("LIKE"))==0)	
	{
		sprintf(ExecStatement,"select * from mm_category_material where NAME LIKE '%s%%' and NOW() between ValidFrom and ValidTo order by IDCaM;",margv);
	
	}
	else if (strncmp(option,"LH",strlen("LH"))==0)	
	{
		sprintf(ExecStatement,"select IDCaM,NAME from mm_category_material where IDCLASSMAT='%s' and NOW() between ValidFrom and ValidTo order by IDCaM;",margv);
	
	}	

	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLUpdateCategoryMaterial(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char* idcategory=NULL;
	char* idclass=NULL;
	char* name=NULL;
	char* code=NULL;
	char* genaccount=NULL;
	char* costaccount=NULL;
	char* inaccount=NULL;
	char* whaccount=NULL;
	char* validfrom=NULL;
	char* validto=NULL;
	char* muser=NULL;
	char* delete=NULL;	

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			idcategory=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			idclass=(char*)listpointer->MyItem;
		}	
		else if(enumargv==2)
		{
			name=(char*)listpointer->MyItem;
		}
		else if (enumargv==3)
		{
			code=(char*)listpointer->MyItem;
			if(strncmp(code,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(code,(const char*)"");
			}
		}
		else if (enumargv==4)
		{
			genaccount=(char*)listpointer->MyItem;
			if(strncmp(genaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(genaccount,(const char*)"");
			}
		}
		else if (enumargv==5)
		{
			costaccount=(char*)listpointer->MyItem;
			if(strncmp(costaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(costaccount,(const char*)"");
			}
		}
		else if (enumargv==6)
		{
			inaccount=(char*)listpointer->MyItem;
			if(strncmp(inaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(inaccount,(const char*)"");
			}
		}
		else if (enumargv==7)
		{
			whaccount=(char*)listpointer->MyItem;
			if(strncmp(whaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(whaccount,(const char*)"");
			}
		}
		else if (enumargv==8)
		{
			validfrom=(char*)listpointer->MyItem;
		}
		else if (enumargv==9)
		{
			validto=(char*)listpointer->MyItem;
		}
		else if (enumargv==10)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if (enumargv==11)
		{
			delete=(char*)listpointer->MyItem;
		}
		
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(delete,"0",strlen("0"))==0)
	{
		sprintf(ExecStatement,"delete from mm_category_material where IDCaM=%s and IDCLASSMAT=%s;",idcategory,idclass); 
	}
	else
	{
		sprintf(ExecStatement,"update mm_category_material SET IDCLASSMAT='%s',NAME='%s',CODE='%s',GEN_ACCOUNT='%s',COST_ACCOUNT='%s',INCOMMING_ACCOUNT='%s',WH_ACCOUNT='%s',ValidFrom='%s',ValidTo='%s',LastUpdate=NOW(),LastUpdateBy='%s' where IDCaM=%s and IDCLASSMAT=%s;",idclass,name,code,genaccount,costaccount,inaccount,whaccount,validfrom,validto,muser,idcategory,idclass); 
	}

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	idcategory=NULL;
	idclass=NULL;
	name=NULL;
	code=NULL;
	genaccount=NULL;
	costaccount=NULL;
	inaccount=NULL;
	whaccount=NULL;
	validfrom=NULL;
	validto=NULL;
	muser=NULL;
	delete=NULL;	
}
void F_SQLInsertGroupMaterial(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char* idcategory=NULL;
	char* name=NULL;
	char* code=NULL;
	char* genaccount=NULL;
	char* costaccount=NULL;
	char* inaccount=NULL;
	char* whaccount=NULL;
	char* validfrom=NULL;
	char* validto=NULL;
	char* muser=NULL;
	char* firstrecflag=NULL;	

	char *sql1=NULL;
	int sql1len=strlen("select IF(MAX(IDGM) IS NULL,@ag:=100,@a:=MAX(IDGM)+1) from mm_group_material where IDCATEGMAT=%s;")+4;
	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			idcategory=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			name=(char*)listpointer->MyItem;
		}
		else if (enumargv==2)
		{
			code=(char*)listpointer->MyItem;
			if(strncmp(code,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(code,(const char*)"");
			}
		}
		else if (enumargv==3)
		{
			genaccount=(char*)listpointer->MyItem;
			if(strncmp(genaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(genaccount,(const char*)"");
			}
		}
		else if (enumargv==4)
		{
			costaccount=(char*)listpointer->MyItem;
			if(strncmp(costaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(costaccount,(const char*)"");
			}
		}
		else if (enumargv==5)
		{
			inaccount=(char*)listpointer->MyItem;
			if(strncmp(inaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(inaccount,(const char*)"");
			}
		}
		else if (enumargv==6)
		{
			whaccount=(char*)listpointer->MyItem;
			if(strncmp(whaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(whaccount,(const char*)"");
			}
		}
		else if (enumargv==7)
		{
			validfrom=(char*)listpointer->MyItem;
		}
		else if (enumargv==8)
		{
			validto=(char*)listpointer->MyItem;
		}
		else if (enumargv==9)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if (enumargv==10)
		{
			firstrecflag=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(firstrecflag,"1",strlen("1"))==0)
	{
		sprintf(ExecStatement,"insert into mm_group_material (IDGM,IDCATEGMAT,NAME,CODE,GEN_ACCOUNT,COST_ACCOUNT,INCOMMING_ACCOUNT,WH_ACCOUNT,ValidFrom,ValidTo,Created,CreatedBy) VALUES(100,'%s','%s','%s','%s','%s','%s','%s','%s','%s',NOW(),'%s');",idcategory,name,code,genaccount,costaccount,inaccount,whaccount,validfrom,validto,muser); 
	}
	else
	{
		
		if(SQLExecPlus(mydata,(char*)"SET @ag:=0;",INSERT_OR_UPDATE))
		{	
			sql1=(char*)malloc(sql1len);
			memset(sql1,'\0',sql1len);
			sprintf(sql1,"select IF(MAX(IDGM) IS NULL,@ag:=100,@ag:=MAX(IDGM)+1) from mm_group_material where IDCATEGMAT=%s;",idcategory);
			if(SQLExecPlus(mydata,sql1,EXECUTE_STATEMENT))
			{
				sprintf(ExecStatement,"insert into mm_group_material (IDGM,IDCATEGMAT,NAME,CODE,GEN_ACCOUNT,COST_ACCOUNT,INCOMMING_ACCOUNT,WH_ACCOUNT,ValidFrom,ValidTo,Created,CreatedBy) VALUES(@ag,'%s','%s','%s','%s','%s','%s','%s','%s','%s',NOW(),'%s');",idcategory,name,code,genaccount,costaccount,inaccount,whaccount,validfrom,validto,muser); 
				
			}
			else
			{

				strcpy(ExecStatement,"ERR: Procedura de Incrementare");
			}
			free(sql1);
			sql1=NULL;		
		}
		else
		{

			strcpy(ExecStatement,"ERR: SET @a:=0");
		}


	}

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	idcategory=NULL;
	name=NULL;
	code=NULL;
	genaccount=NULL;
	costaccount=NULL;
	inaccount=NULL;
	whaccount=NULL;
	validfrom=NULL;
	validto=NULL;
	muser=NULL;
	firstrecflag=NULL;	
}
void F_SQLGetGroupMaterial(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select * from mm_group_material order by IDGM;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select * from mm_group_material where IDGM=%s and NOW() between ValidFrom and ValidTo order by IDGM;",margv);
	}
	else if (strncmp(option,"LIKE",strlen("LIKE"))==0)	
	{
		sprintf(ExecStatement,"select * from mm_group_material where NAME LIKE '%s%%' and NOW() between ValidFrom and ValidTo order by IDGM;",margv);
		
	}
	else if (strncmp(option,"LH",strlen("LH"))==0)	
	{
		sprintf(ExecStatement,"select IDGM,NAME from mm_group_material where IDCATEGMAT=%s and NOW() between ValidFrom and ValidTo order by IDGM;",margv);
	}
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLUpdateGroupMaterial(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char* idgroup=NULL;
	char* idcategory=NULL;
	char* name=NULL;
	char* code=NULL;
	char* genaccount=NULL;
	char* costaccount=NULL;
	char* inaccount=NULL;
	char* whaccount=NULL;
	char* validfrom=NULL;
	char* validto=NULL;
	char* muser=NULL;
	char* delete=NULL;	

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			idgroup=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			idcategory=(char*)listpointer->MyItem;
		}	
		else if(enumargv==2)
		{
			name=(char*)listpointer->MyItem;
		}
		else if (enumargv==3)
		{
			code=(char*)listpointer->MyItem;
			if(strncmp(code,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(code,(const char*)"");
			}
		}
		else if (enumargv==4)
		{
			genaccount=(char*)listpointer->MyItem;
			if(strncmp(genaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(genaccount,(const char*)"");
			}
		}
		else if (enumargv==5)
		{
			costaccount=(char*)listpointer->MyItem;
			if(strncmp(costaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(costaccount,(const char*)"");
			}
		}
		else if (enumargv==6)
		{
			inaccount=(char*)listpointer->MyItem;
			if(strncmp(inaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(inaccount,(const char*)"");
			}
		}
		else if (enumargv==7)
		{
			whaccount=(char*)listpointer->MyItem;
			if(strncmp(whaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(whaccount,(const char*)"");
			}
		}
		else if (enumargv==8)
		{
			validfrom=(char*)listpointer->MyItem;
		}
		else if (enumargv==9)
		{
			validto=(char*)listpointer->MyItem;
		}
		else if (enumargv==10)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if (enumargv==11)
		{
			delete=(char*)listpointer->MyItem;
		}
		
		listpointer=listpointer -> NextArgv; 	
	}	
	
	if(strncmp(delete,"0",strlen("0"))==0)
	{
		sprintf(ExecStatement,"delete from mm_group_material where IDGM=%s and IDCATEGMAT=%s;",idgroup,idcategory); 
	}
	else
	{
		sprintf(ExecStatement,"update mm_group_material SET IDCATEGMAT=%s,NAME='%s',CODE='%s',GEN_ACCOUNT='%s',COST_ACCOUNT='%s',INCOMMING_ACCOUNT='%s',WH_ACCOUNT='%s',ValidFrom='%s',ValidTo='%s',LastUpdate=NOW(),LastUpdateBy='%s' where IDGM=%s and IDCATEGMAT=%s;",idcategory,name,code,genaccount,costaccount,inaccount,whaccount,validfrom,validto,muser,idgroup,idcategory); 
	}

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	idgroup=NULL;
	idcategory=NULL;
	name=NULL;
	code=NULL;
	genaccount=NULL;
	costaccount=NULL;
	inaccount=NULL;
	whaccount=NULL;
	validfrom=NULL;
	validto=NULL;
	muser=NULL;
	delete=NULL;	
}
void F_SQLInsertTypeMaterial(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char* idtype=NULL;
	char* name=NULL;
	char* code=NULL;
	char* genaccount=NULL;
	char* costaccount=NULL;
	char* inaccount=NULL;
	char* whaccount=NULL;
	char* validfrom=NULL;
	char* validto=NULL;
	char* muser=NULL;
	char* firstrecflag=NULL;	
	char *sql1=NULL;
	int sql1len=strlen("select IF(MAX(IDTM) IS NULL,@at:=100,@at:=MAX(IDTM)+1) from mm_type_material where IDGROUPMAT=%s;")+4;


	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			idtype=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			name=(char*)listpointer->MyItem;
		}
		else if (enumargv==2)
		{
			code=(char*)listpointer->MyItem;
			if(strncmp(code,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(code,(const char*)"");
			}
		}
		else if (enumargv==3)
		{
			genaccount=(char*)listpointer->MyItem;
			if(strncmp(genaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(genaccount,(const char*)"");
			}
		}
		else if (enumargv==4)
		{
			costaccount=(char*)listpointer->MyItem;
			if(strncmp(costaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(costaccount,(const char*)"");
			}
		}
		else if (enumargv==5)
		{
			inaccount=(char*)listpointer->MyItem;
			if(strncmp(inaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(inaccount,(const char*)"");
			}
		}
		else if (enumargv==6)
		{
			whaccount=(char*)listpointer->MyItem;
			if(strncmp(whaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(whaccount,(const char*)"");
			}
		}
		else if (enumargv==7)
		{
			validfrom=(char*)listpointer->MyItem;
		}
		else if (enumargv==8)
		{
			validto=(char*)listpointer->MyItem;
		}
		else if (enumargv==9)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if (enumargv==10)
		{
			firstrecflag=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(firstrecflag,"1",strlen("1"))==0)
	{
		sprintf(ExecStatement,"insert into mm_type_material (IDTM,IDGROUPMAT,NAME,CODE,GEN_ACCOUNT,COST_ACCOUNT,INCOMMING_ACCOUNT,WH_ACCOUNT,ValidFrom,ValidTo,Created,CreatedBy) VALUES(100,'%s','%s','%s','%s','%s','%s','%s','%s','%s',NOW(),'%s');",idtype,name,code,genaccount,costaccount,inaccount,whaccount,validfrom,validto,muser); 
	}
	else
	{

		if(SQLExecPlus(mydata,(char*)"SET @at:=0;",INSERT_OR_UPDATE))
		{	
			sql1=(char*)malloc(sql1len);
			memset(sql1,'\0',sql1len);
			sprintf(sql1,"select IF(MAX(IDTM) IS NULL,@at:=100,@at:=MAX(IDTM)+1) from mm_type_material where IDGROUPMAT=%s;",idtype);
			if(SQLExecPlus(mydata,sql1,EXECUTE_STATEMENT))
			{
				sprintf(ExecStatement,"insert into mm_type_material (IDTM,IDGROUPMAT,NAME,CODE,GEN_ACCOUNT,COST_ACCOUNT,INCOMMING_ACCOUNT,WH_ACCOUNT,ValidFrom,ValidTo,Created,CreatedBy) VALUES(@at,'%s','%s','%s','%s','%s','%s','%s','%s','%s',NOW(),'%s');",idtype,name,code,genaccount,costaccount,inaccount,whaccount,validfrom,validto,muser); 
				
			}
			else
			{

				strcpy(ExecStatement,"ERR: Procedura de Incrementare");
			}
			free(sql1);
			sql1=NULL;		
		}
		else
		{

			strcpy(ExecStatement,"ERR: SET @a:=0");
		}
	
	}

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	idtype=NULL;
	name=NULL;
	code=NULL;
	genaccount=NULL;
	costaccount=NULL;
	inaccount=NULL;
	whaccount=NULL;
	validfrom=NULL;
	validto=NULL;
	muser=NULL;
	firstrecflag=NULL;	
}
void F_SQLGetTypeMaterial(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select * from mm_type_material order by IDTM;");
	}
	else if (strncmp(option,"=",strlen("="))==0)
	{
		sprintf(ExecStatement,"select * from mm_type_material where IDTM=%s and NOW() between ValidFrom and ValidTo order by IDTM;",margv);
	}
	else if (strncmp(option,"LIKE",strlen("LIKE"))==0)	
	{
		sprintf(ExecStatement,"select * from mm_type_material where NAME LIKE '%s%%' and NOW() between ValidFrom and ValidTo order by IDTM;",margv);
	}
	else if (strncmp(option,"LH",strlen("LH"))==0)	
	{
		sprintf(ExecStatement,"select IDTM,NAME from mm_type_material where IDGROUPMAT=%s and NOW() between ValidFrom and ValidTo order by IDTM;",margv);
	}
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLUpdateTypeMaterial(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char* idtype=NULL;
	char* idgroup=NULL;
	char* name=NULL;
	char* code=NULL;
	char* genaccount=NULL;
	char* costaccount=NULL;
	char* inaccount=NULL;
	char* whaccount=NULL;
	char* validfrom=NULL;
	char* validto=NULL;
	char* muser=NULL;
	char* delete=NULL;	

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			idtype=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			idgroup=(char*)listpointer->MyItem;
		}	
		else if(enumargv==2)
		{
			name=(char*)listpointer->MyItem;
		}
		else if (enumargv==3)
		{
			code=(char*)listpointer->MyItem;
			if(strncmp(code,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(code,(const char*)"");
			}
		}
		else if (enumargv==4)
		{
			genaccount=(char*)listpointer->MyItem;
			if(strncmp(genaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(genaccount,(const char*)"");
			}
		}
		else if (enumargv==5)
		{
			costaccount=(char*)listpointer->MyItem;
			if(strncmp(costaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(costaccount,(const char*)"");
			}
		}
		else if (enumargv==6)
		{
			inaccount=(char*)listpointer->MyItem;
			if(strncmp(inaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(inaccount,(const char*)"");
			}
		}
		else if (enumargv==7)
		{
			whaccount=(char*)listpointer->MyItem;
			if(strncmp(whaccount,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(whaccount,(const char*)"");
			}
		}
		else if (enumargv==8)
		{
			validfrom=(char*)listpointer->MyItem;
		}
		else if (enumargv==9)
		{
			validto=(char*)listpointer->MyItem;
		}
		else if (enumargv==10)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if (enumargv==11)
		{
			delete=(char*)listpointer->MyItem;
		}
		
		listpointer=listpointer -> NextArgv; 	
	}	

	if(strncmp(delete,"0",strlen("0"))==0)
	{
		sprintf(ExecStatement,"delete from mm_type_material where IDTM=%s and IDGROUPMAT=%s;",idtype,idgroup); 
	}
	else
	{	
		sprintf(ExecStatement,"update mm_type_material SET NAME='%s',CODE='%s',GEN_ACCOUNT='%s',COST_ACCOUNT='%s',INCOMMING_ACCOUNT='%s',WH_ACCOUNT='%s',ValidFrom='%s',ValidTo='%s',LastUpdate=NOW(),LastUpdateBy='%s' where IDTM=%s and  IDGROUPMAT=%s;",name,code,genaccount,costaccount,inaccount,whaccount,validfrom,validto,muser,idtype,idgroup);
	}

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	idtype=NULL;
	idgroup=NULL;
	name=NULL;
	code=NULL;
	genaccount=NULL;
	costaccount=NULL;
	inaccount=NULL;
	whaccount=NULL;
	validfrom=NULL;
	validto=NULL;
	muser=NULL;
	delete=NULL;	
}
int SQLExec(int s,MYSQL* myData,char* myQuery,SQL_EXEC_OPTIONS mExecOption){


	MYSQL_RES *mRes;
	MYSQL_FIELD *mFields;
	MYSQL_ROW mRow;
	long nrRows=0,nrFields=0,i=0;
	long x=0;
	char *mBuff=NULL;
	char *mbs=NULL,*tmpc=NULL;
	char *MYSQLerr=NULL;
	char *mbss=NULL;
	char *p=NULL;
	char *p1=NULL;	
	char *p2=NULL;
	char *mb=NULL;
	char mCMD[64];
	char mno[16];
	int USER_ID=0;
	int zz=0;
	unsigned long *lengths;
	unsigned int totallen;
	unsigned int new_amount=0;
	int mylen=0;	
	long myaffrows=0;
	memset(mno,'\0',16);
	memset(mCMD,'\0',64);

		
	
	if((mysql_real_query(myData,myQuery,strlen(myQuery)))<0)
	{
		
		if(strncmp(myQuery,"ERR",3)==0)
		{
			mbs=PrepareBuff2SendData(strlen(myQuery),myQuery,&mylen);
			
		}
		else
		{
			MYSQLerr=(char*)mysql_error(myData);
			mbs=PrepareBuff2SendData(strlen(MYSQLerr),MYSQLerr,&mylen);
		}
		
		zz=send_cmd(s,10,mbs,(long)mylen,MY_ASCII_DATA);
		free(mbs);
		mbs=NULL; //paranoia
		
	
		return(-1);
	}
	
	if(mExecOption==INSERT_OR_UPDATE)
	{
		myaffrows=mysql_affected_rows(myData);
		if(s>0)
		{
			
			sprintf(mno,"%lu",myaffrows);
			mbs=PrepareBuff2SendData(strlen(mno),mno,&mylen);
			zz=send_cmd(s,10,mbs,(long)mylen,MY_ASCII_DATA);
			free(mbs);
			mbs=NULL; //paranoia
			return myaffrows;
		}
		else
		{
			return myaffrows;
		}
	}

	mRes=mysql_store_result(myData);
	

	if(!mRes)
	{
		USER_ID=-1;	
		goto myEND;
	}
	nrRows=mysql_num_rows(mRes);
	if(nrRows==0)
	{
		goto myEND;
	}
	nrFields=mysql_num_fields(mRes);

	sprintf(mno,"%lu,%lu",nrRows,nrFields);	
	WaitReply(s,strlen(mno),mno,mCMD);
	if(memcmp(mCMD,CMD_OPTION_BREAK,strlen(CMD_OPTION_BREAK))==0)
	{
			goto myEND;
	}
	memset(mno,'\0',16);
	
	
	if(memcmp(mCMD,CMD_OPTION_FETCHTFIELD,strlen(CMD_OPTION_FETCHTFIELD))==0)
	{
		
		mbss=(char*)malloc(16);	
		memset(mbss,'\0',16);
		new_amount=0;	
		
		for(i=0;i<nrFields;i++)
		{
			
			mFields=mysql_fetch_field(mRes);
			
			
			if(i==nrFields-1)
			{
				tmpc=concat(mbss,mFields->name,(char*)0);
			}
			else
			{
				tmpc=concat(mbss,mFields->name,",",(char*)0);
			}
			p1=tmpc;
			new_amount=(strlen(tmpc)*sizeof(char))+1;	
			p=realloc(mbss,new_amount);
			memset(p,'\0',new_amount);
			p2=p;
			while((*p++=*tmpc++)!='\0');
			tmpc=p1;
			p+='\0';
			p=p2;
			mbss=p;
			free(tmpc);
			tmpc=NULL;
			p1=NULL;
			
		}
		
		WaitReply(s,strlen(mbss),mbss,mCMD);
		free(mbss);
		mbss=NULL;
		p=NULL;
		p2=NULL;
		memset(mCMD,'\0',64);
		mFields=NULL;
		i=0;
		if(memcmp(mCMD,CMD_OPTION_BREAK,strlen(CMD_OPTION_BREAK))==0)
		{
			goto myEND;
		}
		
	}


	while ((mRow = mysql_fetch_row(mRes)))
	{

		if(!mRow)
		{
			goto myEND;
		}
		x++;
		lengths=mysql_fetch_lengths(mRes);
		totallen=0;
		
		mbss=(char*)malloc(16);	
		memset(mbss,'\0',16);
		new_amount=0;
		for(i=0;i<nrFields;i++)
		{
			totallen+=lengths[i];	
			
			mBuff=mRow[i] ? mRow[i] : " ";	
			
			if(i==nrFields-1)
			{
				tmpc=concat(mbss,mBuff,(char*)0);
			}
			else
			{
				tmpc=concat(mbss,mBuff,",",(char*)0);
			}
			
			p1=tmpc;
			new_amount=(strlen(tmpc)*sizeof(char))+1;	
			p=realloc(mbss,new_amount);
			memset(p,'\0',new_amount);
			p2=p;
			while((*p++=*tmpc++)!='\0');
			tmpc=p1;
			p+='\0';
			p=p2;
			mbss=p;
			
			free(tmpc);
			tmpc=NULL;
			p1=NULL;
			mBuff='\0';
						
		}
		
		WaitReply(s,strlen(mbss),mbss,mCMD);
		if(memcmp(mCMD,CMD_OPTION_BREAK,strlen(CMD_OPTION_BREAK))==0)
		{
			break;
		}
		
		memset(mCMD,'\0',64);
		free(mbss);
		mbss=NULL;
		p=NULL;
		p2=NULL;
	}

myEND:
	
	mb=NULL;
	mb=(char*)PrepareBuff2SendData(strlen(MY_EOR),MY_EOR,&mylen);
	zz=send_cmd(s,10,mb,(long)mylen,MY_ASCII_DATA);
	free(mb);
	mb=NULL;
	mFields=NULL;
	mRow=NULL;
	mysql_free_result(mRes);
	return USER_ID;

}

