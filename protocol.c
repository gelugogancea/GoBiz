#include "include/gobiz.h"

void* mymalloc(unsigned int,unsigned int*);

extern void leftcopy(char*,char*,int,int);
extern void rightcopy(char*,char*,int,int);
extern void midcopy(char*,char*,int,int,int);
extern char* concat(const char*, ...);
extern long SearchForString(char*,const char*,int);
extern void fcs16_update(unsigned short*, unsigned char*, unsigned long);
extern unsigned int Byte2Int(unsigned char,unsigned char);
int SearchForIllegalChar(char*);

char* PrepareBuff2SendData(long RecNo,char* mData,int* mylen)
{
	char *myret=NULL;
	char *mp=NULL;
	void *p=NULL;
	char sRecNo[16];
	int lmylen=0;
	int lenin=0;
	
	unsigned int reallen=0;	
	
	lenin=strlen(mData)*2;
	
	unsigned short minitck=0xFFFF;
	char mCkSum[16];

	myret=(char*)mymalloc(lenin,&reallen);
	p=myret;
	mp=mData;
	memset(sRecNo,0x0,16);
	memset(mCkSum,0x0,16);
	memset(myret,'\0',reallen);
	sprintf(sRecNo,"%lu",(unsigned long)RecNo);
	strcat(myret,sRecNo);
	strcat(myret,MY_PROTO_NULL);
	strcat(myret,(const char*)mp);
	strcat(myret,MY_PROTO_NULL);
	myret+='\0';
	fcs16_update((unsigned short*)&minitck,(unsigned char*)myret,(unsigned long)strlen(myret));	
	lmylen=strlen(myret);
	myret+=lmylen;
	*myret=minitck & 0xFF;
	myret++;
	*myret+=(minitck>>8) & 0xFF;
	myret+='\0';
	myret=p;
	lmylen+=2;
	*mylen=lmylen;
	mp=NULL;
	return myret;	
}

char* PrepareBuff2SendCMD(long NrOfRec,const char* FunctionName,unsigned long ErrNo,DATA_TYPE_TO_SEND tData){
	
	char mErr[255];
	char mCkSum[16];
	char sDataType[8];
	char sNrOfRec[16];
	char *myret=NULL;
	char *p=NULL;
	
	unsigned short minitck=0xFFFF;
	
	sprintf(mErr,"%lu",(unsigned long) ErrNo);
	if(!NrOfRec)
	{
		p=concat("0",MY_PROTO_NULL,FunctionName,MY_PROTO_NULL,mErr,MY_PROTO_NULL,(char*)0);
	}
	else
	{
		sprintf(sDataType,"%d",tData);
		sprintf(sNrOfRec,"%lu",NrOfRec);
		p=concat(sNrOfRec,MY_PROTO_NULL,FunctionName,MY_PROTO_NULL,mErr,MY_PROTO_NULL,sDataType,MY_PROTO_NULL,(char*)0);
	}
	
	fcs16_update((unsigned short*)&minitck,(unsigned char*)p,(unsigned long)strlen(p));	
	myret=p;
	sprintf(mCkSum,"%c%c",(char)(minitck & 0xFF),(char)((minitck>>8) & 0xFF));
	myret=concat(myret,mCkSum,(char*)0);	
	free(p);
	p=NULL;
	FunctionName=NULL;
	return myret;
}

int ProtocolInterpretor(void* mBuff,FUNCTIONS_HANDLE* mFunction){

	int mposoccurfn=0;
	int remainlengthstring=0;
	char *tmpBuff=(char*)mBuff;
	char *mstring=NULL,*tmparg=NULL;
	long p=0;
	long mErr=0;
	unsigned int mylen=0;
	unsigned short mcksum=0xFFFF;
	

	mstring=(char*)malloc(strlen(tmpBuff)+1);		
	
	memset(mstring,0x0,strlen(tmpBuff)+1);	
	p=(long)mstring;	
	
	fcs16_update((unsigned short*)&mcksum,(unsigned char*)tmpBuff,(unsigned long)strlen(tmpBuff));	

	if((mcksum / 0x100)==0)
	{
		strncpy(mstring,tmpBuff,strlen(tmpBuff)-1);	//daca un byte din HiByte din CkSum este zero
		
	}
	else if((mcksum % 0x100)==0)
	{
		strncpy(mstring,tmpBuff,strlen(tmpBuff));	//daca LoByte din CKSUM este  zero	
	}
	else
	{
		strncpy(mstring,tmpBuff,strlen(tmpBuff)-2);	//mai putin 2 octeti ai FCS16
	}

	mposoccurfn=0;
		
	remainlengthstring=strlen(mstring);
	mposoccurfn=SearchForString(mstring,(const char*)MY_PROTO_NULL,strlen(mstring));
	if(mposoccurfn==0)		
	{
		
		midcopy(mstring,mFunction->FunctionNameHandle,1,strlen(mstring),strlen(mstring));
		mErr=0;
		goto myEND;
	}
	midcopy(mstring,mFunction->FunctionNameHandle,1,mposoccurfn,strlen(mstring));
	remainlengthstring-=mposoccurfn+(strlen(MY_PROTO_NULL));	
	mstring+=mposoccurfn+(strlen(MY_PROTO_NULL));
	mposoccurfn=0;	
	
	mFunction->ArgvList=NULL;	
	
	while(remainlengthstring!=0)
	{
		
		
		if((mposoccurfn=SearchForString(mstring,(const char*)MY_PROTO_NULL,strlen(mstring)))==0)
		{
			break;
			
		}
		mFunction->HowManyArgv++;
		tmparg=mymalloc(mposoccurfn+1,&mylen);
		midcopy(mstring,tmparg,1,mposoccurfn,strlen(mstring));	
		SearchForIllegalChar(tmparg);
		mFunction->ArgvList=AddItem((ARGV_LIST*)mFunction->ArgvList,tmparg);
		mstring+=mposoccurfn+(strlen(MY_PROTO_NULL));
		remainlengthstring-=mposoccurfn+(strlen(MY_PROTO_NULL));
		free(tmparg);
		tmparg=NULL;

	}
myEND:
	tmpBuff=NULL;
	mstring=(char*)p;	
	p=0;
	free(mstring);
	mstring=NULL;
	return mErr;
}

ARGV_LIST * AddItem (ARGV_LIST *listpointer, void* data) {
	ARGV_LIST *prev=NULL;
	ARGV_LIST *work=NULL;
	ARGV_LIST *curr=NULL;
	char *p=NULL;
	int mylen=0;
	unsigned int z=0;
	char *mdata=NULL;
    	long pvaddr=0;
	long ppaddr=0;
	int i=0;
	
	p=(char*)data;
	mylen=strlen(p);
	mdata=(char*)mymalloc(mylen,&z);
	pvaddr=(long)p;
	ppaddr=(long)mdata;

	curr=(ARGV_LIST*)calloc(1,sizeof(ARGV_LIST));	
	
	for(i=0;i<mylen;i++)
	{
		mdata[i]=p[i];
	}
	mdata+='\0';
	p=(char*)pvaddr;
	mdata=(char*)ppaddr;
	if(!curr)
	{
		return NULL;
	}
	curr->NextArgv=NULL;
	curr->MyItem=mdata;
	
	if(!listpointer)
	{

		return curr;
	}
	else
	{
		work=listpointer;
		prev=NULL;
		while(work)
		{
			prev=work;
			work=work->NextArgv;
		}
		if(!prev)
		{
			curr->NextArgv=work;
			return curr;
		}
		else
		{
			prev->NextArgv=curr;
		}
	}
	return listpointer;
}
ARGV_LIST * RemoveItem (FUNCTIONS_HANDLE* mfunc,long MyIdx,...) {
	long i=0;
	long x=0;
	ARGV_LIST *prev=NULL;
	ARGV_LIST *work=NULL;		
	
	if(!MyIdx)
	{
		MyIdx=-1;
	}	

	if(!mfunc->ArgvList)
	{
		return NULL;
	}
	work=mfunc->ArgvList;

	for(i=0;i<mfunc->HowManyArgv;i++)
	{
		if(MyIdx!=i)
		{
			x++;
			prev=work;
			free(prev->MyItem);
			work=work->NextArgv;
			free(prev);
			prev=NULL;
			
		}
	}
	mfunc->HowManyArgv-=x;
	return work;
}

int ProtocolInterpretorCMD(void* mBuff,char* mCMD){

	int remainlengthstring=0;
	char *tmpBuff=(char*)mBuff;
	char *mstring=NULL;
	unsigned short mcksum=0xFFFF;

	mstring=(char*)malloc(strlen(tmpBuff));		
	
	
	memset(mstring,0x0,strlen(tmpBuff));	
	
	fcs16_update((unsigned short*)&mcksum,(unsigned char*)tmpBuff,(unsigned long)strlen(tmpBuff));	
	if(mcksum!=0)
	{
		return ERR_NO_FCS_FAIL;
	}	
	
	strncpy(mstring,tmpBuff,strlen(tmpBuff)-2);	//mai putin 2 octeti ai FCS16
	tmpBuff=NULL;
	remainlengthstring=strlen(mstring);
	strncpy(mCMD,mstring,strlen(mstring));
	
	free(mstring);
	mstring=NULL;
	return remainlengthstring;
}
int WaitReply(int s,long tLen,char* mData,char* mResult){
	
	int zz=0,ii=0;
	int mylen=0;
	char *mbs=NULL;
	char *mp=NULL;
	char mrecBuff[1024];
	memset(mrecBuff,'\0',1024);

	mp=mData;
	
	
	mbs=PrepareBuff2SendData(tLen,mp,&mylen);
	zz=send_cmd(s,1,mbs,(long)mylen,MY_ASCII_DATA);
	free(mbs);
	mbs=NULL;	
	zz=0;
	
	while(zz==0)
	{
		zz=recv_data(s,0xFFFFFFFF,mrecBuff,1,1,1024);
	}
	ii=ProtocolInterpretorCMD(mrecBuff,mResult);
	
	mp=NULL;
	return ii;
}
void* mymalloc(unsigned int mysize,unsigned int * mreallen)
{
	unsigned int mres=0;
	
	mres=mysize % 16;
	if(mres)
	{
		mres=16-(mysize%16)+mysize;
	}
	else
	{
		mres=mysize+mres;
	}
	
	
	*mreallen=mres;	
	return (void*)((char*)calloc(1,mres));
}

int SearchForIllegalChar(char *src){
/*

<0x20
"=0x22
#=0x23
$=0x24
&=0x26
'=0x27
,=0x2C
;=0x3B
^=0x5E
`=0x60
|=0x7C
>125

*/

	int x=0,i=0;
	
	unsigned long addrinit=0;
	char *p=NULL;
	char *dst=NULL;
	p=src;
	dst=p;
	addrinit=(unsigned long)p;
	
	p+='\0';
	
	do 
	{

		if(p[i]<0x20)
		{
			i++;
		}
		else if(p[i]==0x22)	
		{
			i++;
		}
		else if(p[i]==0x23)	
		{
			i++;
		}
		else if(p[i]==0x24)	
		{
			i++;
		}
		else if(p[i]==0x26)	
		{
			i++;
		}
		else if(p[i]==0x27)	
		{
			i++;
		}
		else if(p[i]==0x2C)	
		{
			i++;
		}
		else if(p[i]==0x3B)	
		{
			i++;
		}
		else if(p[i]==0x5E)	
		{
			i++;
		}
		else if(p[i]==0x60)	
		{
			i++;
		}
		else if(p[i]==0x7C)	
		{
			i++;
		}
		else if(p[i]>0x7D)	
		{
			i++;
		}

		dst[x]=p[i];
		dst+='\0';	
		x++;
		i++;

		if(dst[x-1]<0x20)	
		{
			x--;
		}
		else if(dst[x-1]==0x22)	
		{
			x--;
		}
		else if(dst[x-1]==0x23)	
		{
			x--;
		}
		else if(dst[x-1]==0x24)	
		{
			x--;
		}
		else if(dst[x-1]==0x26)	
		{
			x--;
		}
		else if(dst[x-1]==0x27)	
		{
			x--;
		}
		else if(dst[x-1]==0x2C)	
		{
			x--;
		}
		else if(dst[x-1]==0x3B)	
		{
			x--;
		}
		else if(dst[x-1]==0x5E)	
		{
			x--;
		}	
		else if(dst[x-1]==0x60)	
		{
			x--;
		}
		else if(dst[x-1]==0x7C)	
		{
			x--;
		}
		else if(dst[x-1]>0x7D)	
		{
			x--;
		}
	}while(p[x]!='\0');

	p=(char*)addrinit;
	dst=p;
	return i-x;
}
