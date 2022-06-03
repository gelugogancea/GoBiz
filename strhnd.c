#include "include/gobiz.h"
extern void* mempcpy(void*,const void*,size_t);
void leftcopy(char* input,char* output,int pos,int mystrlen)
{
	char *tmp=NULL;
	void* p=NULL;
	tmp=(char*)malloc(mystrlen+10);
	p=tmp;
	memset(tmp,0x0,mystrlen+10);
	strncpy(tmp,input,mystrlen);
	tmp[pos]='\0';
	strcpy(output,tmp);
	tmp=(char*)p;
	if(tmp && pos<=mystrlen)
	{
		tmp=NULL;
		
	}
	else
	{
		free(tmp);

	}
}

void rightcopy(char* input,char* output,int pos,int mystrlen)
{
	char *tmp=NULL;
	void* p=NULL;
	//int mystrlen=0;
	tmp=(char*)malloc(mystrlen+10);
	p=tmp;
	memset(tmp,0x0,mystrlen+10);
	strncpy(tmp,input,mystrlen);
	tmp+=mystrlen-pos;	
	strcpy(output,tmp);
	tmp=(char*)p;
	if(tmp && pos<=mystrlen)
	{
		free(tmp);
	}
	else
	{
		tmp=NULL;	
	}
}

void midcopy(char* input,char* output,int start_pos, int stop_pos,int mystrlen)
{
	char *tmp=NULL;
	long p=0;
	tmp=(char*)malloc(mystrlen+10);
	p=(long)tmp;
	memset(tmp,0x0,mystrlen+10);	

	strncpy(tmp,input,mystrlen);
	tmp+=start_pos-1;
	tmp[stop_pos]='\0';
	strncpy(output,tmp,strlen(tmp));
	tmp=(char*)p;
	free(tmp);
	tmp=NULL;
	p=0;
}
long SearchForString(char *mBuff,const char *sforsearch,int mystrlen){
	
	char* tmp=NULL;
	char* tmpfragment=NULL;
	long ptmp=0;
	long ptmpfrag=0;
	long i=0;
	int lenstr=0;
	int lencriteria=0;
	int cmpres=0;
	
	tmpfragment=(char*)malloc(mystrlen+1);	
	tmp=(char*)malloc(mystrlen+1);

	ptmp=(long)tmp;
	ptmpfrag=(long)tmpfragment;

	memset(tmpfragment,0x0,mystrlen+1);
	memset(tmp,0x0,mystrlen+1);

	strncpy(tmp,(const char*)mBuff,mystrlen);
	lenstr=strlen(tmp);
	lencriteria=strlen(sforsearch);
	for(i=0;i<lenstr;i++)
	{
		midcopy(tmp,tmpfragment,i+1,lencriteria,mystrlen);	
		cmpres=memcmp(tmpfragment,sforsearch,lencriteria);
		if(cmpres==0)
		{
			break;
		}
	}
	tmp=(char*)ptmp;
	tmpfragment=(char*)ptmpfrag;
	
	free(tmp);
	free(tmpfragment);
	ptmpfrag=0;	
	ptmp=0;
	tmp=NULL;
	tmpfragment=NULL;	

	if(i>=lenstr)
	{
		i=0;
	} 
	mBuff=NULL;
	sforsearch=NULL;
	return i;	
}

char* concat (const char *str, ...)
{
  va_list ap;
  size_t allocated = 256;
  char *result = NULL;
  const char *s=NULL;
  char *wp=NULL;
  char *newp=NULL;
  size_t len=0;
  result = (char *) malloc (allocated+10);
  memset(result,0x0,allocated+10);
 
  if (allocated) 
   {
      

      va_start (ap, str);

      wp = result;
      for (s = str; s != NULL; s = va_arg (ap, const char *))
        {
          len = strlen (s);


          if (wp + len + 1 > result + allocated)
            {
              allocated = (allocated + len) * 2;
              newp = (char *) realloc (result, allocated);
              if (newp == NULL)
                {
                  free (result);
                  return NULL;
                }
              wp = newp + (wp - result);
              result = newp;
            }

          wp = mempcpy (wp, s, len);
        }


      *wp++ = '\0';


      newp = realloc (result, (wp - result)+1);
      
      if (newp != NULL)
        result=newp;

      va_end (ap);
    }
    return newp;	
}

 