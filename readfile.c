#include "include/gobiz.h"
//extern void my_error(DB_ENGINE,int,char*,char*);
#define GOBIZ_MAINPROC_PORT	1
#define GOBIZ_AUXPROC_PORT	2
#define GOBIZ_BUFF_SIZE		3
#define DB_HOST			4
#define DB_USER			5
#define DB_PASS			6
#define DB_SOCK_PATH		7
#define DB_SELECT_DB		8

int SelectSectionFromFile(char*,MY_SERVER_CON_PARAM*);
int ReadConfFromFile(MY_SERVER_CON_PARAM*);
char* smid(char*,int,int);


int ReadConfFromFile(MY_SERVER_CON_PARAM *mparam)
{
    FILE *f;
    char buff[2048];
    char *ret,b;
    char *mhomenv=NULL;
    char *p=NULL;	
    char *mypath=NULL;
    int i;
    ret=&b;
    
   
    mhomenv=NULL;
    mypath=(char*)malloc(256);
    memset(mypath,0x0,256);
    mhomenv=(char*)malloc(256);
    p=mhomenv;
    memset(mhomenv,0x0,256);
    p=getenv((const char*)"GOBIZ_HOME");
    if (mhomenv==NULL)
    {
    	printf("Nu este setata ariabila de mediu GOBIZ_HOME\n");
    }
    else
    {
    	sprintf(mypath,"%s/gobiz.conf",p);
    }
    free(mhomenv);
    mhomenv=NULL;
    p=NULL;
    
    	
    f=fopen(mypath,"r");
    if (f==NULL)
    {
	printf("Nu exista fisierul de configurare gobiz.conf\n");
	exit(0);
    }
    while ((ret=fgets(buff,sizeof(buff),f))!=NULL)
    {

	i=SelectSectionFromFile(buff,mparam);
    	if (i==GOBIZ_MAINPROC_PORT)
		{
		
    	}
    }
    
    free(mypath);
    mypath=NULL;
    ret=NULL;	
    fclose(f);
    return 0;
}
int SelectSectionFromFile(char mbuff[],MY_SERVER_CON_PARAM *mparam)
{

    char *mport=NULL,*mauxport=NULL,*buffsize=NULL,*timeout=NULL,*maxtry=NULL;
    char *dbhost=NULL,*dbuser=NULL,*dbpass=NULL,*selectDB=NULL,*sockpath=NULL;
    int i,x;

    if ((i=strncmp((const char*)mbuff,(const char*)MY_GOBIZ_APP_SECTION,sizeof(MY_GOBIZ_APP_SECTION)-1))==0)
    {

	return MY_ERR_OK;
    }
    else if ((x=strncmp((const char*)mbuff,(const char*)MY_DB_SECTION,sizeof(MY_DB_SECTION)-1))==0)
    {
	
	return MY_ERR_OK;
    }
    else if ((x=strncmp((const char*)mbuff,(const char*)MY_GOBIZ_MAINPROC_PORT,sizeof(MY_GOBIZ_MAINPROC_PORT)-1))==0)
    {
  	mport=smid((char*)mbuff,sizeof(MY_GOBIZ_MAINPROC_PORT)-1,strlen(mbuff)-sizeof(MY_GOBIZ_MAINPROC_PORT));
	mparam->MainProcessPort=atoi(mport);
        free(mport);
	mport=NULL;
	return MY_ERR_OK;
    }
    else if ((x=strncmp((const char*)mbuff,(const char*)MY_GOBIZ_AUXPROC_PORT,sizeof(MY_GOBIZ_AUXPROC_PORT)-1))==0)
    {
	mauxport=smid((char*)mbuff,sizeof(MY_GOBIZ_AUXPROC_PORT)-1,strlen(mbuff)-sizeof(MY_GOBIZ_AUXPROC_PORT));
	mparam->AuxProcessPort=atoi(mauxport);
        free(mauxport);
	mauxport=NULL;
	
	return MY_ERR_OK;
    }
    else if ((x=strncmp((const char*)mbuff,(const char*)MY_GOBIZ_BUFF_SIZE,sizeof(MY_GOBIZ_BUFF_SIZE)-1))==0)
    {
	buffsize=smid((char*)mbuff,sizeof(MY_GOBIZ_BUFF_SIZE)-1,strlen(mbuff)-sizeof(MY_GOBIZ_BUFF_SIZE));
	mparam->BuffSize=atoi(buffsize);
        free(buffsize);
	buffsize=NULL;
	
	return MY_ERR_OK;
    }
    else if ((x=strncmp((const char*)mbuff,(const char*)MY_GOBIZ_TIME_OUT,sizeof(MY_GOBIZ_TIME_OUT)-1))==0)
    {
	timeout=smid((char*)mbuff,sizeof(MY_GOBIZ_TIME_OUT)-1,strlen(mbuff)-sizeof(MY_GOBIZ_TIME_OUT));
	mparam->TimeOut=atoi(timeout);
        if(mparam->TimeOut>60)
	{
		mparam->TimeOut=0;
	}
	free(timeout);
	timeout=NULL;
	
	return MY_ERR_OK;
    }	
    else if ((x=strncmp((const char*)mbuff,(const char*)MY_GOBIZ_MAX_TRY,sizeof(MY_GOBIZ_MAX_TRY)-1))==0)
    {
	maxtry=smid((char*)mbuff,sizeof(MY_GOBIZ_MAX_TRY)-1,strlen(mbuff)-sizeof(MY_GOBIZ_MAX_TRY));
	mparam->MaxTry=atoi(maxtry);
        free(maxtry);
	maxtry=NULL;
	return MY_ERR_OK;
    }	
    else if ((x=strncmp((const char*)mbuff,(const char*)MY_DB_HOST,sizeof(MY_DB_HOST)-1))==0)
    {
	dbhost=smid((char*)mbuff,sizeof(MY_DB_HOST)-1,strlen(mbuff)-sizeof(MY_DB_HOST));
	strcpy(mparam->myHost,dbhost);
        free(dbhost);
	dbhost=NULL;
	return MY_ERR_OK;
    }
    else if ((x=strncmp((const char*)mbuff,(const char*)MY_DB_USER,sizeof(MY_DB_USER)-1))==0)
    {
	dbuser=smid((char*)mbuff,sizeof(MY_DB_USER)-1,strlen(mbuff)-sizeof(MY_DB_USER));
	strcpy(mparam->mySuperUser,dbuser);
        free(dbuser);
	dbuser=NULL;
	return MY_ERR_OK;
    }		
    else if ((x=strncmp((const char*)mbuff,(const char*)MY_DB_PASS,sizeof(MY_DB_PASS)-1))==0)
    {
	dbpass=smid((char*)mbuff,sizeof(MY_DB_PASS)-1,strlen(mbuff)-sizeof(MY_DB_PASS));
	strcpy(mparam->mySuperUserPass,dbpass);
        free(dbpass);
	dbpass=NULL;
	return MY_ERR_OK;
    }
    else if ((x=strncmp((const char*)mbuff,(const char*)MY_DB_SELECT_DB,sizeof(MY_DB_SELECT_DB)-1))==0)
    {

	selectDB=smid((char*)mbuff,sizeof(MY_DB_SELECT_DB)-1,strlen(mbuff)-sizeof(MY_DB_SELECT_DB));
	strcpy(mparam->mySelectedDB,selectDB);
        free(selectDB);
	selectDB=NULL;
	return MY_ERR_OK;
    }			
    else if ((x=strncmp((const char*)mbuff,(const char*)MY_DB_SOCK_PATH,sizeof(MY_DB_SOCK_PATH)-1))==0)
    {
	sockpath=smid((char*)mbuff,sizeof(MY_DB_SOCK_PATH)-1,strlen(mbuff)-sizeof(MY_DB_SOCK_PATH));
	strcpy(mparam->myDBSocketPath,sockpath);
        free(sockpath);
	sockpath=NULL;
	return MY_ERR_OK;
    }	
    else if ((x=strncmp((const char*)mbuff,(const char*)MY_COMMENT,sizeof(MY_COMMENT)-1))==0)
    {
	return MY_ERR_OK;
    }
    else if ((x=strncmp((const char*)mbuff,(const char*)MY_BLANK,sizeof(MY_BLANK)-1))==0)
    {
	return MY_ERR_OK;
    }
    return ERR_NO_UNKNOWN_ITEM;
}
char* smid(char *mybuf,int deunde,int cat)
{
        char *buff=NULL;
        char *sbuff=NULL;
	long p=0;
	long p1=0;
        int i=0;


	buff=(char*)malloc(strlen(mybuf)+1);
	sbuff=(char*)malloc(strlen(mybuf)+1);
	memset(buff,0x0,strlen(mybuf)+1);
	memset(sbuff,0x0,strlen(mybuf)+1);
	p=(long)buff;
	p1=(long)sbuff;
	if (!(buff))
        {
                perror("Nu pot sa aloc memorie");
                exit(0);
        }

        if (!(sbuff))
        {
                perror("Nu pot sa aloc memorie");
                exit(0);
        }


        strcpy(buff,mybuf);


        for (i=0;i<deunde;i++)
        {*buff++;}



        strncpy(sbuff,buff,strlen(buff));

	sbuff[cat]='\0';
        buff=(char*)p;
	sbuff=(char*)p1;
	free(buff);
	buff=NULL;
	return sbuff;

}


