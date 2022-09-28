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
//中序遍历二叉树T
{
    BiTNode* st[maxleng];  //定义指针栈，用于保存访问过的节点//在后续操作中访问该节点的右孩子
    int top=0;//置空栈
    if(!T)
        return ERROR;
    do{
        while(T){
            if(top==maxleng)  //栈满
                exit(OVERFLOW);
            st[top++]=T; //根指针进栈
            T=T->lchild; //t移向左子树
        }
        if(top){//为非空栈
            T=st[--top];//弹出根指针
            visit(T);
            T=T->rchild;//准备遍历右子树
        }
    }while(top||T);//父节点未访问，或右子树未遍历
    return OK;
}
