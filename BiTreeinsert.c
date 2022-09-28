#include "stdio.h"
#include "stdlib.h"
#include<string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int KeyType; 
typedef struct {
     KeyType  key;
     char others[20];
} TElemType; //二叉树结点类型定义
typedef struct BiTNode{  //二叉链表结点的定义
      TElemType  data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
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
void PreOrderTraverse(BiTree T)
{
    if (T)
    {
        printf(" %d,%s",T->data.key,T->data.others);
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
void InOrderTraverse(BiTree T)
{
    if (T)
    {
        InOrderTraverse(T->lchild);
        printf(" %d,%s",T->data.key,T->data.others);
        InOrderTraverse(T->rchild);
    }
}
status Assign(BiTree *T,KeyType e,TElemType value);
BiTNode* LocateNode(BiTree T,KeyType e);
int main()
{
    DEF definition[100];
    BiTree T;
    TElemType e;
    int ans,i=0,key;
    do {
    	scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
    } while (definition[i++].pos);
    ans=CreateBiTree(&T,definition);
    scanf("%d%d%s",&key,&e.key,e.others);
    ans=Assign(&T,key,e);
    if (ans==OK)
    {
        PreOrderTraverse(T);
        printf("\n");
        InOrderTraverse(T);
    }
    else printf("赋值操作失败");
    return 1;
}
status Assign(BiTree *T,KeyType e,TElemType value)
//实现结点赋值。此题允许通过增加其它函数辅助实现本关任务
{
    BiTNode *new,*now;
    if(!(*T))
        return ERROR;
    else{
        if(new=LocateNode(*T,e))
        {
            if(now=LocateNode(*T,value.key)){//关键字是否重复
                if(strcmp(now->data.others,value.others)&&e!=value.key)
                    return ERROR;
            }
            (*new).data=value;
            return OK;
        }
        else //查找失败
            return ERROR;
    }
}
BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    if(!T)
        return NULL;
    else{
        if(T->data.key==e)
            return T;
        LocateNode(T->lchild,e);
        LocateNode(T->rchild,e);
    }
}