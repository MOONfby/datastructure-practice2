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
} TElemType; //������������Ͷ���
typedef struct BiTNode{  //����������Ķ���
      TElemType  data;
      struct BiTNode *lchild,*rchild;
} BiTNode, *BiTree;
void free0(void *p);
#include "ctype.h"
#include "string.h"
#define free free0
#undef free
int freed=FALSE;
KeyType e;
void free0(void *p)
{
    if (((BiTree)p)->data.key==e)
        freed=TRUE;
    memset(p,0,sizeof(BiTNode));
    free(p);
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
status DeleteNode(BiTree *T,KeyType e);
BiTNode* LocateNode(BiTree T,KeyType e);
BiTNode* ParentNode(BiTree T,BiTNode* p );
BiTNode* RightNode(BiTree T);
int main()
{
    DEF definition[100];
    BiTree T;
    int ans,i=0;
    do {
        scanf("%d%d%s",&definition[i].pos,&definition[i].data.key,definition[i].data.others);
    } while (definition[i++].pos);
    ans=CreateBiTree(&T,definition);
	scanf("%d",&e);
	ans=DeleteNode(&T,e);
	if (ans==OK )
	{
	    PreOrderTraverse(T);
	    printf("\n");
	    InOrderTraverse(T);
	}
	else printf("ɾ������ʧ��");
	return 1;
}
status DeleteNode(BiTree *T,KeyType e)
//ɾ����㡣��������ͨ������������������ʵ�ֱ�������
{
    BiTNode *p,*parent,*right;
    if(p=LocateNode(*T,e)){
        if(p==*T)
            parent=NULL;
        else
            parent=ParentNode(*T,p);//����e��˫�׽��
        if(!p->lchild&&!p->rchild){ //eΪ��Ϊ0�Ľ��
            if(parent->lchild->data.key==e){
                free(p);
                parent->lchild=NULL;
            }
            if(parent->rchild->data.key==e){
                free(p);
                parent->rchild=NULL;
            }
        }
        else if(!p->lchild||!p->rchild){  //��Ϊ1�Ľ��
            if(!parent){
                if(p->lchild){
                    *T=p->lchild;
                    free(p);
                }
                if(p->rchild){
                    *T=p->rchild;
                    free(p);
                }
            }
            else{
                if(parent->lchild->data.key==e){
                    if(p->lchild){
                        parent->lchild=p->lchild;
                        free(p);
                    }
                    if(p->rchild){
                        parent->lchild=p->rchild;
                        free(p);
                    }
                }
                if(parent->rchild->data.key==e){
                    if(p->lchild){
                        parent->rchild=p->lchild;
                        free(p);
                    }
                    if(p->rchild){
                        parent->rchild=p->rchild;
                        free(p);
                    }
                }
            }
        }
        else{
            if(!parent){
                (*T)=p->lchild;
                right=RightNode(p->lchild);
                right->rchild=p->rchild;
                free(p);
            }
            else{
                if(parent->lchild->data.key==e){
                    parent->lchild=p->lchild;//e�����Ӵ��汻ɾ����eλ��
                    /***e����������Ϊe�������������ҽ���������***/
                    right=RightNode(p->lchild);
                    right->rchild=p->rchild;
                    free(p);
                }
                if(parent->rchild->data.key==e){
                    parent->rchild=p->lchild;
                    right=RightNode(p->lchild);
                    right->rchild=p->rchild;
                    free(p);
                }
            }
        }
        return OK;
    }
    else
        return ERROR;
}
BiTNode* LocateNode(BiTree T,KeyType e)
//���ҽ��
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
BiTNode* ParentNode(BiTree T,BiTNode* p )
//����˫�׽��
{
    if(!T) 
        return NULL;
    if(T->lchild&&T->lchild->data.key==p->data.key) 
        return T;
    if(T->rchild&&T->rchild->data.key==p->data.key)
            return T;
    if(ParentNode(T->lchild, p))
        return ParentNode(T->lchild, p);
    else
        return ParentNode(T->rchild, p);
}
BiTNode* RightNode(BiTree T)
//���������������ҽ��
{
    if(!T)
        return NULL;
    if(!T->rchild&&T->lchild)
        return T;
    if(!T->lchild&&!T->rchild)
        return T;
    if(!T->lchild&&T->rchild){
        if(RightNode(T->rchild))
            return RightNode(T->rchild);
    }
    if(T->lchild&&T->rchild){
        if(RightNode(T->rchild))
            return RightNode(T->rchild);
    }
}