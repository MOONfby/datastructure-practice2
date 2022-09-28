#include<stdlib.h>
#include "stdio.h"
#include "stdlib.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode{  //单链表（链式结构）结点的定义
      ElemType data;
      struct LNode *next;
    }LNode,*LinkList;
status SaveList(LinkList L,char FileName[])
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 1 *********/
    FILE *fp;
    LinkList p;
    if(L){
        if(L->next){
            p=L->next;
            while((fp=fopen(FileName,"wb"))!=NULL){
                while(p){
                    fprintf(fp,"%d",p->data);
                    fputc(' ',fp);
                    p=p->next;
                }
                fclose(fp);
                return OK;
            }
        }
        else 
            printf("空线性表");
    }
    else
        return INFEASIBLE;
    /********** End 1 **********/
}

status LoadList(LinkList* L,char FileName[])
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
{
    // 请在这里补充代码，完成本关任务
    /********** Begin 2 *********/
    FILE *fp;
    LinkList p,q,tail;
    if(!*L){
        *L=tail=(LinkList)malloc(sizeof(LNode));
        q=(LinkList)malloc(sizeof(LNode));
        while((fp=fopen(FileName,"rb"))!=NULL){
            p=(LinkList)malloc(sizeof(LNode));
            while(!feof(fp)){
                fscanf(fp,"%d",&p->data);
                tail->next=p;
                q=tail;
                tail=p;
                p=(LinkList)malloc(sizeof(LNode));
            }
            q->next=NULL;
            fclose(fp);
            return OK;
        }
    }
    else
        return INFEASIBLE;
    /********** End 2 **********/
}
#include "string.h"
int main() {
	LinkList L;
	int f,i=0,j,e;
	FILE *fp;
	char FileName[30];
	strcpy(FileName,"src/step13/list.dat");
	scanf("%d",&f);
	if (!f) {
		L=NULL;
		j=SaveList(L,"src/step13/list.dat");
		if (j==INFEASIBLE) printf("INFEASIBLE\n");
    	else printf("不能对不存在的线性表进行写文件操作！\n");
    	
    	L=(LinkList) malloc(sizeof(LNode));
    	L->next=NULL;
        j=LoadList(&L,"");
        if (j==INFEASIBLE) printf("INFEASIBLE\n");
        else printf("不能对已存在的线性表进行写操作！否则会覆盖原数据，造成数据丢失\n");
    }
    else {
    	L=(LinkList) malloc(sizeof(LNode));
		L->next=NULL;
		LNode *s,*r=L;
    	scanf("%d",&i);
     	while (i) {
			s=(LNode*) malloc(sizeof(LNode));
			s->data=i;
			r->next=s;
			r=s;
			scanf("%d",&i);
		}
		r->next=NULL;
		j=SaveList(L,"D:\\C\\datalab\\test.txt");
		if(j==OK) printf("OK\n");
    	while(L)
    	{
        	s = L->next;
            L->data=0;
        	free(L);
        	L = s;
    	}
		j=LoadList(&L,"D:\\C\\datalab\\test.txt");
		if(j==OK) printf("OK\n");
		for(s=L->next;s;s=s->next)
			printf("%d ",s->data);
	}
	return 1;
}