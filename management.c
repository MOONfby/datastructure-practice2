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
typedef int ElemType; //����Ԫ�����Ͷ���
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
typedef int ElemType;
typedef struct LNode {  //��������ʽ�ṹ�����Ķ���
    ElemType data;
    struct LNode* next;
}LNode, * LinkList;
typedef struct LNodes {  //���Ա�Ĺ������
    struct linear {
        char name[30];
        LNode L;
    }linear;
    struct LNodes* next;
}LNodes,*LISTS;
status AddList(LISTS Lists, char ListName[]);//����һ�������Ա�
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
			printf("	������뼸�����Ա�");
			scanf("%d", &n);
			while (n--)
			{
				printf("	���������Ա�����֣�");
				scanf("%s", name);
				AddList(Lists, name);
                p=Lists->next;
                while(p->next){
                    p=p->next;
                }
                head=&p->linear.L;
                head=(LNode*)malloc(sizeof(LNode));
                head->next=NULL;
                printf("    ���Ա��ʼ���ɹ�\n");
            }
			break;
		case 2://�����Ա�ı���
			ListsTraverse(Lists);
			break;
        }
    }
    return 0;
}
status AddList(LISTS Lists, char ListName[])//����һ�������Ա���ʼ�����Ա�
{
    LISTS p,q,new;
    LNode* head;
    head = NULL;
    q = Lists;
    p = Lists->next;
    if (!Lists->next)//�ձ�
    {
        new = (LISTS)malloc(sizeof(LNodes));
        strcpy(new->linear.name, ListName);
        Lists->next = new;
        new->next = NULL;
        return OK;
    }
    else {
        while (p) {//�ҵ�β���
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
        printf("    ���Ա�Ϊ��");
}
status ListTraverse(LinkList L)
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
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
            printf("�����Ա�");
        }
    }
    else
        printf("    ���Ա�����");
        return INFEASIBLE;
}