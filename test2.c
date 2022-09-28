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
typedef struct {
    KeyType  key;
    char others[20];
} TElemType; //二叉树结点类型定义
typedef struct BiTNode {  //二叉链表结点的定义
    TElemType  data;
    struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;
typedef struct LISTS {  //线性表的管理表定义
    struct {
        char name[30];
        BiTree T;
    } elem[10];
    int length;
    int listsize;
}LISTS;
status CreateBiTree(BiTree* T,int i,TElemType definition[]);
status judge(TElemType definition[]);//创建二叉树时判断关键字是否重复
status CreateBiTree(BiTree* T,int i,TElemType definition[])
/*根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，
如果有相同的关键字，返回ERROR*/
{
    if (definition[i].key != -1) {
        if (!definition[i].key) {
            *T = NULL;
			i++;
        }
        else {
            *T = (BiTree)malloc(sizeof(BiTNode));
            (*T)->data = definition[i++];
            CreateBiTree(&(*T)->lchild, i,definition);
            CreateBiTree(&(*T)->rchild,i, definition);
        }
    }
    return OK;
}
int main() {
	BiTree T = NULL;
	BiTNode* p;
	LISTS Lists;
	TElemType definition[50],value,c;
	int op ,depth,e,LR;
	int ans, i = 0, sum = 0,e1,e2,j;
	char name[50],ListName[20];
	Lists.length = 0;
	e=1;
	while (e) {
		printf("\n\n");
		printf("          Menu for BiTree On Sequence Struture			\n");
		printf(" **************************************************************\n");
		printf("        1.CreateBiTree			2.DestroyBiTree			\n");
		printf("        3.ClearBiTree			4.BiTreeEmpty			\n");
		printf("        5.BiTreeDepth			6.LocateNode			\n");
		printf("        7.Assign			8.GetSibling			\n");
		printf("        9.InsertNode			10.DeleteNode			\n");
		printf("        11.PreOrderTraverse		12.InOrderTraverse		\n");
		printf("        13.PostOrderTraverse		14.LevelOrderTraverse   \n");
		printf("        15.SaveBiTree			16.LoadBiTree			\n");
		printf("        17.MaxPathSum			18.LowestCommonAncestor	\n");
		printf("        19.InvertTree			20.MultipleManagement	\n");
		printf("        21.AddList			22.RemoveList	\n");
		printf("        23.LocateList			24.ListsTraverse\n");
		printf("    	           0. Exit                   \n");
		printf("**************************************************************\n");
		printf("    please choose:");
		scanf("%d", &e);
		switch (e) {
		case 1://二叉树创建
			if (!T) {
				printf("\tplease input:");
				do {
					scanf("%d%s", &definition[i].key, definition[i].others);
				} while (definition[i++].key != -1);
				i = 0;
				CreateBiTree(&T,i,definition);
				printf("\tOK");
			}
			else
				printf("\tERROR");
			break;
        /****
		case 2://二叉树销毁
			ans = DestroyBiTree(&T);
			if (ans == OK)
				printf("\t二叉树销毁成功！\n");
			else
				printf("\t线性表不存在，线性表销毁失败！\n");
			break;
		case 3://二叉树清空
			if (ClearBiTree(&T) == OK)
				printf("	线性表清空成功！\n");
			else
				printf("	线性表不存在!\n");
			break;
		case 4://二叉树判空
			ans = BiTreeEmpty(T);
			if (!ans)
				printf("\t二叉树为空");
			else
				printf("\t二叉树非空");
			break;
		case 5://二叉树深度
			depth=BiTreeDepth(T);
			if (depth)
				printf("\t二叉树的深度为：%d\n",depth);
			else
				printf("\t二叉树不存在\n");
			break;
		case 6://查找结点
			printf("\t请输入你想查找的节点的关键字：");
			scanf("%d", &e);
			p=LocateNode(T, e);
			if (p) 
				printf("\t%d,%s", p->data.key, p->data.others);
			else 
				printf("\t查找失败");
			break;
		case 7://结点赋值
			printf("\t请输入要替换的结点的关键字：");
			scanf("%d",&e);
			printf("\t请输入要修改的结点值:");
			scanf("%d%s", &value.key,value.others);
			ans=Assign(&T, e, value);
			if (ans)
				printf("\tOK");
			else
				printf("\tERROR");
			break;
		case 8://查找兄弟结点
			printf("\t请输入要查找结点的关键字：");
			scanf("%d", &e);
			p=GetSibling(T, e);
			if (p)
				printf("\t%d,%s", p->data.key, p->data.others);
			else
				printf("\t无兄弟结点");
			break;
		case 9://插入结点
			printf("\t请输入结点关键字：");
			scanf("%d", &e);
			printf("\t0表示作为左孩子结点，1表示作为右孩子结点，-1表示作为根结点插入，请输入：");
			scanf("%d", &LR);
			printf("\t请输入待插入结点的关键字和结点值：");
			scanf("%d%s", &c.key, c.others);
			ans=InsertNode(&T, e, LR, c);
			if (ans)
				printf("\tOK");
			else
				printf("\tERROR");
			break;
		case 10://删除结点
			printf("请输入待删除结点的关键字：");
			scanf("%d", &e);
			ans=DeleteNode(&T, e);
			if (ans)
				printf("\tOK");
			else
				printf("\tERROR");
			break;
		case 11://先序遍历
			PreOrderTraverse(T, visit);
			break;
		case 12://中序遍历
			InOrderTraverse(T, visit);
			break;
		case 13://后序遍历
			PostOrderTraverse(T,visit);
			break;
		case 14://按层遍历
			LevelOrderTraverse(T,visit);
			break;
		case 15://将二叉树保存到文件中
			printf("\t请输入文件名");
			scanf("%s", name);
			ans=SaveBiTree(T, name);
			if (ans)
				printf("\tOK");
			else
				printf("\tERROR");
			break;
		case 16://读出文件中的数据并创建二叉树
			printf("\t请输入文件名");
			scanf("%s", name);
			ans = LoadBiTree(&T, name);
			if (ans)
				printf("\tOK");
			else
				printf("\tERROR");
			break;
		case 17://根节点到叶子结点的最大路径和
			ans=MaxPathSum(T,sum);
			printf("\t%d", ans);
			break;
		case 18://e1节点和e2节点的最近公共祖先
			printf("\t请输入e1节点的关键字：");
			scanf("%d", &e1);
			printf("\t请输入e2结点的关键字：");
			scanf("%d", &e2);
			p = LowestCommonAncestor(T, e1, e2);
			if (p)
				printf("\t%d,%s", p->data.key, p->data.others);
			else
				printf("\te1或e2结点不存在");
			break;
		case 20://对多表中的单表操作
			Management(&Lists);
			break;
		case 21://增加线性表
			printf("\t请输入该线性表的名字：");
			scanf("%s", ListName);
			AddList(&Lists,ListName);
			break;
		case 22://移除线性表
			printf("\t请输入该线性表的名字：");
			scanf("%s", ListName);
			ans=RemoveList(&Lists,ListName);
			if (ans)
				printf("\tOK");
			else
				printf("\tERROR");
			break;
		case 23://查找线性表
			printf("\t请输入该线性表的名字：");
			scanf("%s", ListName);
			ans = LocateList(Lists, ListName);
			if (ans) {
				printf("\t%s",Lists.elem[ans].name);
				PreOrderTraverse(Lists.elem[ans].T, visit);
			}
			else
				printf("\tERROR");
			break;
		case 24://多表遍历
			for (i = 0; i < Lists.length; i++) {
				printf("%s：", Lists.elem[i].name);
				PreOrderTraverse(Lists.elem[i].T, visit);
				putchar('\n');
			}
            *****/
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("			欢迎下次再使用本系统！			\n");
}//end of main()
