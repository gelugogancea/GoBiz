#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	char* m=(char*)malloc(sizeof(char*));
	char n[10];
	void *p;
	
	int mno=99;
	char s;
	
	s=mno+'0';
		
	p=m;	

	
	*m='L';
	m++;
	*m='M';
	m++;
	*m='N';
	m++;
	*m=0;
	m++;
	*m=0xA;
	m++;
	*m='S';
	m+='\0';
	
	m=p;
	memcpy(n,m,6);
	n[6]='\0';
	return 0;
}

