#include "stdio.h"
#include "stdlib.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
typedef int status;
typedef int TElemType;
typedef struct BiTNode{  //����������Ķ���
      TElemType  data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
void free0(void  *p);
#include "string.h"
#include "ctype.h"
#define free free0
#undef free
struct ptr{
    void *pused[100],*pfree[100];
    int len_used,len_free;
    } pm;
void free0(void *p)
{
    pm.pfree[pm.len_free++]=p;
    memset(p,0,sizeof(BiTNode));
    free(p);
}
BiTree CreateBiTree()
{
    BiTree T;
    int x;
    scanf("%d",&x);
    if (x==0) T=NULL;
    else {
        pm.pused[pm.len_used++]=T=(BiTree) malloc(sizeof(BiTNode));
        T->lchild=CreateBiTree();
        T->rchild=CreateBiTree();
    }
    return T;
}
status ClearBiTree(BiTree *T);
int main()
{
    BiTree T=CreateBiTree();
    int i,j;
	ClearBiTree(&T);
	if (!T)
    {
        for(i=0;i<pm.len_used;i++)
        {
            for(j=0;j<pm.len_free;j++)
                if (pm.pused[i]==pm.pfree[j]) break;
            if (j>=pm.len_free)
            {
                printf("δ��ȷ�ͷŶ��������");
                return 1;
            }
        }
        printf("OK");
    }
 	else printf("ERROR");
	return 1;
}
status ClearBiTree(BiTree *T)
//�����������óɿգ���ɾ�����н�㣬�ͷŽ��ռ�
{
    BiTree p,q;
    if(*T){
        ClearBiTree(&(*T)->lchild);
        ClearBiTree(&(*T)->rchild);
        free(*T);
        (*T)=NULL;
    }
}
