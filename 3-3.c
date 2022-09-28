#include <stdio.h>
typedef char ElemType;
#define MAXLENGTH 100
#define N 100
typedef struct TWSTACK {
     ElemType elem[N];
     int top1,top2;
     } TWSTACK;
typedef struct QUEUE {
     ElemType elem[MAXLENGTH];
     int front,length;
     } QUEUE;
int main()
{
    char str[100];
    scanf("%s",str);
    printf("%s",isPalindrome(str)?"YES":"NO");
    return 0;
}
int isPalindrome(char *str)
//判断字符串str是否回文，是则返回1，否则返回0
{
     int i;
    char a,b;
    QUEUE p;
    TWSTACK q;
    iniQueue(p);
    for(i=0;str[i]!='@';i++)
        enQueue(p,str[i]);//入队列
    inistack(q);
    for(i=0;str[i]!='@';i++)
        push(q,1,str[i]);//入栈
    for(i=0;i<p.length;i++){
        pop(q,1,a);
        deQueue(p,b);
        if(a!=b)
            return 0;
    }
    return 1;
}

