#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int status;
typedef int ElemType; //数据元素类型定义
typedef int ElemType;
typedef struct{  //顺序表（顺序结构）的定义
	      ElemType * elem;
	      int length;
	      int listsize;
}SqList;
typedef struct{  //线性表的管理表定义
     struct { char name[30];
     		  SqList L;	
      } elem[10];
      int length;
      int listsize;
 }LISTS;
status InitList(SqList* L);
status DestroyList(SqList* L);
status ListInsert(SqList *L,int i,ElemType e);
status ListTraverse(SqList L);
status AddList(LISTS *Lists,char ListName[]);
status RemoveList(LISTS *Lists,char ListName[]);
int main() {
	LISTS Lists;
   int n,e;
   char name[30];
   Lists.length=0;
	scanf("%d", &n);
	while(n--)
   {
    	scanf("%s",name);
   		AddList(&Lists,name);
      scanf("%d",&e);
      while (e)
      {
      		ListInsert(&Lists.elem[Lists.length-1].L,Lists.elem[Lists.length-1].L.length+1,e);
      		scanf("%d",&e);
      }
   }
   scanf("%s",name);
   if (RemoveList(&Lists,name)==OK)
	   for(n=0;n<Lists.length;n++)
   		{
   			printf("%s ",Lists.elem[n].name);
   			ListTraverse(Lists.elem[n].L);
        	putchar('\n');
   		}
   else printf("删除失败");
return 1;
}
status InitList(SqList* L)
// 线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
{
    if(L->elem==NULL){
        L->elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
        L->length=0;
        L->listsize=LIST_INIT_SIZE;
        return OK;
    }
    else
        return INFEASIBLE;
}
status DestroyList(SqList* L)
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
{
     if(L->elem!=NULL){
        free(L->elem);
        L->elem=NULL;
        return OK;
    }
    else 
        return INFEASIBLE;
}
status ListInsert(SqList *L,int i,ElemType e)
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
{
    int *p,*q;
    if(L->elem!=NULL){
        if(L->length+1>=L->listsize){//内存不足
            L->elem=(ElemType*)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
            L->listsize+=LISTINCREMENT;
        }
        if(i==0||i>L->length+1)  //i值不合理      
            return ERROR;
        if(!(L->length)){//空表
            L->elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
            L->listsize=LIST_INIT_SIZE;
            L->elem[0]=e;
            L->length=1;
            return OK;
        }
        else   //正常情况
            {
            p=&L->elem[i-1];
            for(q=&L->elem[L->length-1];q>=p;q--){
                *(q+1)=*q;      //插入点右边的元素右移
            }
            *p=e;      //插入元素
            L->length++;
            return OK;
            }
    }
    else
        return -1;
}
status ListTraverse(SqList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    int i;
    if(L.elem!=NULL){
        if(L.length>0){
            for(i=0;i<L.length-1;i++){
                printf("%d ",L.elem[i]);
            }
            printf("%d",L.elem[L.length-1]);
            return OK;
        }
        else
            return OK;
    }
    else
        return -1;
}
status AddList(LISTS *Lists,char ListName[])
// 只需要在Lists中增加一个名称为ListName的空线性表，线性表数据又后台测试程序插入。
{
    int i;
    Lists->elem[Lists->length].L.elem=NULL;
    InitList(&Lists->elem[Lists->length].L);
    for(i=0;ListName[i]!='\0';i++)
        Lists->elem[Lists->length].name[i]=ListName[i];
    Lists->length++;
}
status RemoveList(LISTS *Lists,char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    int i;
    for(i=0;i<Lists->length;i++){
        if(!strcmp(Lists->elem[i].name,ListName)){
            DestroyList(&Lists->elem[i].L);//销毁线性表
            if(i!=Lists->length-1)
                Lists->elem[i]=Lists->elem[i+1];
            Lists->length--;
            return OK;
        }
    }
    return ERROR;
}
