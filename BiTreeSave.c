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
//status SaveBiTree(BiTree T, char FileName[]);
//status LoadBiTree(BiTree &T, char FileName[]);
#include "string.h"
typedef struct {
    int pos;
    TElemType data; 
} DEF;
status DestroyBiTree(BiTree *T)
{
   if (*T)
   {
        DestroyBiTree(&(*T)->lchild);
        DestroyBiTree(&(*T)->rchild);
        free(*T);
        *T=NULL;
   }
   return OK;
}
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
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree *T,  char FileName[]);
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
    //char FileName[20];
    //strcpy( FileName,"step13/test.dat");
    SaveBiTree(T,"D:\\C\\datalab\\tes.txt");
    DestroyBiTree(&T);
    LoadBiTree(&T,"D:\\C\\datalab\\test1.txt");
    PreOrderTraverse(T);
    printf("\n");
    InOrderTraverse(T);
    return 1;
}
status SaveBiTree(BiTree T, char FileName[])
//将二叉树的结点数据写入到文件FileName中
{
    FILE *fp;
    BiTNode *st[maxleng],*leader;
    int top=0;
    if(!(fp=(fopen(FileName,"wb"))))
        return ERROR;
    st[top++]=T;//根结点入栈
    while(top){
        leader=st[top-1];
        fprintf(fp,"%d,%s ",leader->data.key,leader->data.others);
        top--;
        if(leader->rchild)//根结点出栈的同时右孩子结点入栈，左孩子结点入栈
            st[top++]=leader->rchild;
        if(leader->lchild)
            st[top++]=leader->lchild;
    }
    fclose(fp);
    return OK;
}
status LoadBiTree(BiTree *T,  char FileName[])
//读入文件FileName的结点数据，创建二叉树
{
   FILE *fp;
   int i=0;
   DEF definition[100];
   fp=fopen(FileName,"rb");
    do{
     fscanf(fp,"%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
    }while(definition[i++].pos);
   fclose(fp);
   CreateBiTree(T,definition);
}
