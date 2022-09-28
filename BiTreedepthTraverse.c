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
} TElemType; //二叉树结点类型定义
typedef struct BiTNode{  //二叉链表结点的定义
      TElemType  data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
void visit(BiTree T)
{
    printf(" %d,%s",T->data.key,T->data.others);
}

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
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree));
int main()
{
    DEF definition[100];
    BiTree T;
    int ans,i=0;
    do {
    	scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
    } while (definition[i++].pos);
    ans=CreateBiTree(&T,definition);
    	LevelOrderTraverse(T,visit);
    	return 1;
}
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
//按层遍历二叉树T
{
    BiTNode *st[maxleng],*leader;//定义指针队列，保存根结点便于访问右子树
    int front=0,rear=0;//置空队列
    if(!T)
        return ERROR;
    st[rear++]=T;//根结点入队
    while(front<rear){//队列非空
        leader=st[front++];//出队
        visit(leader);//访问队头结点
        if(leader->lchild){//根结点出队的同时左右孩子入队
            st[rear++]=leader->lchild;
        }
        if(leader->rchild){
            st[rear++]=leader->rchild;
        }
    }
    return OK;
}