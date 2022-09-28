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
} TElemType; //������������Ͷ���
typedef struct BiTNode{  //����������Ķ���
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
int pre=-32767;//ȫ�ֱ��������浱ǰ�������ǰ����ֵ
status JudgeBiTree(BiTree T)
//�ж϶�����T�Ƿ�Ϊ����������
{
    /****
    int left,right;
    if(!T)//����Ҳ�����������
    return OK;
    left=JudgeBiTree(T->lchild);//�ݹ��ж�������
    if(left=0)
        return ERROR;
    if(T->data.key>pre)
        pre=T->data.key;//��¼ǰ������ֵ
    else
        return 0;
    right=JudgeBiTree(T->rchild);//����ж�������
        return right;
        ***/
    BiTNode* st[50];  //����ָ��ջ�����ڱ�����ʹ��Ľڵ�//�ں��������з��ʸýڵ���Һ���
    int i,j,num[20],number;
    int top=0;//�ÿ�ջ
    i=0;
    if(!T)
        return OK;
    do{
        while(T){
            if(top==50)  //ջ��
                exit(OVERFLOW);
            st[top++]=T; //��ָ���ջ
            T=T->lchild; //t����������
        }
        if(top){//Ϊ�ǿ�ջ
            T=st[--top];//������ָ��
            num[i++]=T->data.key;
            T=T->rchild;//׼������������
        }
    }while(top||T);//���ڵ�δ���ʣ���������δ����
    number=i;
    for(i=0;i<number;i++){
        for(j=i+1;j<number;j++){
            if(num[j]<num[i])
                return ERROR;
        }
    }
    return OK;
}