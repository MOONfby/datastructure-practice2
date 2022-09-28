#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 20
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct
   { ElemType *elem;//指向整型的指针
     int length;
     int listsize;
   }SqList;
int insert(SqList L,ElemType x);
int main()
{
    SqList L;
    ElemType x;
    int i;
    L.elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    L.length=0;
    L.listsize=LIST_INIT_SIZE;
    scanf("%d",&x);
    while (x)
    {
        L.elem[L.length++]=x;
        scanf("%d",&x);
    }
    scanf("%d",&x);
    insert(L,x);
    for(i=0;i<L.length+1;i++)
        printf("%8d",L.elem[i]);
    if (L.length>L.listsize) printf("\n程序未处理溢出");

	return 0;
}
int insert(SqList L,ElemType x)
{
    int i,*p,*q;
    if(L.length+1>=L.listsize)
        L.elem=(ElemType*)realloc(L.elem,(L.listsize+LIST_INIT_SIZE)*sizeof(ElemType));
    L.listsize+=LIST_INIT_SIZE;
    if(!(L.length))
        L.elem[0]=x;
    else{
        for(i=0;i<L.length;i++){
            if(L.elem[i]<=x&&x<=L.elem[i+1]){
                p=&L.elem[i+1];   //插入点位置
                break;
            }
        }
        for(q=&L.elem[L.length-1];q>=p;q--){
            *(q+1)=*q;      //插入点右边的元素右移
        }
            *p=x;      //插入元素
    }
    L.length++;
}