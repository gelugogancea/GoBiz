#include "include/gobiz.h"
#include <sys/resource.h>
#include <sys/times.h>


extern unsigned long FormatErrNumber(unsigned char,unsigned char,unsigned int);
extern void my_error(unsigned long,char*,char*,int,int);

long recv_data(int s,int rBytes,void* retBuf,int timeout,short int MyWait,int iBuffSize)
{
	

	int recvsize=0,unlock_try=0;
	long realrecvsize=0;
	char *myptr=NULL;
	char *p=NULL;
	short int mbool=0;
	struct timeval tv;
	fd_set fd_read;
	int val=1,oflag=0,mytry=0;
	int length=0,mi=0;
	int aa=0;
	int myFailCount=0;
	unsigned char ErrClass=0;
	unsigned char ErrType=0;
	unsigned int ErrNumber=0;
	
	if((fcntl(s,F_SETFL,oflag | O_NDELAY))<0)
	{
		ErrClass=ERR_CLASS_SYSTEM;
		ErrType=ERR_TYPE_HANDLE_SOCK;
		ErrNumber=ERR_NO_NDELAY;
		my_error(FormatErrNumber(ErrClass,ErrType,ErrNumber),ERR_MSG_NDELAY,"recv_data",0,0);
		ErrClass=0;
		ErrType=0;
		ErrNumber=0;
		
	}
	
	if((ioctl(s,FIONBIO,&val))<0)	 	//1 este lock ...o este unlock
	{					
		ErrClass=ERR_CLASS_SYSTEM;
		ErrType=ERR_TYPE_HANDLE_SOCK;
		ErrNumber=ERR_NO_FIONBIO_LOCK;
		my_error(FormatErrNumber(ErrClass,ErrType,ErrNumber),ERR_MSG_FIONBIO_LOCK,"recv_data",0,0);
		ErrClass=0;
		ErrType=0;
		ErrNumber=0;
		
	}		
	
				
			myptr=retBuf;
			p=myptr;
			FD_CLR(s,&fd_read);
			FD_ZERO(&fd_read);
			FD_SET(s,&fd_read);
			mbool=FD_ISSET(s,&fd_read);			
			tv.tv_sec=0;
			tv.tv_usec=timeout*1000;
			unlock_try=select(s+1,&fd_read,NULL,NULL,&tv);
						
			if(unlock_try<=0)
			{
				
			   
			    goto myEND;
				
			}

			for(;;)
			{
				
				
myAGAIN:				
				if(rBytes!=0xFFFFFFFF)
				{
					do 
					{	
					
						mi=ioctl(s,FIONREAD,&length,sizeof(length));	
					
						
						recvsize=read(s,myptr,length);
						if(recvsize>0)
						{
							aa+=recvsize;
							myptr+=recvsize;
							myFailCount=0;
							printf("OK\n");
						}
						else
						{
							myFailCount++;
							if(myFailCount>100)
							{
								printf("FAIL COUNT\n");
								goto myEND;
								realrecvsize=-1;
							}
							FD_CLR(s,&fd_read);
							FD_ZERO(&fd_read);
							FD_SET(s,&fd_read);
							tv.tv_sec=0;
							tv.tv_usec=10000;
							select(s+1,&fd_read,NULL,NULL,&tv);
						}
						
						if(aa>rBytes)
						{
							realrecvsize=-1;
							goto myEND;
						}
												
						printf("IOCTL : %d     %d    %ul\n",aa,length,rBytes);
						length=0;
						recvsize=0;
					}while(aa!=rBytes);
				}
				else
				{

					mi=ioctl(s,FIONREAD,&length,sizeof(length));	
					
					if(length>0)
					{	
						
							recvsize=read(s,myptr,length);
							myptr+=recvsize;
							realrecvsize+=recvsize;
						recvsize=0;
						
						
					}
					else
					{
					
						usleep(10);	
					}
					
				}
					
				if(mi<0)	
				{
					break;
				}	
								
	
				
				if(rBytes!=0xFFFFFFFF)
				{
				
					if(aa>0)
					{	
				    
				    		if(aa==iBuffSize)
						{
							realrecvsize=aa;
							break;	
						}
						else if(recvsize==rBytes+4)
						{
							realrecvsize=aa;
							break;
						}
						else
						{
							realrecvsize+=aa;
						}
					
						
						if(aa==rBytes)
						{
							MyWait=0;
							break;
						}
						else
						{
							MyWait=1;
		
							continue;
						}
						
					
				    
					}
					else if(recvsize==0 && length==0)
					{
						
						break;
					}
					else if(recvsize<=0 && realrecvsize<rBytes)
					{
						mytry++;
						
						if(mytry>1000)
						{
							realrecvsize=0;
							break;
							
						}
						else
						{
							continue;
						}
					}			    
			    		else if(recvsize<=0 && realrecvsize==rBytes)
					{
					    break;
					}
					else if(recvsize==EAGAIN)
					{
					    perror("RECV:EAGAIN ERR : ");
					    usleep(10);
					    goto myAGAIN;
					}
			    
				}
				else
				{
					if(recvsize>0)	
					{	
						realrecvsize+=recvsize;
					}
					else if(recvsize==0)
			    		{
			   	    		break;
				
			    		}
			    		else if(recvsize<0)
					{
					
					
						if(recvsize==EINTR)
						{
							recvsize=1;
							goto myAGAIN;
						}
						else if(recvsize==EAGAIN)
						{	
							recvsize=1;
						}
						else if(recvsize==EIO)
						{
							recvsize=1;
						}
						else
						{
							goto myEND;
						}
					}
					
				}
			
				
			}

	
myEND:			
			
			myptr+='\0';	
			myptr=p;
			val=0;
			
			if((ioctl(s,FIONBIO,&val))<0)
			{
				
				ErrClass=ERR_CLASS_SYSTEM;
				ErrType=ERR_TYPE_HANDLE_SOCK;
				ErrNumber=ERR_NO_FIONBIO_UNLOCK;
				my_error(FormatErrNumber(ErrClass,ErrType,ErrNumber),ERR_MSG_FIONBIO_UNLOCK,"recv_data",0,0);
				ErrClass=0;
				ErrType=0;
				ErrNumber=0;
				
			}	
			
			return(realrecvsize);
					

	
}
int send_cmd(int s,int timeout,char* mcmd,long mylen,SEND_OPTION myOption)
{
	fd_set fd_write;
	struct timeval tv;
	unsigned char ErrClass=0,ErrType=0;
	unsigned int ErrNumber=0;
	int res,sent,val=1,myret=0;
	
	
	FD_ZERO(&fd_write);
	FD_CLR(s,&fd_write);
	FD_SET(s,&fd_write);
	tv.tv_sec=0;
	tv.tv_usec=timeout*1000;
	if((ioctl(s,FIONBIO,&val))<0)	 	
	{					
		ErrClass=ERR_CLASS_SYSTEM;
		ErrType=ERR_TYPE_HANDLE_SOCK;
		ErrNumber=ERR_NO_FIONBIO_LOCK;
		my_error(FormatErrNumber(ErrClass,ErrType,ErrNumber),ERR_MSG_FIONBIO_LOCK,"send_cmd",0,0);
		ErrClass=0;
		ErrType=0;
		ErrNumber=0;
		
	}	
	res=select(s+1,NULL,&fd_write,NULL,&tv);
	if(!res)
	{
	    
	    myret=-1;
	    
	}
	else if(res==0)
	{
	    
	    myret=0;
	    
	}
	else
	{
		if(FD_ISSET(s,&fd_write))
		{

			if(myOption==MY_CMD)
			{	
				sent=send(s,(void*)mcmd,4,0);
			}
			else
			{
				sent=send(s,(void*)mcmd,(size_t)mylen,0);
				
			}
			myret=sent;
			
		}
		else
		{
 
		    myret=0;
		}
		
		myret=0;
	}
	val=0;
	if((ioctl(s,FIONBIO,&val))<0)
	{	 	
		ErrClass=ERR_CLASS_SYSTEM;
		ErrType=ERR_TYPE_HANDLE_SOCK;
		ErrNumber=ERR_NO_FIONBIO_UNLOCK;
		my_error(FormatErrNumber(ErrClass,ErrType,ErrNumber),ERR_MSG_FIONBIO_UNLOCK,"send_cmd",0,0);
		ErrClass=0;
		ErrType=0;
		ErrNumber=0;
		
	}
	return(myret);
}

