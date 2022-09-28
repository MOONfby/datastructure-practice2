#include<stdio.h>
#include<stdlib.h>
#define LIST_INIT_SIZE 5000
#define LISTINCREMENT 10
typedef int ElemType;
typedef struct
   { ElemType *elem;
     int length;
     int listsize;
    } SqList;
void  TriSqList(SqList  A,SqList  B,SqList  C);
int main()
{
    SqList L[3];
    ElemType x;
    int i;
    for(i=0;i<3;i++)
    {
    	L[i].elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
    	L[i].length=0;
    	L[i].listsize=LIST_INIT_SIZE;
    	scanf("%d",&x);
    	while (x)
    	{
        	L[i].elem[L[i].length++]=x;
        	scanf("%d",&x);
    	}
    }
    TriSqList(L[0],L[1],L[2]);
    for(i=0;L[0].elem[i];i++)
        printf(" %d",L[0].elem[i]);
	return 0;
}
void  TriSqList(SqList A,SqList B,SqList C)
{
    int i,k,f[LIST_INIT_SIZE]={0},*p,*q;
    for(i=0;i<B.length;i++){
        for(k=0;k<C.length;k++){
            if(B.elem[i]==C.elem[k]){
                f[B.elem[i]]=1;
                break;
            }
        }
    }
    q=&A.elem[A.length-1];
    for(i=A.length-1;i>=0;i--){
        if(f[A.elem[i]]){
            for(p=&A.elem[i];p<=q;p++){  //把要删除的元素之前的元素向前移
                *p=*(p+1);
            }
            A.length--;
        }
    }
}
