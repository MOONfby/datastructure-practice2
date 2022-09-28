#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 1000
typedef int ElemType;
typedef struct{
    ElemType *base;
    int stacksize;
    int top;
}SqStack;
void inistack(SqStack *S);
void push(SqStack *S,int c);
int pop(SqStack *S,int *op);
int operate(int a,char theta,int b);
int main()
{
    SqStack S;
    char c,theta;
    int s,a,b;
    s=0;
    inistack(&S);//操作数栈
    while((c=getchar())&&c!='@'){
            if(c>='0'&&c<='9'){//字符转化为数字
                s*=10;
                s+=c-'0';
            }
            else if(c=='.'){
                push(&S,s);
                s=0;
            }
            else{
                theta=c;
                pop(&S,&b);
                pop(&S,&a);
                push(&S,operate(a,theta,b));
            }
        }
    printf("%d",S.base[0]);
    return 0;
}
void inistack(SqStack *S)
{
    S->base=(ElemType*)malloc(STACK_INIT_SIZE*sizeof(ElemType));
    S->stacksize=STACK_INIT_SIZE;
    S->top=0;
}
void push(SqStack *S,int c)
{   
    if(S->top==S->stacksize){
        S->base=(ElemType*)realloc(S->base,(STACK_INIT_SIZE+S->stacksize)*sizeof(ElemType));
        S->stacksize+=STACK_INIT_SIZE;
    }
    S->base[S->top]=c;
    S->top++;
}
int pop(SqStack *S,int *op)
{
    if(S->top==0)
        return 0;
    else{
        *op=S->base[S->top-1];
        S->top--;
        return 1;
    }
}
int operate(int a,char theta,int b)
{
    int result;
    switch(theta){
        case '+': result=a+b;
            break;
        case '-': result=a-b;
            break;
        case '*': result=a*b;
            break;
        case '/': result=a/b;
            break;
    }
    return result;
}