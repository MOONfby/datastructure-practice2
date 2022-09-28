#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char SUANFA(char *s)
{
char *cSet;
int *cNum,i,j,length=0,n=strlen(s);
cSet=(char *)malloc(sizeof(int)*n);
cNum=(int *)malloc(sizeof(int)*n);
for(i=0;i<n;i++)
{
for(j=0;j<length;j++)
if (s[i]==cSet[j])
{
cNum[j]++;
break;
}
if (j>=length)
cNum[length]=1, cSet[length++]=s[i];
}
for(i=0;i<length;i++)
if (cNum[i]==1)
return cSet[i];
return '\0';
}
int main()
{
char a[]="abcdabcdefg";
printf("ans=%c",SUANFA(a));
return 0;
}