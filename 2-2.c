#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef  struct  Dnode
    {
        ElemType     data;
        struct  Dnode *prior,*next;
    } *DuLinkList;
void  adjust(DuLinkList  L);
int main()
{
    DuLinkList L,p,tail;
    int n,i;
    L=tail=(DuLinkList)malloc(sizeof(struct Dnode));
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        p=(DuLinkList)malloc(sizeof(struct Dnode));
        scanf("%d",&p->data);
        tail->next=p;
        p->prior=tail;
        tail=p;
    }
    L->prior=tail;
    tail->next=L;
    adjust(L);
    p=L->next;
    while(p!=L)
    {
        printf(" %d",p->data);
        p=p->next;
    }
}
void  adjust(DuLinkList  L)
{
    DuLinkList p,q;
    int i,k,number,insert[10000]={0};
    i=1,k=0;   
    p=L->next;
    while(p!=L){
        k++;      //统计链表中元素的个数
        p=p->next;
    }
    number=k;
    for(p=L->next;p!=L;p=p->next){
        if(!(i%2)){              //位于第偶数个的元素从链表中删除,保存在数组里
            insert[i]=p->data;
            p->prior->next=p->next;
            p->next->prior=p->prior;
        }
        i++;
    }
    if(!(number%2))      //确定最后一个偶数位置
        i=number;
    else
        i=number-1;
    p=L->prior;
    for(k=0,i;k<number/2;k++,i-=2){   //连接元素
        q=(DuLinkList)malloc(sizeof(DuLinkList));
        q->data=insert[i];
        p->next=q;
        q->prior=p;
        p=q;
    }
    L->prior=p;
    p->next=L;//首尾相连
}

