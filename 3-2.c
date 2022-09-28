#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
#define MAXLENGTH 100
typedef struct QUEUE {
     ElemType elem[MAXLENGTH];
     int front,length;
     } QUEUE;
void iniQueue(QUEUE *Q);        //��ʼ��
int enQueue(QUEUE *Q,ElemType e);//����Ԫ��
int deQueue(QUEUE *Q, ElemType e);//ɾ��Ԫ��
int main()
{
int  i,f,e1,e2;
QUEUE Q;
scanf("%d",&f);
switch(f)
{
case 0: iniQueue(&Q);
      if (Q.front>=0 && Q.front<MAXLENGTH && !Q.length) printf("OK");
      else printf("��ʼ��ʧ��");
		break;
case 1:	Q.length=MAXLENGTH;
		Q.front=0;
      e1=rand();
		if (enQueue(&Q,e1))
      		{  printf("���ʱδ����");break;}
		Q.length=MAXLENGTH-1;
		if (!enQueue(&Q,e1))
      		{  printf("�����������ò���ȷ");break;}
		Q.length=rand()%MAXLENGTH;
		Q.front=0;
      if (enQueue(&Q,e1)==0)
      		{  printf("��ӷ���ֵ�д�");break;}
      printf("OK");
		break;
case 2: Q.front=rand()%MAXLENGTH;
      Q.length=0;
      if (deQueue(&Q,e1)) 
      	{  printf("����ʱδ�п�");break;}
      e1=rand();
      enQueue(&Q,e1); 
      if (deQueue(&Q,e2)==0 || e1!=e2) {printf("Ԫ�س��ӷ���ֵ������Ԫ���д�");break;} 
      printf("OK");
		break;
case 3: i=1;
	   iniQueue(&Q);
      scanf("%d",&f);
      while (f)
      {
      	if (f==1) enQueue(&Q,i++);
       else deQueue(&Q,e1);
	     scanf("%d",&f);
      }
      for(i=0;i<Q.length;i++)
      	printf(" %d",Q.elem[(Q.front+i)%MAXLENGTH]);
}
return 1;
}
void iniQueue(QUEUE *Q)
//�ú���ʵ�ֳ�ʼ��Q
{
    Q->front=0;
    Q->length=0;
}
int enQueue(QUEUE *Q,ElemType e)
//��Ԫ��e���Q���ɹ���ջ����1�����򷵻�0
{
    if(Q->length==MAXLENGTH)
        return 0;
    if(Q->length==MAXLENGTH-1)
        return 1;
    else{
        Q->elem[Q->front+Q->length]=e;//��β���
        Q->length++;
    }
    return 1;
}
int deQueue(QUEUE *Q, ElemType e)
//��Q����Ԫ�س��ӣ���ֵ��e���ɹ����ӷ���1�����򷵻�0
{
    if(Q->length==0)
        return 0;
    else{
        e=Q->elem[Q->front];   //���׳���
        Q->front++;
        Q->length--;
    }
    return 1;
}
