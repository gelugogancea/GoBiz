#include "include/gobiz.h"

extern unsigned long Int2Long(unsigned int,unsigned int);
extern LONG_HiLow Long2Int(unsigned long);
extern unsigned int Byte2Int(unsigned char,unsigned char);
extern INT_HiLow Int2Byte(unsigned int);

void my_error(unsigned long ErrCode,char *ErrMsg,char* FunctionNo,int SES_ID,int USER_ID)
{
	FILE *f;
	char *envhome=NULL,*mypath=NULL,*merrmsg,*s_time;
	char* ErrNumber=NULL;
	int y,nbytes;
	unsigned char ErrClass=0;
	unsigned char ErrType=0;
	unsigned int ErrNo=0;
	char *pe=NULL;
	LONG_HiLow ErrorCode;
	INT_HiLow ErrClassAndType;

	time_t now;
	struct tm *l_time;
	
	mypath=(char*)calloc(1,256);
	envhome=(char*)calloc(1,256);
	pe=envhome;
	pe=getenv((const char*)"GOBIZ_HOME");
	
	if (envhome==NULL)
	{
		perror("GoBIZ - GNET SOFTWARE COMPANY\ne-mail:develop@gonetsoftware.com\nhttp://www.gonetsoftware.com\n\nVariabila de mediu GOBIZ_HOME nu este setata\n");
		free(envhome);	
		envhome=NULL;
		exit(0);
	}
	else
	{
		sprintf(mypath,"%s/gobiz.log",pe);
	}
	free(envhome);	
	envhome=NULL;
	pe=NULL;

	ErrNumber=(char*)calloc(1,256);
	merrmsg=(char*)calloc(1,2048);
	s_time=(char*)calloc(1,256);

	now=time((time_t*)NULL);
	l_time=localtime(&now);
	strftime(s_time,25,"%F %T",l_time);	

	ErrorCode=Long2Int(ErrCode);
	ErrNo=ErrorCode.int_Low;
	ErrClassAndType=Int2Byte(ErrorCode.int_Hi);
	ErrClass=ErrClassAndType.ch_Hi;
	ErrType=ErrClassAndType.ch_Low;
	sprintf(ErrNumber,"%d : %d :: %d ",ErrClass,ErrType,ErrNo);	

	f=fopen((const char*)mypath,"a+");
	
	
	sprintf(merrmsg,"%s : %s -> %s - %s : USER_ID : %d \n",s_time,ErrNumber,ErrMsg,FunctionNo,USER_ID);
	
	
	
	if (f==NULL)
	{
		perror("USPHOTO - GNET SOFTWARE COMPANY\ne-mail:develop@gonetsoftware.com\nhttp://www.gonetsoftware.com\n\nNu pot sa deschid gobiz.log");
		goto myEND;
	}

	y=fseek(f,0L,SEEK_END);
	nbytes=fwrite((const void*)merrmsg,sizeof(char),strlen(merrmsg),f);
	if (nbytes<0)
	{
		perror("USPHOTO - GENT SOFTWARE COMPANY\ne-mail:develop@gonetsoftware.com\nhttp://www.gonetsoftware.com\n\nNu pot sa scriu in gobiz.log");
	}
	fclose(f);


myEND:
	free(s_time);
	s_time=NULL;
	free(merrmsg);
	merrmsg=NULL;
	free(mypath);
	mypath=NULL;
	free(ErrNumber);
	ErrNumber=NULL;
	
}
unsigned long FormatErrNumber(unsigned char ErrClass,unsigned char ErrType,unsigned int ErrNumber){
	unsigned long mret=0;
	unsigned int ErrClassType=0;
	
	ErrClassType=Byte2Int(ErrClass,ErrType);	
	mret=Int2Long(ErrClassType,ErrNumber);

	return mret;
}

