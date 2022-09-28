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
status InsertNode(BiTree *T,KeyType e,int LR,TElemType c);
BiTNode* LocateNode(BiTree T,KeyType e);
int main()
{
    DEF definition[100];
    BiTree T;
    TElemType c;
    int ans,i=0,e,LR;
    do {
    	scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
    } while (definition[i++].pos);
    ans=CreateBiTree(&T,definition);
    	scanf("%d%d%d%s",&e,&LR,&c.key,c.others);
    	ans=InsertNode(&T,e,LR,c);
    	if (ans==OK)
    	{
    	    PreOrderTraverse(T);
    	    printf("\n");
    	    InOrderTraverse(T);
    	}
    	else printf("插入操作失败");
    	return 1;
}
status InsertNode(BiTree *T,KeyType e,int LR,TElemType c)
//插入结点。此题允许通过增加其它函数辅助实现本关任务
{
    BiTNode *p,*q;
    BiTree newbase;
    p=LocateNode(*T,e);
    if(!p)
        return ERROR;  //不存在被插入节点；
    else{
        if(q=LocateNode(*T,c.key)){
            if(strcmp(q->data.others,c.others))//待插入结点关键字有重复
                return ERROR;
        }
        newbase=(BiTNode*)malloc(sizeof(BiTNode));
        newbase->data=c;
        if(LR==0){
            newbase->rchild=p->lchild;
            newbase->lchild=NULL;
            p->lchild=newbase;//c作为e的左孩子结点
        }
        else if(LR==1){
            newbase->lchild=NULL;
            newbase->rchild=p->rchild;
            p->rchild=newbase;//c作为e的右孩子结点
        }
        else{
            newbase->rchild=*T;
            newbase->lchild=NULL;
            *T=newbase;
        }
    }
    return OK;
}
BiTNode* LocateNode(BiTree T,KeyType e)
//查找结点
{
    if(!T) 
        return NULL;
    if(T->data.key == e) 
        return T;
    if(LocateNode(T->lchild, e))
        return LocateNode(T->lchild, e);
    else
        return LocateNode(T->rchild, e);
}