#include "stdio.h"
#include "stdlib.h"
#include <string.h>
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
} TElemType; //������������Ͷ���
typedef struct BiTNode{  //����������Ķ���
      TElemType  data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
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
void CreateBiTree(BiTree* );
status judge(TElemType definition[]);
int main()
{
    
    BiTree T;
    int ans,i=0;
    i=0;
    CreateBiTree(&T);
        PreOrderTraverse(T);
        printf("\n");
        InOrderTraverse(T);
return 1;
}
void CreateBiTree(BiTree* T)
/*���ݴ���֦�Ķ������ȸ���������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK��
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    TElemType definition;
    scanf("%d%s",&definition.key,definition.others);
    if(definition.key!=-1){
        if(!definition.key){
            *T=NULL;
        }
        else{
        *T=(BiTree)malloc(sizeof(BiTNode));
        (*T)->data=definition;
        CreateBiTree(&(*T)->lchild);
        CreateBiTree(&(*T)->rchild);
        }
    }
}
status judge(TElemType definition[]){
    int i,j;
    for(i=0;definition[i].key!=-1;i++){
        for(j=i+1;definition[j].key!=-1;j++){
            if(definition[i].key==definition[j].key&&definition[i].key){
                if(strcmp(definition[i].others,definition[j].others))//�ؼ��ֲ�Ψһ
                    return ERROR;
            }
        }
    }
    return OK;
}