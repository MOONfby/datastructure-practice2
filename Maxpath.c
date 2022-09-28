#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define maxleng 100
typedef int status;
typedef int KeyType;
typedef struct
{
    KeyType key;
    char others[20];
} TElemType; //二叉树结点类型定义
typedef struct BiTNode
{ //二叉链表结点的定义
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;
status judge(TElemType definition[])
{
    int i, j;
    for (i = 0; definition[i].key != -1; i++)
    {
        for (j = i + 1; definition[j].key != -1; j++)
        {
            if (definition[i].key == definition[j].key && definition[i].key)
            {                                                           //当key相同时，判断others是否相同
                if (strcmp(definition[i].others, definition[j].others)) //关键字不唯一
                    return ERROR;
            }
        }
    }
    return OK;
}
status CreateBiTree(BiTree *T, TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR*/
{
    static int i = 0;
    if (definition[i].key != -1)
    {
        if (!definition[i].key)
        {
            *T = NULL;
        }
        else
        {
            *T = (BiTree)malloc(sizeof(BiTNode));
            (*T)->data = definition[i];
            i++;
            CreateBiTree(&(*T)->lchild, definition);
            i++;
            CreateBiTree(&(*T)->rchild, definition);
        }
    }
    return OK;
}
int max;
status MaxPathSum(BiTree T,int max,int sum)//根节点到叶子结点的最大路径和
{
    if (!T)
        return max;
    else if (T->lchild && T->rchild)
    {
        MaxPathSum(T->lchild, max,sum + T->data.key);
        MaxPathSum(T->rchild,max, sum + T->data.key);
    }
    else if (T->lchild && !T->rchild)
        MaxPathSum(T->lchild, max,sum + T->data.key);
    else if (!T->lchild && T->rchild)
        MaxPathSum(T->rchild, max,sum + T->data.key);
    else {
        if (sum + T->data.key > max) {
            max = sum + T->data.key;
        }
    }
}
int main()
{
    BiTree T = NULL;
    BiTNode *p;
    TElemType definition[100], value, c;
    int op = 1, depth, e, LR;
    int ans, i = 0;
    char name[50];
    extern max,sum;
    while (op)
    {
        scanf("%d", &op);
        switch (op)
        {
        case 1: //二叉树创建
            printf("\tplease input");
            do
            {
                scanf("%d%s", &definition[i].key, definition[i].others);
            } while (definition[i++].key != -1);
            if (judge(definition) == ERROR)
                printf("\tERROR");
            else
            {
                ans = CreateBiTree(&T, definition);
                if (ans == OK)
                    printf("\tOK");
            }
            break;
        case 2: //根节点到叶子结点的最大路径和
            ans = MaxPathSum(T, max,sum);
            printf("\t%d", ans);
            break;
        case 0:
            break;
        } // end of switch
    }     // end of while
    printf("			欢迎下次再使用本系统！			\n");
} // end of main()
