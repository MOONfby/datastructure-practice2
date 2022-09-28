#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
typedef struct LNode {  //单链表（链式结构）结点的定义
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;
typedef struct LNodes {  //线性表的管理表定义
    struct linear {
        char name[30];
        LNode L;
    }linear;
    struct LNodes* next;
}LNodes,*LISTS;
status AddList(LISTS Lists, char ListName[]);//增加一个新线性表
status ListTraverse(LinkList L);
void ListsTraverse(LISTS Lists);
int main()
{
	LinkList L;
	LISTS Lists = NULL,p;
    LNode *head;
	int op, n;
	char name[30];
	op = 1, n=0;
	Lists = (LISTS)malloc(sizeof(LNodes));
	Lists->next = NULL;
    while(op){
        scanf("%d",&op);
        switch(op){
        case 1:
			printf("	您想插入几个线性表？");
			scanf("%d", &n);
			while (n--)
			{
				printf("	请输入线性表的名字：");
				scanf("%s", name);
				AddList(Lists, name);
                p=Lists->next;
                while(p->next){
                    p=p->next;
                }
                head=&p->linear.L;
                head=(LNode*)malloc(sizeof(LNode));
                head->next=NULL;
                printf("    线性表初始化成功\n");
            }
			break;
		case 2://多线性表的遍历
			ListsTraverse(Lists);
			break;
        }
    }
    return 0;
}
status AddList(LISTS Lists, char ListName[])//增加一个新线性表并初始化线性表
{
    LISTS p,q,new;
    LNode* head;
    head = NULL;
    q = Lists;
    p = Lists->next;
    if (!Lists->next)//空表
    {
        new = (LISTS)malloc(sizeof(LNodes));
        strcpy(new->linear.name, ListName);
        Lists->next = new;
        new->next = NULL;
        return OK;
    }
    else {
        while (p) {//找到尾结点
            q = p;
            p = p->next;
        }
        new = (LISTS)malloc(sizeof(LNodes));
        q->next = new;
        new->next = NULL;
        strcpy(new->linear.name, ListName);
        return OK;
    }
}
void ListsTraverse(LISTS Lists) {
    LISTS p;
    p = Lists->next;
    if (p) {
        while (p) {
            printf("%s:", p->linear.name);
            ListTraverse(&p->linear.L);
            putchar('\n');
            p = p->next;
        }
    }
    else
        printf("    线性表为空");
}
status ListTraverse(LinkList L)
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
{
    LinkList p;
    if (L) {
        if (L->next) {
            p = L->next;
            while (p) {
                printf("%d ", p->data);
                p = p->next;
            }
            return OK;
        }
        else {
            printf("空线性表");
        }
    }
    else
        printf("    线性表不存在");
        return INFEASIBLE;
}