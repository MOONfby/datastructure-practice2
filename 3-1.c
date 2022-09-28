#include <stdio.h>
#include <stdlib.h>
#define N 100
typedef int ElemType;
typedef struct TWSTACK {    //��̬����
     ElemType elem[N];
     int top1,top2;
     } TWSTACK;
void inistack(TWSTACK *S);            //��ʼ��
int push(TWSTACK *S,int i,ElemType e);//����Ԫ��
int pop(TWSTACK *S,int i, ElemType e);//ɾ��Ԫ��
int main()
{
int  i,f,e1,e2;
TWSTACK S;
scanf("%d",&f);
switch(f)
{
case 0: inistack(&S);
      if (S.top1==0 && S.top2==N-1) printf("OK");
      else printf("��ʼ��ʧ��");
		break;
case 1:	S.top1=rand()%N;
		S.top2=S.top1-1;
      if (push(&S,1,10))
      		{  printf("ջ1��ջʱδ����");break;}
		S.top1=rand()%N;
		S.top2=S.top1-1;
      if (push(&S,2,10))
      		{  printf("ջ2��ջʱδ����");break;}
      S.top1=rand()%N;
		S.top2=S.top1;
      e1=rand();
      if (push(&S,1,e1)==0 || S.top1!=S.top2+1|| S.elem[S.top1-1]!=e1)
      		{  printf("ջ1��ջʱ�д�");break;}
      S.top1=rand()%N;
		S.top2=S.top1;
      if (push(&S,2,e1)==0 || S.top1!=S.top2+1 || S.elem[S.top2+1]!=e1)
      		{  printf("ջ2��ջʱ�д�");break;}
      printf("OK");
		break;
case 2: S.top1=0;
      S.top2=N-1;
      if (pop(&S,1,e1) || pop(&S,2,e1)) 
      	{  printf("��ջʱδ�п�");break;}
      e1=rand();
      push(&S,1,e1);
     if (pop(&S,1,e2)==0 || e1!=e2) {printf("ջ1��ջ�д�");break;} 
      e1=rand();
      push(&S,2,e1);
     if (pop(&S,2,e2)==0 || e1!=e2) {printf("ջ2��ջ�д�");break;} 
       printf("OK");
		break;
case 3: i=1;
	   inistack(&S);
      scanf("%d",&f);
      while (f)
      {
      	if (f==1) push(&S,1,i++);
       else pop(&S,1,e1);
	     scanf("%d",&f);
      }
      for(i=0;i<S.top1;i++)
      	printf(" %d",S.elem[i]);
}
return 1;

}
void inistack(TWSTACK *S)//�ú���ʵ�ֳ�ʼ��S���õ�2����ջ������˫��ջ��ʾ��ͼ�������ʼ��Ҫ��
{
   S->top1=0;
   S->top2=N-1;
}
int push(TWSTACK *S,int i,ElemType e)
//iȡֵ1��2���ֱ��Ӧ�����ջ����Ԫ��eѹ��S�Ķ�Ӧջ���ɹ���ջ����1�����򷵻�0
{
   if(S->top2==S->top1-1){  //����
      return 0;
   }
   else{                   //��ջ
      if(i==1){
         S->elem[S->top1]=e;
         S->top1++;
      }
      if(i==2){
         S->elem[S->top2]=e;
         S->top2--;
      }
   }
   return 1;
}
int pop(TWSTACK *S,int i, ElemType e)
//iȡֵ1��2���ֱ��Ӧ�����ջ����S��Ӧջ��ջ��Ԫ�س�ջ����ֵ��e���ɹ���ջ����1�����򷵻�0
{
      if(i==1){
         if(S->top1==0)
            return 0;
         else{
            e=S->elem[S->top1-1];
            S->top1--;
         }
      }
      if(i==2){
         if(S->top2==N-1)
            return 0;
         else{
            e=S->elem[S->top2+1];
            S->top2++;
         }
      }
   return 1;
}