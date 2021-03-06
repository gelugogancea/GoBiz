#include "include/gobiz.h"

extern int ReadConfFromFile(MY_SERVER_CON_PARAM*);
extern unsigned long FormatErrNumber(unsigned char,unsigned char,unsigned int);
extern void my_error(unsigned long,char*,char*,int,int);
extern unsigned long FormatErrNumber(unsigned char,unsigned char,unsigned int);

extern long recv_data(int,int,void*,int,short int,int);
extern int send_cmd(int,int,char*,long,SEND_OPTION);

extern int ProtocolInterpretor(void*,FUNCTIONS_HANDLE*);
extern char* PrepareBuff2SendCMD(long,const char*,unsigned long,DATA_TYPE_TO_SEND);
extern char* PrepareBuff2SendData(long,char*,int*);
extern ARGV_LIST* RemoveItem (FUNCTIONS_HANDLE*,long,...);

extern void ExecFunction(int,MYSQL*,GOBIZ_SESSION*);

extern char* concat (const char*, ...);

int GiveMeSessionInfo(MYSQL*,GOBIZ_SESSION*);
int GiveMeUserAndPassArgv(GOBIZ_SESSION*);

void GOBIZ_Free(GOBIZ_SESSION*);

int main(int argc, char **argv)
{
    int x;
    if (argc>1)
    {
	if (argc==2)
	{
		if((x=strncmp((const char*)argv[1],(const char*)MAIN_ARGV,strlen(MAIN_ARGV)))==0)
		{
			StartMyServer(TRUE);
		}
		else
		{
			goto myEND;
		}

    	}
	else if(argc>2)
	{
		goto myEND;
	}
    }
    else
    {
	long rinit;
	rinit=init_daemon(0,0);     
	StartMyServer(FALSE);		
    }
    
myEND:    
    return(0);
}
long init_daemon(nochdir,noclose)
{
	
switch (fork())
    {
        case 0:  break;
        case -1: return -1;
        default: _exit(0);          
    }

    if (setsid() < 0)              
      return -1;

   
    signal(SIGHUP,SIG_IGN);
    switch (fork())
    {
        case 0:  break;
        case -1: return -1;
        default: _exit(0);
    }

    if (!nochdir)
      chdir("/");
      umask(0);

    if (!noclose)
    {
        
        int i;
	for(i=1;i<64;i++)
	{
		close(i);
	}
	open("/dev/null",O_RDWR);
        dup(0); dup(0);
    }

    return 0;
}
void StartMyServer(short int mbool)
{

	struct sockaddr_in my_addr;    
        struct sockaddr_in their_addr; 
        int child,i=0;
	int sockfd;
	socklen_t sin_size;
	int yes=1,new_fd=0;
	MY_SERVER_CON_PARAM* mparam=NULL;

	i=getuid();
	if(i==0)
	{
		perror("SECURITY PROBLEM\nCineva incearca sa ruleze acest process avand drepturi de root \nInchid aplicatia\n");
	}	

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
            perror("socket");
            exit(0);
        }

	
	mparam=(MY_SERVER_CON_PARAM*)malloc(sizeof(MY_SERVER_CON_PARAM));	
	ReadConfFromFile(mparam);
		
	if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int))==-1)
	{
	    perror("SET_SOCK_OPT : \n");
	}
	
        my_addr.sin_family = AF_INET;         
        my_addr.sin_port = htons(mparam->MainProcessPort);     
        my_addr.sin_addr.s_addr = INADDR_ANY; 
        bzero(&(my_addr.sin_zero), 8);        

        if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) {
            perror("bind");
            exit(1);
        }

        if (listen(sockfd, 1) == -1) {
            perror("listen");
            exit(1);
        }
	
	
        while(1) {                                      
            sin_size = sizeof(struct sockaddr_in);
            if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr,&sin_size)) == -1) {
                perror("accept");
                continue;
            }
	    mparam->theiraddr=their_addr;	
	    mparam->s=new_fd;
	    if(mbool==FALSE)
	    { 
	    	signal(SIGCHLD,SIG_IGN);

		if((child=fork())==0)
	    	{
	    		close(sockfd);
			UserMainProcess(mparam);
			free(mparam);
			exit(0);
	    
	    	}
	    	close(new_fd);
	    }
	    else
	    {
	    	UserMainProcess(mparam);	
	    }


        }
}
GOBIZ_SESSION* GOBIZ_Init(void){
	GOBIZ_SESSION *minit=NULL;
	
	minit=(GOBIZ_SESSION*)calloc(1,sizeof(GOBIZ_SESSION)+1);	
	minit->FunctionPermission=(FUNCTIONS_ALLOW*)calloc(1,sizeof(FUNCTIONS_ALLOW)+1);
	minit->FunctionToHandle=(FUNCTIONS_HANDLE*)calloc(1,sizeof(FUNCTIONS_HANDLE));
	minit->FunctionToHandle->ArgvList=NULL;
	return minit;

}
int GiveMeSessionInfo(MYSQL* myData,GOBIZ_SESSION *msess)
{
	MYSQL_RES *mRes;
	MYSQL_FIELD *mFields;
	MYSQL_ROW mRow;
	int nrRows=0,nrFields=0,i=0,x=0;
	char mSQLExec[1024];
	int mBuff=0;
	char *MYSQLerr=NULL;
	int USER_ID=0;
	memset(mSQLExec,0x0,1024);
	
	sprintf(mSQLExec,"select ID,TimeIdle,MaxSession from sys_user where UserName='%s' and Password=MD5('%s') and '%s'  between ValidFrom and ValidTo;",msess->username,msess->dbpasswd,msess->datetime);
	if((mysql_real_query(myData,mSQLExec,strlen(mSQLExec)))<0)
	{
		MYSQLerr=(char*)mysql_error(myData);
		return(-1);
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
	mFields=mysql_fetch_fields(mRes);
	while ((mRow = mysql_fetch_row(mRes)))
	{
		if(!mRow)
		{
			goto myEND;
		}
		x++;
			
		for(i=0;i<nrFields;i++)
		{
			mBuff=atoi(mRow[i]);
			if(i==0)
			{
				USER_ID=mBuff;	
				msess->DB_ID=USER_ID;
			}
			else if(i==1)
			{
				msess->MaxTimeIdle=mBuff;
			}
			else if(i==2)
			{
				msess->MaximSessionAllowed=mBuff;
			}
			
		}
	
	}

myEND:
	mysql_free_result(mRes);
	return USER_ID;
	
}
int GiveMeUserAndPassArgv(GOBIZ_SESSION *msess){
	
	int i=0;
	
	ARGV_LIST * listpointer=msess->FunctionToHandle->ArgvList;
	
	for(i=1;i<=msess->FunctionToHandle->HowManyArgv;i++)
	{
		if(i==1)
		{
			strcpy(msess->selectDB,listpointer->MyItem);	
		}
		else if(i==2)
		{
			strcpy(msess->username,listpointer->MyItem);
			
		}	
		else if(i==3)
		{
			strcpy(msess->dbpasswd,listpointer->MyItem);
		}
		listpointer=listpointer -> NextArgv;//urmatorul pointer 
	}
	
	return 0;
}

void UserMainProcess(MY_SERVER_CON_PARAM* myparam){
	
	int t=0;
	int s=myparam->s;
	int nval=0;
	int protoerr=0;
	int msize=0;
	int mypid=0;
	int muid=0;
	int sflag=0;
	int mylendata=0;
	long recvlen=0;
	unsigned long mIdleTime=0;
	int rBytes=0xFFFFFFFF;
	unsigned char ErrClass=0;
	unsigned char ErrType=0;
	unsigned int ErrNumber=0;
	long ErrNoToSend=0;
	char *retBuff=NULL;
	char *mbufftosend=NULL;
	void *MyNULL=NULL;
	MYSQL *myDATA=NULL;
	GOBIZ_SESSION* mSession;
	time_t now;
	struct tm *l_time;	

	retBuff=(char*)malloc(myparam->BuffSize+1);
	memset(retBuff,0x0,myparam->BuffSize+1);
	mSession=GOBIZ_Init();
	
	now=time((time_t*)NULL);
	l_time=localtime(&now);
	strftime(mSession->datetime,20,"%F %T",l_time);
	mypid=getpid();
	muid=getuid();
	mSession->mySPID=mypid;
	mSession->mySUID=muid;
	setfsuid(502);
	if(muid==0)
	{
		
		ErrClass=ERR_CLASS_APP;
		ErrType=ERR_TYPE_SESSION;
		ErrNumber=ERR_NO_SECURITY_ROOT_ACCESS;
		my_error(FormatErrNumber(ErrClass,ErrType,ErrNumber),ERR_MSG_SECURITY_ROOT_ACCESS,"UserMainProcess",mypid,muid);
		ErrClass=0;
		ErrType=0;
		exit(0);
	}	

	t=setsockopt(s,SOL_SOCKET,SO_SNDBUF && SO_RCVBUF,&msize,sizeof(msize));
	nval=fcntl(s,F_SETOWN,mypid);
	if(nval<0)
	{
		if(nval==EINVAL)
		{
			ErrClass=ERR_CLASS_SYSTEM;
			ErrType=ERR_TYPE_HANDLE_SOCK;
			ErrNumber=ERR_NO_IOCTL_EINVAL;
			my_error(FormatErrNumber(ErrClass,ErrType,ErrNumber),ERR_MSG_IOCTL_EINVAL,"UserMainProcess",mypid,muid);
			ErrClass=0;	
			ErrType=0;
			ErrNumber=0;
			
		}
		else if(nval==ENOTTY)
		{
			ErrClass=ERR_CLASS_SYSTEM;
			ErrType=ERR_TYPE_HANDLE_SOCK;
			ErrNumber=ERR_NO_IOCTL_ENOTTY;
			my_error(FormatErrNumber(ErrClass,ErrType,ErrNumber),ERR_MSG_IOCTL_ENOTTY,"UserMainProcess",mypid,muid);
			ErrClass=0;	
			ErrType=0;
			ErrNumber=0;
			
		}
		else
		{
			ErrClass=ERR_CLASS_SYSTEM;
			ErrType=ERR_TYPE_HANDLE_SOCK;
			ErrNumber=ERR_NO_IOCTL_SETOWN_FAIL;
			my_error(FormatErrNumber(ErrClass,ErrType,ErrNumber),ERR_MSG_IOCTL_SETOWN_FAIL,"UserMainProcess",mypid,muid);
			ErrClass=0;	
			ErrType=0;
			ErrNumber=0;
			
		}
	}
	if((ioctl(s,FIOASYNC,&sflag))<0)
	{
		ErrClass=ERR_CLASS_SYSTEM;
		ErrType=ERR_TYPE_HANDLE_SOCK;
		ErrNumber=ERR_NO_IOCTL_FIOASYNC_FAIL;
		my_error(FormatErrNumber(ErrClass,ErrType,ErrNumber),ERR_MSG_IOCTL_FIOASYNC_FAIL,"UserMainProcess",mypid,muid);
		ErrClass=0;	
		ErrType=0;
		ErrNumber=0;
	}
	

	
	
for(;;)
{
	recvlen=recv_data(s,rBytes,(void*)retBuff,myparam->TimeOut,myparam->MaxTry,myparam->BuffSize);
	if(recvlen>0){
		mIdleTime=0;
		protoerr=ProtocolInterpretor((void*)retBuff,(FUNCTIONS_HANDLE*)mSession->FunctionToHandle);
		if(protoerr==ERR_NO_FCS_FAIL){
			ErrClass=ERR_CLASS_SYSTEM;
			ErrType=ERR_TYPE_HANDLE_SOCK;
			ErrNumber=ERR_NO_FCS_FAIL;
			ErrNoToSend=FormatErrNumber(ErrClass,ErrType,ErrNumber);
			mbufftosend=PrepareBuff2SendCMD(0,(const char*)mSession->FunctionToHandle->FunctionNameHandle,ErrNoToSend,DATA_TYPE_NULL);	
			send_cmd(s,myparam->TimeOut,mbufftosend,strlen(mbufftosend),MY_ASCII_DATA);
			ErrClass=0;	
			ErrType=0;
			ErrNumber=0;
			MyNULL=realloc(mbufftosend,0);
			mbufftosend=NULL;	
		}
		else if(strncmp(mSession->FunctionToHandle->FunctionNameHandle,FUNC_PING1024,strlen(FUNC_PING1024))==0)
		{
			ErrNoToSend=FormatErrNumber(ERR_CLASS_OK,ERR_TYPE_OK,ERR_NO_OK);
			mbufftosend=PrepareBuff2SendCMD(0,(const char*)mSession->FunctionToHandle->FunctionNameHandle,ErrNoToSend,DATA_TYPE_NULL);
			send_cmd(s,myparam->TimeOut,mbufftosend,strlen(mbufftosend),MY_ASCII_DATA);	
			MyNULL=realloc(mbufftosend,0);
			mbufftosend=NULL;
			ErrNoToSend=0;
		}
		else if(strncmp(mSession->FunctionToHandle->FunctionNameHandle,FUNC_MY_PID,strlen(FUNC_MY_PID))==0)
		{
			
			char mPID[16];
			sprintf(mPID,"%lu",mSession->mySPID);
			mbufftosend=PrepareBuff2SendData(strlen(mPID),mPID,&mylendata);
			send_cmd(s,myparam->TimeOut,mbufftosend,mylendata,MY_ASCII_DATA);	
			MyNULL=realloc(mbufftosend,0);
			mbufftosend=NULL;
			mylendata=0;
			
		}
		else if(strncmp(mSession->FunctionToHandle->FunctionNameHandle,FUNC_MY_UID,strlen(FUNC_MY_UID))==0)
		{
			char mUID[16];
			sprintf(mUID,"%lu",mSession->mySUID);
			mbufftosend=PrepareBuff2SendData(strlen(mUID),mUID,&mylendata);
			send_cmd(s,myparam->TimeOut,mbufftosend,mylendata,MY_ASCII_DATA);	
			MyNULL=realloc(mbufftosend,0);
			mbufftosend=NULL;
			mylendata=0;

		}
		else if(strncmp(mSession->FunctionToHandle->FunctionNameHandle,CMD_DB_CONNECT,strlen(CMD_DB_CONNECT))==0)
		{	

			GiveMeUserAndPassArgv(mSession);
			if(mSession->selectDB)
			{
				strcpy(myparam->mySelectedDB,mSession->FunctionToHandle->ArgvList->MyItem);	
			}
			
    			myDATA=mysql_init((MYSQL*)0);

			if(!mysql_real_connect(myDATA,(char*)myparam->myHost,(char*)myparam->mySuperUser,(char*)myparam->mySuperUserPass,(char*)myparam->mySelectedDB,(int)NULL,myparam->myDBSocketPath,CLIENT_MULTI_STATEMENTS | CLIENT_MULTI_RESULTS))
			{
    			
				ErrNoToSend=FormatErrNumber(ERR_CLASS_SYSTEM,ERR_TYPE_ACCES_DB,ERR_NO_NOT_CONNECT_DB);
				mbufftosend=PrepareBuff2SendCMD(0,(const char*)mSession->FunctionToHandle->FunctionNameHandle,ErrNoToSend,DATA_TYPE_NULL);
				send_cmd(s,myparam->TimeOut,mbufftosend,strlen(mbufftosend),MY_ASCII_DATA);	
				my_error(ErrNoToSend,ERR_MSG_NOT_CONNECT_DB,"UserMainProcess",mypid,muid);
				MyNULL=realloc(mbufftosend,0);
				mbufftosend=NULL;
				ErrNoToSend=0;
				mSession->FunctionToHandle->ArgvList=RemoveItem(mSession->FunctionToHandle,0);
				memset(retBuff,'\0',myparam->BuffSize);
				memset(mSession->FunctionToHandle->FunctionNameHandle,0x0,64);
				goto myEND;
			}
			else
			{
	    			
				if((GiveMeSessionInfo(myDATA,mSession))>0)
				{
					ErrNoToSend=FormatErrNumber(ERR_CLASS_OK,ERR_TYPE_OK,ERR_NO_OK);
				}
				else
				{
					ErrNoToSend=FormatErrNumber(ERR_CLASS_DB,ERR_TYPE_ACCES_DB,ERR_NO_INVALID_USER);
				}
				
				mbufftosend=PrepareBuff2SendCMD(0,(const char*)mSession->FunctionToHandle->FunctionNameHandle,ErrNoToSend,DATA_TYPE_NULL);
				send_cmd(s,myparam->TimeOut,mbufftosend,strlen(mbufftosend),MY_ASCII_DATA);	
				if((0xFFFFFFFF ^ ErrNoToSend)!=0)
				{
					goto myEND1;
				}
				MyNULL=realloc(mbufftosend,0);
				mbufftosend=NULL;
				ErrNoToSend=0;
				printf("OK\n");
			}
		}
		else if(strncmp(mSession->FunctionToHandle->FunctionNameHandle,CMD_MY_CLOSE_CON,strlen(CMD_MY_CLOSE_CON))==0)
		{
			goto myEND;
		}
		else
		{
			ExecFunction(s,myDATA,mSession);
		}
		mSession->FunctionToHandle->ArgvList=RemoveItem(mSession->FunctionToHandle,0);
		memset(retBuff,'\0',myparam->BuffSize);
		memset(mSession->FunctionToHandle->FunctionNameHandle,0x0,64);
	}
	
	if (mSession->MaxTimeIdle>0)
	{

		usleep(1);
		mIdleTime+=1;
		if((mSession->MaxTimeIdle*1000)==mIdleTime)
		{
			strncpy(mSession->FunctionToHandle->FunctionNameHandle,CMD_MY_CLOSE_CON,strlen(CMD_MY_CLOSE_CON));
			goto myEND;
		}
		
	}	
}
myEND:
ErrNoToSend=FormatErrNumber(ERR_CLASS_OK,ERR_TYPE_OK,ERR_NO_OK);
mbufftosend=PrepareBuff2SendCMD(0,(const char*)mSession->FunctionToHandle->FunctionNameHandle,ErrNoToSend,DATA_TYPE_NULL);
send_cmd(s,myparam->TimeOut,mbufftosend,strlen(mbufftosend),MY_ASCII_DATA);	
myEND1:
MyNULL=realloc(mbufftosend,0);
mbufftosend=NULL;
ErrNoToSend=0;
mysql_close(myDATA);
//free(mSession);
GOBIZ_Free(mSession);
free(retBuff);
retBuff=NULL;
free(myparam);
myparam=NULL;
close(s);
exit(0);
}
void GOBIZ_Free(GOBIZ_SESSION *minit){
		
	minit->FunctionToHandle->ArgvList=NULL;
	free(minit->FunctionToHandle);
	minit->FunctionToHandle=NULL;
	free(minit->FunctionPermission);
	minit->FunctionPermission=NULL;
	minit=NULL;

}

