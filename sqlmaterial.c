#include "include/sqlfunction.h"
extern int SQLExec(int,MYSQL*,char*,SQL_EXEC_OPTIONS);
void F_SQLInsertMaterialGeneral(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *uniquecode=NULL;	
	char *name=NULL;
	char *commercial=NULL;
	char *mattype=NULL;
	char *canalytic=NULL;
	char *cdue=NULL;
	char *cincomme=NULL;
	char *cwh=NULL;
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
			uniquecode=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			name=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			commercial=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			mattype=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			canalytic=(char*)listpointer->MyItem;
			if(strncmp(canalytic,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(canalytic,(const char*)"");
			}
	
		}
		else if(enumargv==5)
		{
			cdue=(char*)listpointer->MyItem;
			if(strncmp(cdue,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(cdue,(const char*)"");
			}
		}
		else if(enumargv==6)
		{
			cincomme=(char*)listpointer->MyItem;
			if(strncmp(cincomme,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(cincomme,(const char*)"");
			}
		}
		else if(enumargv==7)
		{
			cwh=(char*)listpointer->MyItem;
			if(strncmp(cwh,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(cwh,(const char*)"");
			}
		}
		else if(enumargv==8)
		{
			vfrom=(char*)listpointer->MyItem;
		}
		else if(enumargv==9)
		{
			vto=(char*)listpointer->MyItem;
		}
		else if(enumargv==10)
		{
			muser=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv; 	
	}	
	
	sprintf(ExecStatement,"insert into mm_material_general (MNAME,UNIQUE_CODE,TYPE_PROD,COMMERCIAL_CODE,ACC_ANALYTIC,ACC_DUE,ACC_INCOMMING,ACC_WH,ValidFrom,ValidTo,Created,CreatedBy) VALUES('%s',%s,'%s','%s','%s','%s','%s','%s','%s','%s',NOW(),'%s');",name,uniquecode,mattype,commercial,canalytic,cdue,cincomme,cwh,vfrom,vto,muser); 

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	uniquecode=NULL;	
	name=NULL;
	commercial=NULL;
	mattype=NULL;
	canalytic=NULL;
	cdue=NULL;
	cincomme=NULL;
	cwh=NULL;
    vfrom=NULL;
	vto=NULL;
	muser=NULL;
}
void F_SQLGetMaterialGeneral(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{

	int enumargv=0;
	char *option=NULL;
	char *margv=NULL;
	char ExecStatement[2048];
	memset(ExecStatement,'\0',2048);	

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
		sprintf(ExecStatement,"SELECT mm_material_general.IDMG,mm_material_general.MNAME,mm_material_general.UNIQUE_CODE,CONCAT(mm_class_material.NAME,' ',mm_category_material.NAME,' ',mm_group_material.NAME,' ',mm_type_material.NAME) AS encode,mm_material_general.TYPE_PROD,mm_material_general.COMMERCIAL_CODE,mm_material_general.ACC_ANALYTIC,mm_material_general.ACC_DUE,mm_material_general.ACC_INCOMMING,mm_material_general.ACC_WH,mm_material_general.ValidFrom,mm_material_general.ValidTo,mm_material_general.Created,mm_material_general.CreatedBy,mm_material_general.LastUpdate,mm_material_general.LastUpdateBy FROM mm_material_general LEFT JOIN(mm_class_material,mm_category_material,mm_group_material,mm_type_material) ON (mm_class_material.IDCM=ROUND(mm_material_general.UNIQUE_CODE/POW(10,9),0) AND mm_category_material.IDCaM=ROUND(ROUND(ROUND(((mm_material_general.UNIQUE_CODE-(mm_material_general.UNIQUE_CODE%%1000))/1000),0)-(ROUND((mm_material_general.UNIQUE_CODE-(mm_material_general.UNIQUE_CODE%%1000))/1000,0)%%1000),0)/1000,0)%%1000 AND mm_group_material.IDGM=ROUND((mm_material_general.UNIQUE_CODE-(mm_material_general.UNIQUE_CODE%%1000))/1000,0)%%1000 AND mm_type_material.IDTM=mm_material_general.UNIQUE_CODE%%1000 AND mm_class_material.IDCM=mm_category_material.IDCLASSMAT AND mm_category_material.IDCaM=mm_group_material.IDCATEGMAT AND mm_type_material.IDGROUPMAT) WHERE NOW() BETWEEN mm_material_general.ValidFrom AND mm_material_general.ValidTo GROUP BY mm_material_general.IDMG;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
	
		sprintf(ExecStatement,"SELECT mm_material_general.IDMG,mm_material_general.MNAME,mm_material_general.UNIQUE_CODE,CONCAT(mm_class_material.NAME,' ',mm_category_material.NAME,' ',mm_group_material.NAME,' ',mm_type_material.NAME) AS encode,mm_material_general.TYPE_PROD,mm_material_general.COMMERCIAL_CODE,mm_material_general.ACC_ANALYTIC,mm_material_general.ACC_DUE,mm_material_general.ACC_INCOMMING,mm_material_general.ACC_WH,mm_material_general.ValidFrom,mm_material_general.ValidTo,mm_material_general.Created,mm_material_general.CreatedBy,mm_material_general.LastUpdate,mm_material_general.LastUpdateBy FROM mm_material_general LEFT JOIN(mm_class_material,mm_category_material,mm_group_material,mm_type_material) ON (mm_class_material.IDCM=ROUND(mm_material_general.UNIQUE_CODE/POW(10,9),0) AND mm_category_material.IDCaM=ROUND(ROUND(ROUND(((mm_material_general.UNIQUE_CODE-(mm_material_general.UNIQUE_CODE%%1000))/1000),0)-(ROUND((mm_material_general.UNIQUE_CODE-(mm_material_general.UNIQUE_CODE%%1000))/1000,0)%%1000),0)/1000,0)%%1000 AND mm_group_material.IDGM=ROUND((mm_material_general.UNIQUE_CODE-(mm_material_general.UNIQUE_CODE%%1000))/1000,0)%%1000 AND mm_type_material.IDTM=mm_material_general.UNIQUE_CODE%%1000 AND mm_class_material.IDCM=mm_category_material.IDCLASSMAT AND mm_category_material.IDCaM=mm_group_material.IDCATEGMAT AND mm_type_material.IDGROUPMAT) WHERE mm_material_general.IDMG=%s AND NOW() BETWEEN mm_material_general.ValidFrom AND mm_material_general.ValidTo GROUP BY mm_material_general.IDMG;",margv);
	}
	else if (strncmp(option,"LIKE",strlen("LIKE"))==0)	
	{
		
		sprintf(ExecStatement,"SELECT mm_material_general.IDMG,mm_material_general.MNAME,mm_material_general.UNIQUE_CODE,CONCAT(mm_class_material.NAME,' ',mm_category_material.NAME,' ',mm_group_material.NAME,' ',mm_type_material.NAME) AS encode,mm_material_general.TYPE_PROD,mm_material_general.COMMERCIAL_CODE,mm_material_general.ACC_ANALYTIC,mm_material_general.ACC_DUE,mm_material_general.ACC_INCOMMING,mm_material_general.ACC_WH,mm_material_general.ValidFrom,mm_material_general.ValidTo,mm_material_general.Created,mm_material_general.CreatedBy,mm_material_general.LastUpdate,mm_material_general.LastUpdateBy FROM mm_material_general LEFT JOIN(mm_class_material,mm_category_material,mm_group_material,mm_type_material) ON (mm_class_material.IDCM=ROUND(mm_material_general.UNIQUE_CODE/POW(10,9),0) AND mm_category_material.IDCaM=ROUND(ROUND(ROUND(((mm_material_general.UNIQUE_CODE-(mm_material_general.UNIQUE_CODE%%1000))/1000),0)-(ROUND((mm_material_general.UNIQUE_CODE-(mm_material_general.UNIQUE_CODE%%1000))/1000,0)%%1000),0)/1000,0)%%1000 AND mm_group_material.IDGM=ROUND((mm_material_general.UNIQUE_CODE-(mm_material_general.UNIQUE_CODE%%1000))/1000,0)%%1000 AND mm_type_material.IDTM=mm_material_general.UNIQUE_CODE%%1000 AND mm_class_material.IDCM=mm_category_material.IDCLASSMAT AND mm_category_material.IDCaM=mm_group_material.IDCATEGMAT AND mm_type_material.IDGROUPMAT) WHERE mm_material_general.MNAME LIKE '%s%%' and NOW() between mm_material_general.ValidFrom and mm_material_general.ValidTo GROUP by mm_material_general.IDMG;",margv);
	}
	else if (strncmp(option,"CODE",strlen("CODE"))==0)	
	{
		
		sprintf(ExecStatement,"SELECT mm_material_general.IDMG,mm_material_general.MNAME,mm_material_general.UNIQUE_CODE,CONCAT(mm_class_material.NAME,' ',mm_category_material.NAME,' ',mm_group_material.NAME,' ',mm_type_material.NAME) AS encode,mm_material_general.TYPE_PROD,mm_material_general.COMMERCIAL_CODE,mm_material_general.ACC_ANALYTIC,mm_material_general.ACC_DUE,mm_material_general.ACC_INCOMMING,mm_material_general.ACC_WH,mm_material_general.ValidFrom,mm_material_general.ValidTo,mm_material_general.Created,mm_material_general.CreatedBy,mm_material_general.LastUpdate,mm_material_general.LastUpdateBy FROM mm_material_general LEFT JOIN(mm_class_material,mm_category_material,mm_group_material,mm_type_material) ON (mm_class_material.IDCM=ROUND(mm_material_general.UNIQUE_CODE/POW(10,9),0) AND mm_category_material.IDCaM=ROUND(ROUND(ROUND(((mm_material_general.UNIQUE_CODE-(mm_material_general.UNIQUE_CODE%%1000))/1000),0)-(ROUND((mm_material_general.UNIQUE_CODE-(mm_material_general.UNIQUE_CODE%%1000))/1000,0)%%1000),0)/1000,0)%%1000 AND mm_group_material.IDGM=ROUND((mm_material_general.UNIQUE_CODE-(mm_material_general.UNIQUE_CODE%%1000))/1000,0)%%1000 AND mm_type_material.IDTM=mm_material_general.UNIQUE_CODE%%1000 AND mm_class_material.IDCM=mm_category_material.IDCLASSMAT AND mm_category_material.IDCaM=mm_group_material.IDCATEGMAT AND mm_type_material.IDGROUPMAT) WHERE mm_material_general.UNIQUE_CODE=%s and NOW() between mm_material_general.ValidFrom and mm_material_general.ValidTo GROUP by mm_material_general.IDMG;",margv);
	}
	else if (strncmp(option,"LH",strlen("LH"))==0)	
	{
		sprintf(ExecStatement,"select IDMG,COMMERCIAL_CODE,MNAME from mm_material_general where UNIQUE_CODE=%s and NOW() between ValidFrom and ValidTo order by IDMG;",margv);
	}
	else if(strncmp(option,"LC",strlen("LC"))==0)	
	{
		sprintf(ExecStatement,"select IDMG,MNAME from mm_material_general where NOW() between ValidFrom and ValidTo order by IDMG;");
	}
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',2048);	
	option=NULL;
	margv=NULL;
}
void F_SQLUpdateMaterialGeneral(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *IDMAT=NULL;
	char *name=NULL;
	char *commercial=NULL;
	char *canalytic=NULL;
	char *cdue=NULL;
	char *cincomme=NULL;
	char *cwh=NULL;
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
			IDMAT=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			name=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			commercial=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			canalytic=(char*)listpointer->MyItem;
			if(strncmp(canalytic,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(canalytic,(const char*)"");
			}
	
		}
		else if(enumargv==4)
		{
			cdue=(char*)listpointer->MyItem;
			if(strncmp(cdue,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(cdue,(const char*)"");
			}
		}
		else if(enumargv==5)
		{
			cincomme=(char*)listpointer->MyItem;
			if(strncmp(cincomme,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(cincomme,(const char*)"");
			}
		}
		else if(enumargv==6)
		{
			cwh=(char*)listpointer->MyItem;
			if(strncmp(cwh,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(cwh,(const char*)"");
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
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv; 	
	}	
	
	if(strncmp(delete,"0",strlen("0"))==0)
	{
		sprintf(ExecStatement,"delete from mm_material_general where IDMG=%s;",IDMAT); 
	}
	else
	{	
		sprintf(ExecStatement,"update mm_material_general SET MNAME='%s',COMMERCIAL_CODE='%s',ACC_ANALYTIC='%s',ACC_DUE='%s',ACC_INCOMMING='%s',ACC_WH='%s',ValidFrom='%s',ValidTo='%s',LastUpdate=NOW(),LastUpdateBy='%s' where IDMG=%s ;",name,commercial,canalytic,cdue,cincomme,cwh,vfrom,vto,muser,IDMAT);
	}
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	IDMAT=NULL;
	name=NULL;
	commercial=NULL;
	canalytic=NULL;
	cdue=NULL;
	cincomme=NULL;
	cwh=NULL;
        vfrom=NULL;
	vto=NULL;
	muser=NULL;
	delete=NULL;
}
void F_SQLInsertMaterialPriceList(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *idmaterial=NULL;	
	char *uniqreg=NULL;
	char *whcode=NULL;
	char *maxprice=NULL;
	char *cmdmin=NULL;
	char *cmdmax=NULL;
	char *promisedtime=NULL;
	char *accincome=NULL;
	char *acccost=NULL;
	char *status=NULL;
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
			idmaterial=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			uniqreg=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			whcode=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			maxprice=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			cmdmin=(char*)listpointer->MyItem;
		}
		else if(enumargv==5)
		{
			cmdmax=(char*)listpointer->MyItem;
		}
		else if(enumargv==6)
		{
			promisedtime=(char*)listpointer->MyItem;
		}	
		else if(enumargv==7)
		{
			accincome=(char*)listpointer->MyItem;
			if(strncmp(accincome,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(accincome,(const char*)"");
			}
	
		}
		else if(enumargv==8)
		{
			acccost=(char*)listpointer->MyItem;
			if(strncmp(acccost,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(acccost,(const char*)"");
			}
		}
		else if(enumargv==9)
		{
			status=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==10)
		{
			vfrom=(char*)listpointer->MyItem;
		}
		else if(enumargv==11)
		{
			vto=(char*)listpointer->MyItem;
		}
		else if(enumargv==12)
		{
			muser=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv; 	
	}	
	
	sprintf(ExecStatement,"insert into mm_material_purchase (IDMAT,PARTUNIQUEREG,WHCODE,MAXPRICE,MINQTYCMD,MAXQTYCMD,PROMISEDTIME,ACC_INCOME,ACC_COST,STATUS,ValidFrom,ValidTo,Created,CreatedBy) VALUES('%s','%s','%s',%s,%s,%s,%s,'%s','%s','%s','%s','%s',NOW(),'%s');",idmaterial,uniqreg,whcode,maxprice,cmdmin,cmdmax,promisedtime,accincome,acccost,status,vfrom,vto,muser); 

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	idmaterial=NULL;	
	uniqreg=NULL;
	whcode=NULL;
	maxprice=NULL;
	cmdmin=NULL;
	cmdmax=NULL;
	promisedtime=NULL;
	accincome=NULL;
	acccost=NULL;
	status=NULL;
	vfrom=NULL;
	vto=NULL;
	muser=NULL;

}
void F_SQLGetMaterialPriceList(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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

		sprintf(ExecStatement,"select * from mm_material_purchase WHERE NOW() BETWEEN ValidFrom AND ValidTo order by IDMP;");
	}
	else if (strncmp(option,"=",strlen("="))==0)
	{
		
		sprintf(ExecStatement,"select * from mm_material_purchase WHERE PARTUNIQUEREG='%s' and NOW() BETWEEN ValidFrom AND ValidTo order by IDMP;",margv);
	}
	else if (strncmp(option,"XP",strlen("XP"))==0)	
	{
		sprintf(ExecStatement,"select MAXPRICE from mm_material_purchase WHERE PARTUNIQUEREG='%s' and NOW() BETWEEN ValidFrom AND ValidTo order by IDMP;",margv);
	}
	else if (strncmp(option,"LX",strlen("LX"))==0)	
	{
		sprintf(ExecStatement,"select * from mm_material_purchase WHERE IDMAT='%s' order by IDMP;",margv);
	}	

	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLUpdateMaterialPriceList(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *idmaterial=NULL;	
	char *uniqreg=NULL;
	char *whcode=NULL;
	char *maxprice=NULL;
	char *mincmd=NULL;
	char *maxcmd=NULL;
	char *promisedtime=NULL;
	char *accincome=NULL;
	char *acccost=NULL;
	char *status=NULL;
	char *vfrom=NULL;
	char *vto=NULL;
	char *muser=NULL;
	char *idplist=NULL;
	char *delete=NULL;

	char ExecStatement[1024];
	memset(ExecStatement,'\0',1024);	

     	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;

	for(enumargv=0;enumargv<msess->FunctionToHandle->HowManyArgv;enumargv++)
	{
		if(enumargv==0)
		{
			idmaterial=(char*)listpointer->MyItem;
		}	
		else if(enumargv==1)
		{
			uniqreg=(char*)listpointer->MyItem;
		}
		else if(enumargv==2)
		{
			whcode=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			maxprice=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			mincmd=(char*)listpointer->MyItem;
		}
		else if(enumargv==5)
		{
			maxcmd=(char*)listpointer->MyItem;
		}
		else if(enumargv==6)
		{
			promisedtime=(char*)listpointer->MyItem;
		}	
		else if(enumargv==7)
		{
			accincome=(char*)listpointer->MyItem;
			if(strncmp(accincome,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(accincome,(const char*)"");
			}
	
		}
		else if(enumargv==8)
		{
			acccost=(char*)listpointer->MyItem;
			if(strncmp(acccost,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(acccost,(const char*)"");
			}
		}
		else if(enumargv==9)
		{
			status=(char*)listpointer->MyItem;
			
		}
		else if(enumargv==10)
		{
			vfrom=(char*)listpointer->MyItem;
		}
		else if(enumargv==11)
		{
			vto=(char*)listpointer->MyItem;
		}
		else if(enumargv==12)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if(enumargv==13)
		{
			idplist=(char*)listpointer->MyItem;
		}
		else if(enumargv==14)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv; 	
	}	
	if(strncmp(delete,"0",strlen("0"))==0)
	{
		sprintf(ExecStatement,"delete from mm_material_purchase where IDMP=%s;",idplist); 
	}
	else
	{	
		sprintf(ExecStatement,"update mm_material_purchase SET IDMAT='%s',PARTUNIQUEREG='%s',WHCODE='%s',MAXPRICE=%s,MINQTYCMD=%s,MAXQTYCMD=%s,PROMISEDTIME=%s,ACC_INCOME='%s',ACC_COST='%s',STATUS='%s',ValidFrom='%s',ValidTo='%s',LastUpdate=NOW(),LastUpdateBy='%s' where IDMP=%s;",idmaterial,uniqreg,whcode,maxprice,mincmd,maxcmd,promisedtime,accincome,acccost,status,vfrom,vto,muser,idplist); 
	}
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	idmaterial=NULL;	
	uniqreg=NULL;
	whcode=NULL;
	maxprice=NULL;
	mincmd=NULL;
	maxcmd=NULL;
	promisedtime=NULL;
	accincome=NULL;
	acccost=NULL;
	status=NULL;
	vfrom=NULL;
	vto=NULL;
	muser=NULL;
	idplist=NULL;
	delete=NULL;

}
void F_SQLInUpMaterialSuppCode(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *isinsert=NULL;
	char *idmaterial=NULL;	
	char *uniqreg=NULL;
	char *suppcode=NULL;
	char *startread=NULL;
	char *readlen=NULL;
	char *description=NULL;
	char *qty=NULL;
	char *muser=NULL;
	char *idlist=NULL;
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
			idmaterial=(char*)listpointer->MyItem;
		}	
		else if(enumargv==2)
		{
			uniqreg=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			suppcode=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			startread=(char*)listpointer->MyItem;
		}	
		else if(enumargv==5)
		{
			readlen=(char*)listpointer->MyItem;
		}
		else if(enumargv==6)
		{
			description=(char*)listpointer->MyItem;
		}
		else if(enumargv==7)
		{
			qty=(char*)listpointer->MyItem;
		}
		else if(enumargv==8)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if(enumargv==9)
		{
			idlist=(char*)listpointer->MyItem;
		}
		else if(enumargv==10)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(isinsert,"1",strlen("1"))==0)	
	{
		sprintf(ExecStatement,"insert into mm_material_suppcode (IDMAT,PARTUNIQUEREG,SUPPLIERCODE,STARTREAD,READLEN,DESCRIPTION,QTY,Created,CreatedBy) VALUES('%s','%s','%s',%s,%s,'%s',%s,NOW(),'%s');",idmaterial,uniqreg,suppcode,startread,readlen,description,qty,muser); 

	}
	else
	{
		if(strncmp(delete,"0",strlen("0"))==0)
		{
			sprintf(ExecStatement,"delete from mm_material_suppcode where IDMS=%s;",idlist); 
		}
		else
		{
			sprintf(ExecStatement,"update mm_material_suppcode SET IDMAT='%s',PARTUNIQUEREG='%s',SUPPLIERCODE='%s',STARTREAD=%s,READLEN=%s,DESCRIPTION='%s',QTY=%s,LastUpdate=NOW(),LastUpdateBy='%s' where IDMS=%s;",idmaterial,uniqreg,suppcode,startread,readlen,description,qty,muser,idlist); 
		}	
	}
			
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);
	
	memset(ExecStatement,'\0',1024);	
	isinsert=NULL;
	idmaterial=NULL;	
	uniqreg=NULL;
	suppcode=NULL;
	startread=NULL;
	readlen=NULL;
	description=NULL;
	qty=NULL;
	muser=NULL;
	idlist=NULL;
	delete=NULL;
}
void F_SQLGetMaterialSuppCode(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select * from mm_material_suppcode order by IDMS;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select * from mm_material_suppcode WHERE PARTUNIQUEREG='%s' order by IDMS;",margv);
	}
	else if (strncmp(option,"LX",strlen("LX"))==0)	
	{
		sprintf(ExecStatement,"select * from mm_material_suppcode WHERE IDMAT='%s' order by IDMS;",margv);
	}
	else if (strncmp(option,"SLX",strlen("SLX"))==0)	
	{
		sprintf(ExecStatement,"select * from mm_material_suppcode WHERE SUPPLIERCODE='%s' order by IDMS;",margv);
	}	

	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLInUpMaterialPF(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *isinsert=NULL;
	char *idmaterial=NULL;	
	char *uniqreg=NULL;
	char *description=NULL;
	char *buom=NULL;
	char *auom=NULL;
	char *ratio=NULL;
	char *matoper=NULL;
	char *width=NULL;
	char *height=NULL;
	char *weight=NULL;
	char *volume=NULL;
	char *inwh=NULL;
	char *outwh=NULL;
	char *muser=NULL;
	char *idpf=NULL;
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
			idmaterial=(char*)listpointer->MyItem;
		}	
		else if(enumargv==2)
		{
			uniqreg=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			description=(char*)listpointer->MyItem;	
		}
		else if(enumargv==4)
		{
			buom=(char*)listpointer->MyItem;	
		}
		else if(enumargv==5)
		{
			auom=(char*)listpointer->MyItem;
			if(strncmp(auom,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(auom,(const char*)"");
			}	
		}
		else if(enumargv==6)
		{
			ratio=(char*)listpointer->MyItem;	
			
		}
		else if(enumargv==7)
		{
			matoper=(char*)listpointer->MyItem;	
			if(strncmp(matoper,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(matoper,(const char*)"");
			}
		}
		else if(enumargv==8)
		{
			width=(char*)listpointer->MyItem;	
		}
		else if(enumargv==9)
		{
			height=(char*)listpointer->MyItem;	
		}
		else if(enumargv==10)
		{
			weight=(char*)listpointer->MyItem;	
		}
		else if(enumargv==11)
		{
			volume=(char*)listpointer->MyItem;	
		}
		else if(enumargv==12)
		{
			inwh=(char*)listpointer->MyItem;	
		}
		else if(enumargv==13)
		{
			outwh=(char*)listpointer->MyItem;	
		}
		else if(enumargv==14)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if(enumargv==15)
		{
			idpf=(char*)listpointer->MyItem;
		}
		else if(enumargv==16)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(isinsert,"1",strlen("1"))==0)	
	{
		sprintf(ExecStatement,"insert into mm_material_PF(IDMAT,PARTUNIQUEREG,PFDESCRIPTION,BASEUOM,CONVERTUOM,RATIO,MATHOPER,WIDTH,HEIGHT,WEIGHT,VOLUME,INWH,OUTWH,Created,CreatedBy) VALUES(%s,'%s','%s','%s','%s',%s,'%s',%s,%s,%s,%s,%s,%s,NOW(),'%s');",idmaterial,uniqreg,description,buom,auom,ratio,matoper,width,height,weight,volume,inwh,outwh,muser); 
	}
	else
	{
		if(strncmp(delete,"0",strlen("0"))==0)
		{
			sprintf(ExecStatement,"delete from mm_material_PF where IDPF=%s;",idpf); 
		}
		else
		{
			sprintf(ExecStatement,"update mm_material_PF SET IDMAT=%s,PARTUNIQUEREG='%s',PFDESCRIPTION='%s',BASEUOM='%s',CONVERTUOM='%s',RATIO=%s,MATHOPER='%s',WIDTH=%s,HEIGHT=%s,WEIGHT=%s,VOLUME=%s,INWH=%s,OUTWH=%s,LastUpdate=NOW(),LastUpdateBy='%s' where IDPF=%s;",idmaterial,uniqreg,description,buom,auom,ratio,matoper,width,height,weight,volume,inwh,outwh,muser,idpf); 
	 
		}	
	}
			
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);

	isinsert=NULL;
	idmaterial=NULL;	
	uniqreg=NULL;
	description=NULL;
	buom=NULL;
	auom=NULL;
	ratio=NULL;
	matoper=NULL;
	width=NULL;
	height=NULL;
	weight=NULL;
	volume=NULL;
	inwh=NULL;
	outwh=NULL;
	muser=NULL;
	idpf=NULL;
	delete=NULL;

}
void F_SQLGetMaterialPF(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select * from mm_material_PF order by IDPF;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select * from mm_material_PF WHERE PARTUNIQUEREG='%s' order by IDPF;",margv);
	}
	else if (strncmp(option,"LX",strlen("LX"))==0)	
	{
		sprintf(ExecStatement,"select * from mm_material_PF WHERE IDMAT='%s' order by IDPF;",margv);
	}
	else if (strncmp(option,"SLX",strlen("SLX"))==0)	
	{
		sprintf(ExecStatement,"select * from mm_material_PF WHERE PFDESCRIPTION LIKE '%s%%' order by IDPF;",margv);
	}	

	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLInUpMaterialWH(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *isinsert=NULL;
	char *idmaterial=NULL;	
	char *uniqreg=NULL;
	char *stocmin=NULL;
	char *stocmax=NULL;
	char *storagemin=NULL;
	char *storagemax=NULL;
	char *negstock=NULL;
	char *demotion=NULL;
	char *demotionut=NULL;
	char *perisabil=NULL;
	char *validtime=NULL;
	char *codewh=NULL;
	char *codecc=NULL;
	char *acc_wh=NULL;
	char *acc_income=NULL;
	char *acc_cost=NULL;
	char *status=NULL;
	char *statustype=NULL;
	char *vfrom=NULL;
	char *vto=NULL;
	char *id=NULL;
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
			idmaterial=(char*)listpointer->MyItem;
		}	
		else if(enumargv==2)
		{
			uniqreg=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			stocmin=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			stocmax=(char*)listpointer->MyItem;
		}
		else if(enumargv==5)
		{
			storagemin=(char*)listpointer->MyItem;
		}
		else if(enumargv==6)
		{
			storagemax=(char*)listpointer->MyItem;
		}
		else if(enumargv==7)
		{
			negstock=(char*)listpointer->MyItem;
		}
		else if(enumargv==8)
		{
			demotion=(char*)listpointer->MyItem;
		}
		else if(enumargv==9)
		{
			demotionut=(char*)listpointer->MyItem;
		}
		else if(enumargv==10)
		{
			perisabil=(char*)listpointer->MyItem;
		}
		else if(enumargv==11)
		{
			validtime=(char*)listpointer->MyItem;
		}
		else if(enumargv==12)
		{
			codewh=(char*)listpointer->MyItem;
			if(strncmp(codewh,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(codewh,(const char*)"");
			}
		}
		else if(enumargv==13)
		{
			codecc=(char*)listpointer->MyItem;
			if(strncmp(codecc,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(codecc,(const char*)"");
			}
		}
		else if(enumargv==14)
		{
			acc_wh=(char*)listpointer->MyItem;
			if(strncmp(acc_wh,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(acc_wh,(const char*)"");
			}
		}
		else if(enumargv==15)
		{
			acc_income=(char*)listpointer->MyItem;
			if(strncmp(acc_income,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(acc_income,(const char*)"");
			}
		}
		else if(enumargv==16)
		{
			acc_cost=(char*)listpointer->MyItem;
			if(strncmp(acc_cost,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(acc_cost,(const char*)"");
			}
		}
		else if(enumargv==17)
		{
			status=(char*)listpointer->MyItem;
		}
		else if(enumargv==18)
		{
			statustype=(char*)listpointer->MyItem;
		}
		else if(enumargv==19)
		{
			vfrom=(char*)listpointer->MyItem;
		}
		else if(enumargv==20)
		{
			vto=(char*)listpointer->MyItem;
		}
		else if(enumargv==21)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if(enumargv==22)
		{
			id=(char*)listpointer->MyItem;
		}
		else if(enumargv==23)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(isinsert,"1",strlen("1"))==0)	
	{
		sprintf(ExecStatement,"insert into mm_material_wh(IDMAT,PARTUNIQUEREG,StocMIN,StocMAX,StorageMINTime,StorageMAXTime,NegativeStock,DemotionQTY,DemotionUnitTime,Perisabil,ValidTime,CODEWH,CODECENTERCOST,ACC_WH,ACC_INCOME,ACC_COST,STATUS,STATUSTYPE,ValidFrom,ValidTo,Created,CreatedBy)VALUES(%s,'%s',%s,%s,%s,%s,'%s',%s,%s,%s,%s,'%s','%s','%s','%s','%s','%s','%s','%s','%s',NOW(),'%s')",idmaterial,uniqreg,stocmin,stocmax,storagemin,storagemax,negstock,demotion,demotionut,perisabil,validtime,codewh,codecc,acc_wh,acc_income,acc_cost,status,statustype,vfrom,vto,muser); 
		

	}
	else
	{
		if(strncmp(delete,"0",strlen("0"))==0)
		{
			sprintf(ExecStatement,"delete from mm_material_wh where IDMWH=%s;",id); 
		}
		else
		{
			sprintf(ExecStatement,"update mm_material_wh SET IDMAT=%s,PARTUNIQUEREG='%s',StocMIN=%s,StocMAX=%s,StorageMINTime=%s,StorageMAXTime=%s,NegativeStock='%s',DemotionQTY=%s,DemotionUnitTime=%s,Perisabil=%s,ValidTime=%s,CODEWH='%s',CODECENTERCOST='%s',ACC_WH='%s',ACC_INCOME='%s',ACC_COST='%s',STATUS='%s',STATUSTYPE='%s',ValidFrom='%s',ValidTo='%s',LastUpdate=NOW(),LastUpdateBy='%s' where IDMWH=%s;",idmaterial,uniqreg,stocmin,stocmax,storagemin,storagemax,negstock,demotion,demotionut,perisabil,validtime,codewh,codecc,acc_wh,acc_income,acc_cost,status,statustype,vfrom,vto,muser,id); 
	 
		}	
	}

	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);

	isinsert=NULL;
	idmaterial=NULL;	
	uniqreg=NULL;
	stocmin=NULL;
	stocmax=NULL;
	storagemin=NULL;
	storagemax=NULL;
	negstock=NULL;
	demotion=NULL;
	demotionut=NULL;
	perisabil=NULL;
	validtime=NULL;
	codewh=NULL;
	codecc=NULL;
	acc_wh=NULL;
	acc_income=NULL;
	acc_cost=NULL;
	status=NULL;
	statustype=NULL;
	vfrom=NULL;
	vto=NULL;
	muser=NULL;
	id=NULL;
	delete=NULL;
}
void F_SQLGetMaterialWH(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select * from mm_material_wh order by IDMWH;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select * from mm_material_wh WHERE PARTUNIQUEREG='%s' order by IDMWH;",margv);
	}
	else if (strncmp(option,"LX",strlen("LX"))==0)	
	{
		sprintf(ExecStatement,"select * from mm_material_wh WHERE IDMAT='%s' order by IDMWH;",margv);
	}
	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}
void F_SQLInUpMaterialSales(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
{
	int enumargv=0;
	char *isinsert=NULL;
	char *idmaterial=NULL;
	char *uniqreg=NULL;
	char *whcode=NULL;
	char *price=NULL;
	char *declarpromo=NULL;
	char *promodescription=NULL;
	char *discount=NULL;
	char *discountqty=NULL;
	char *mindelivery=NULL;
	char *status=NULL;
	char *pricepriority=NULL;
	char *additionvalue=NULL;
	char *vfrom=NULL;
	char *vto=NULL;
	char *id=NULL;
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
			idmaterial=(char*)listpointer->MyItem;
		}	
		else if(enumargv==2)
		{
			uniqreg=(char*)listpointer->MyItem;
		}
		else if(enumargv==3)
		{
			whcode=(char*)listpointer->MyItem;
		}
		else if(enumargv==4)
		{
			price=(char*)listpointer->MyItem;
		}	
		else if(enumargv==5)
		{
			declarpromo=(char*)listpointer->MyItem;
		}
		else if(enumargv==6)
		{
			promodescription=(char*)listpointer->MyItem;
			if(strncmp(promodescription,MY_NULL,strlen(MY_NULL))==0)
			{
				strcpy(promodescription,(const char*)"");
			}
		}
		else if(enumargv==7)
		{
			discount=(char*)listpointer->MyItem;
		}	
		else if(enumargv==8)
		{
			discountqty=(char*)listpointer->MyItem;
		}
		else if(enumargv==9)
		{
			mindelivery=(char*)listpointer->MyItem;
		}
		else if(enumargv==10)
		{
			status=(char*)listpointer->MyItem;
		}
		else if(enumargv==11)
		{
			pricepriority=(char*)listpointer->MyItem;
		}
		else if(enumargv==12)
		{
			additionvalue=(char*)listpointer->MyItem;
		}
		else if(enumargv==13)
		{
			vfrom=(char*)listpointer->MyItem;
		}
		else if(enumargv==14)
		{
			vto=(char*)listpointer->MyItem;
		}
		else if(enumargv==15)
		{
			muser=(char*)listpointer->MyItem;
		}
		else if(enumargv==16)
		{
			id=(char*)listpointer->MyItem;
		}
		else if(enumargv==17)
		{
			delete=(char*)listpointer->MyItem;
		}
		listpointer=listpointer -> NextArgv;	
	}	
	
	if(strncmp(isinsert,"1",strlen("1"))==0)	
	{
		sprintf(ExecStatement,"insert into mm_material_sale(IDMAT,PARTUNIQUEREG,WHCODE,PRICE,DECLARPROMO,PROMODESCRIPTION,DISCOUNT,DISCOUNTQTY,MINDELIVERY,STATUS,PRICEPRIORITY,ADDITIONVALUE,ValidFrom,ValidTo,Created,CreatedBy)VALUES('%s','%s','%s',%s,'%s','%s',%s,%s,%s,'%s','%s',%s,'%s','%s',NOW(),'%s')",idmaterial,uniqreg,whcode,price,declarpromo,promodescription,discount,discountqty,mindelivery,status,pricepriority,additionvalue,vfrom,vto,muser); 
		

	}
	else
	{
		if(strncmp(delete,"0",strlen("0"))==0)
		{
			sprintf(ExecStatement,"delete from mm_material_sale where IDMS=%s;",id); 
		}
		else
		{
			sprintf(ExecStatement,"update mm_material_sale SET IDMAT=%s,PARTUNIQUEREG='%s',WHCODE='%s',PRICE=%s,DECLARPROMO='%s',PROMODESCRIPTION='%s',DISCOUNT=%s,DISCOUNTQTY=%s,MINDELIVERY=%s,STATUS='%s',PRICEPRIORITY='%s',ADDITIONVALUE=%s,ValidFrom='%s',ValidTo='%s',LastUpdate=NOW(),LastUpdateBy='%s' where IDMS=%s;",idmaterial,uniqreg,whcode,price,declarpromo,promodescription,discount,discountqty,mindelivery,status,pricepriority,additionvalue,vfrom,vto,muser,id); 
	 
		}	
	}
	SQLExec(s,mydata,ExecStatement,INSERT_OR_UPDATE);

	isinsert=NULL;
	idmaterial=NULL;
	uniqreg=NULL;
	whcode=NULL;
	price=NULL;
	declarpromo=NULL;
	promodescription=NULL;
	discount=NULL;
	discountqty=NULL;
	mindelivery=NULL;
	status=NULL;
	pricepriority=NULL;
	additionvalue=NULL;
	vfrom=NULL;
	vto=NULL;
	id=NULL;
	muser=NULL;
	delete=NULL;
}
void F_SQLGetMaterialSale(int s,MYSQL* mydata,GOBIZ_SESSION* msess)
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
		sprintf(ExecStatement,"select * from mm_material_sale order by IDMS;");
	}
	else if (strncmp(option,"=",strlen("="))==0)	
	{
		sprintf(ExecStatement,"select * from mm_material_sale WHERE PARTUNIQUEREG='%s' order by IDMS;",margv);
	}
	else if (strncmp(option,"LX",strlen("LX"))==0)	
	{
		sprintf(ExecStatement,"select * from mm_material_sale WHERE IDMAT='%s' order by IDMS;",margv);
	}

	SQLExec(s,mydata,ExecStatement,EXECUTE_STATEMENT);
	
	memset(ExecStatement,'\0',1024);	
	option=NULL;
	margv=NULL;
	
}

