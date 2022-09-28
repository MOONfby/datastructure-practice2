#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
typedef struct node
   { ElemType data;
     struct node *next;
    } NODE,*LinkList;
void TriLinkList(LinkList  A,LinkList  B,LinkList  C);
int main()
{
    LinkList L[3],p;
    ElemType x;
    int i;
    for(i=0;i<3;i++)
    {
    	L[i]=p=(NODE *)malloc(sizeof(NODE));
    	scanf("%d",&x);
    	while (x)
    	{
				p->next=(NODE *)malloc(sizeof(NODE));
				p=p->next;
				p->data=x;
				scanf("%d",&x);
    	}
      p->next=NULL;
    }
    TriLinkList(L[0],L[1],L[2]);
    for(p=L[0]->next;p;p=p->next)
        printf(" %d",p->data);
	return 0;
}
void TriLinkList(LinkList  A,LinkList  B,LinkList  C)
{
    LinkList p,p1,p2,q;
    int f[5000]={0};
    for(p1=B->next;p1;p1=p1->next){
        for(p2=C->next;p2;p2=p2->next){
            if(p1->data==p2->data){
                f[p1->data]=1;
                break;
            }
        }
    }
    for(q=A,p=A->next;p!=NULL,q<p;p=p->next){
        if(f[p->data])
            q->next=p->next;
        else
            q=q->next;
    }
}
