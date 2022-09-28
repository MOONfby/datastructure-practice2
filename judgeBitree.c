#include "stdio.h"
#include "stdlib.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define YES 1
#define NO 0
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
status JudgeBiTree(BiTree T);
int main()
{
    DEF definition[100];
    BiTree T;
    int ans,i=0;
    do {
    	scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
    } while (definition[i++].pos);
    CreateBiTree(&T,definition);
    if (JudgeBiTree(T))
    	   printf("YES");
    else 	printf("NO");
    return 1;
}
int pre=-32767;//全局变量，保存当前结点中序前驱的值
status JudgeBiTree(BiTree T)
//判断二叉树T是否为二叉排序树
{
    /****
    int left,right;
    if(!T)//空树也是排序二叉树
    return OK;
    left=JudgeBiTree(T->lchild);//递归判断左子树
    if(left=0)
        return ERROR;
    if(T->data.key>pre)
        pre=T->data.key;//记录前驱结点的值
    else
        return 0;
    right=JudgeBiTree(T->rchild);//最后判断右子树
        return right;
        ***/
    BiTNode* st[50];  //定义指针栈，用于保存访问过的节点//在后续操作中访问该节点的右孩子
    int i,j,num[20],number;
    int top=0;//置空栈
    i=0;
    if(!T)
        return OK;
    do{
        while(T){
            if(top==50)  //栈满
                exit(OVERFLOW);
            st[top++]=T; //根指针进栈
            T=T->lchild; //t移向左子树
        }
        if(top){//为非空栈
            T=st[--top];//弹出根指针
            num[i++]=T->data.key;
            T=T->rchild;//准备遍历右子树
        }
    }while(top||T);//父节点未访问，或右子树未遍历
    number=i;
    for(i=0;i<number;i++){
        for(j=i+1;j<number;j++){
            if(num[j]<num[i])
                return ERROR;
        }
    }
    return OK;
}