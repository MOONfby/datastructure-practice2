#include "stdio.h"
#include "stdlib.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define maxleng 100
typedef int status;
typedef int KeyType; 
typedef struct {
     KeyType  key;
     char others[20];
} TElemType; //������������Ͷ���
typedef struct BiTNode{  //����������Ķ���
      TElemType  data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}
status InOrderTraverse(BiTree T,void (*visit)(BiTree));
typedef struct {
    int pos;
    TElemType data;
} DEF;
status CreateBiTree(BiTree *T,DEF definition[])
{
    int i=0,j;
    static BiTNode *p[100];
    while (j=definition[i].pos)
    {
    	 p[j]=(BiTNode *)malloc(sizeof(BiTNode));
       p[j]->data=definition[i].data;
       p[j]->lchild=NULL;
       p[j]->rchild=NULL;
       if (j!=1)
       		if (j%2)   p[j/2]->rchild=p[j];  
       	   else      p[j/2]->lchild=p[j];
       i++;
    }
    *T=p[1];
    return OK;
}
int main()
{
DEF definition[100];
BiTree T;
int ans,i=0;
do {
	scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
} while (definition[i++].pos);
ans=CreateBiTree(&T,definition);
InOrderTraverse(T,visit);
return 1;
}
status InOrderTraverse(BiTree T,void (*visit)(BiTree))
//�������������T
{
    BiTNode* st[maxleng];  //����ָ��ջ�����ڱ�����ʹ��Ľڵ�//�ں��������з��ʸýڵ���Һ���
    int top=0;//�ÿ�ջ
    if(!T)
        return ERROR;
    do{
        while(T){
            if(top==maxleng)  //ջ��
                exit(OVERFLOW);
            st[top++]=T; //��ָ���ջ
            T=T->lchild; //t����������
        }
        if(top){//Ϊ�ǿ�ջ
            T=st[--top];//������ָ��
            visit(T);
            T=T->rchild;//׼������������
        }
    }while(top||T);//���ڵ�δ���ʣ���������δ����
    return OK;
}
