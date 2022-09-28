#include "stdio.h"
#include "stdlib.h"
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
BiTNode* GetSibling(BiTree T,KeyType e);
int main()
{
    DEF definition[100];
    BiTree T;
    int ans,i=0,e;
    do {
    	scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
    } while (definition[i++].pos);
    ans=CreateBiTree(&T,definition);
    	scanf("%d",&e);
    	BiTNode *p=GetSibling(T,e);
    	if(p) printf("%d,%s",p->data.key,p->data.others);
    	else printf("无兄弟结点");
    	return 1;
}
BiTNode* GetSibling(BiTree T,KeyType e)
//实现获得兄弟结点
{
    if(!T){
        return NULL;
    }
    else{
        if(T->lchild){
            if(T->lchild->data.key==e)
                return T->rchild;
        }
        if(T->rchild){
            if(T->rchild->data.key==e)
                return T->lchild;
        }
        GetSibling(T->lchild,e);
        GetSibling(T->rchild,e);
    }
}
