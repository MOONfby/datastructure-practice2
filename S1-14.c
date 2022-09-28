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
typedef int ElemType; //����Ԫ�����Ͷ���
typedef int ElemType;
typedef struct{  //˳���˳��ṹ���Ķ���
	      ElemType * elem;
	      int length;
	      int listsize;
}SqList;
typedef struct{  //���Ա�Ĺ������
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
   else printf("ɾ��ʧ��");
return 1;
}
status InitList(SqList* L)
// ���Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
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
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
{
    int *p,*q;
    if(L->elem!=NULL){
        if(L->length+1>=L->listsize){//�ڴ治��
            L->elem=(ElemType*)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
            L->listsize+=LISTINCREMENT;
        }
        if(i==0||i>L->length+1)  //iֵ������      
            return ERROR;
        if(!(L->length)){//�ձ�
            L->elem=(ElemType *)malloc(sizeof(ElemType)*LIST_INIT_SIZE);
            L->listsize=LIST_INIT_SIZE;
            L->elem[0]=e;
            L->length=1;
            return OK;
        }
        else   //�������
            {
            p=&L->elem[i-1];
            for(q=&L->elem[L->length-1];q>=p;q--){
                *(q+1)=*q;      //������ұߵ�Ԫ������
            }
            *p=e;      //����Ԫ��
            L->length++;
            return OK;
            }
    }
    else
        return -1;
}
status ListTraverse(SqList L)
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
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
// ֻ��Ҫ��Lists������һ������ΪListName�Ŀ����Ա����Ա������ֺ�̨���Գ�����롣
{
    int i;
    Lists->elem[Lists->length].L.elem=NULL;
    InitList(&Lists->elem[Lists->length].L);
    for(i=0;ListName[i]!='\0';i++)
        Lists->elem[Lists->length].name[i]=ListName[i];
    Lists->length++;
}
status RemoveList(LISTS *Lists,char ListName[])
// Lists��ɾ��һ������ΪListName�����Ա�
{
    int i;
    for(i=0;i<Lists->length;i++){
        if(!strcmp(Lists->elem[i].name,ListName)){
            DestroyList(&Lists->elem[i].L);//�������Ա�
            if(i!=Lists->length-1)
                Lists->elem[i]=Lists->elem[i+1];
            Lists->length--;
            return OK;
        }
    }
    return ERROR;
}
