#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	char *ch;
   int length;
} HString;
void Replace(HString* S,HString T,HString V);
void getNext(HString T,int* next);
int main()
{
    HString S[3];
    char buf[100],i,j;
    for(i=0;i<3;i++)
    {
        fgets(buf,100,stdin);
        S[i].length=strlen(buf)-1;  //-1是去掉回车符号
        S[i].ch=(char *)malloc(S[i].length);
        for(j=0;j<S[i].length; j++)
            S[i].ch[j]=*(buf+j);
    }
    Replace(&S[0],S[1],S[2]);
    printf("S的长度:%d\n",S[0].length);
    for(i=0;i<S[0].length;i++)
        putchar(S[0].ch[i]);
    return 1;
}
void Replace(HString* S,HString T,HString V)
{
    int i,j,m,n,next[T.length];
    char *p,*q;
    i=0,j=0;
    getNext(T,next);
    while(i<S->length){
        while(i<S->length&&j<T.length){ //KMP查找子串
            if(j=-1||S->ch[i]==T.ch[j]){//匹配成功
                i++;
                j++;
            }
            else
                j=next[j];
        }
        if(j==T.length){  //匹配成功
            m=i-j;
            if(T.length==V.length){//被替换子串与替换串长度相等
                for(n=0;n<V.length;n++){
                    S->ch[m]=V.ch[n];      
                }
            }
            else if(T.length<V.length){//被替换子串比替换子串短
                q=&S->ch[i-j+T.length-1];
                for(p=&S->ch[S->length-1];p>q;p--){//后移
                    *(p+T.length-V.length)=*p;
                }
                for(n=0;n<V.length;n++){
                    S->ch[m]=V.ch[n];      
                }
                S->length=S->length+T.length-V.length;
            }
            else{                     //被替换子串比替换子串长
                q=&S->ch[S->length-1];
                for(p=&S->ch[i-j+T.length];p<=q;p++){//后移
                    *(p+T.length-V.length)=*p;
                }
                for(n=0;n<V.length;n++){
                    S->ch[m]=V.ch[n];      
                }
                S->length=S->length+T.length-V.length;
            }
        }
    }
    for(i=0;i<S->length;i++)
        printf("%c",S->ch[i]);
}
void getNext(HString T,int* next)
/****以模式字符串为主字符串，以模式字符串的前缀为目标字符串，
一旦字符串匹配成功，那么当前的next值就是匹配成功的字符串的长度****/
{
    next[0]=-1;
    int i,j;
    i=0;
    j=-1;
    while(i<T.length){
        if(j=-1||T.ch[i]==T.ch[j]){
            ++i;
            ++j;
            next[i]=j;
        }
        else
            j=next[j];
    }
}
