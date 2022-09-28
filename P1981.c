#include<stdio.h>
#include<stdlib.h>
#define STACK_INIT_SIZE 100000
typedef int ElemType;
typedef struct {
    ElemType *base;
    int top;
    int stacksize;
}SqStack;
void inistack(SqStack *S);
void push(SqStack *S,unsigned long long int c);//将运算数入栈
void push_1(SqStack *S,char c);//将运算符入栈
int pop(SqStack *S,unsigned long long int *op);   //将操作数出栈
int pop_1(SqStack *S,char *theta);//将操作符出栈
char getTop(SqStack *S);      //获取运算符栈顶
char precede(char top,char c);  //比较操作符的优先级
unsigned long long int operate(unsigned long long int a,char theta,unsigned long long int b);//计算
int main()
{
    SqStack S1,S2;
    inistack(&S1);//操作数栈
    inistack(&S2);//运算符栈
    push_1(&S2,'#');//将底层运算符送入运算符栈底
    char c,theta;
    long long int i,s,a,b;
    int num[4];
    s=0;
    while(c=getchar()){
        if(c>='0'&&c<='9'){
            s*=10;
            s+=c-'0';
        }
        else{
            push(&S1,s%10000);
            s=0;
            if(c!='\n'){
                switch(precede(getTop(&S2),c)){
                    case '>':push_1(&S2,c);
                        break;
                    case '=':push_1(&S2,c);
                        break;
                    case '<':pop_1(&S2,&theta);
                            pop(&S1,&b);pop(&S1,&a);
                            push(&S1,operate(a,theta,b)%10000);
                            push_1(&S2,c);
                            break;  
                } 
            }
            else
                break;
        }
    }
    while(S2.top>1){
        pop_1(&S2,&theta);
        pop(&S1,&b);pop(&S1,&a);
        push(&S1,operate(a,theta,b)%10000);
    }
    printf("%u",S1.base[0]%10000);
    return 0;
}
void inistack(SqStack *S)
{
    S->base=(ElemType*)malloc(STACK_INIT_SIZE*sizeof(ElemType));
    S->stacksize=STACK_INIT_SIZE;
    S->top=0;
}
void push(SqStack *S,unsigned long long int c)
{   
    if(S->top==S->stacksize){
        S->base=(ElemType*)realloc(S->base,(STACK_INIT_SIZE+S->stacksize)*sizeof(ElemType));
        S->stacksize+=STACK_INIT_SIZE;
    }
    S->base[S->top]=c;
    S->top++;
}
void push_1(SqStack *S,char c)
{   
    if(S->top==S->stacksize){
        S->base=(ElemType*)realloc(S->base,(STACK_INIT_SIZE+S->stacksize)*sizeof(ElemType));
        S->stacksize+=STACK_INIT_SIZE;
    }
    S->base[S->top]=c;
    S->top++;
}
int pop(SqStack *S,unsigned long long int *op)
{
    if(S->top==0)          //判断栈是不是非空
        return 0;
    else{ 
        *op=S->base[S->top-1];
        S->top--;
        return 1;
    }
}
int pop_1(SqStack *S,char *theta)
{
    if(S->top==0)          //判断栈是不是非空
        return '\0';
    else{
        *theta=S->base[S->top-1];
        S->top--;
        return 1;
    }
}
unsigned long long int operate(unsigned long long int a,char theta,unsigned long long int b)
{
    int result;
    switch(theta){
        case '+': result=(a+b)%10000;
            break;
        case '*': result=(a*b)%10000;
            break;
    }
    return result;
}
char getTop(SqStack *S)
{
    return S->base[S->top-1];
}
char precede(char top,char c)
{
    if(top=='#')
        return '>';
    else if(top=='+'){
        if(c=='*')
            return '>';
        if(c=='+')
            return '=';
    }
    else if(top='*'){
        if(c=='+')
            return '<';
        if(c=='*')
            return '=';
    }
}