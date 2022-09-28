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
} TElemType; //������������Ͷ���
typedef struct BiTNode {  //����������Ķ���
    TElemType  data;
    struct BiTNode* lchild, * rchild;
} BiTNode, * BiTree;
typedef struct LISTS {  //���Ա�Ĺ������
    struct {
        char name[30];
        BiTree T;
    } elem[10];
    int length;
    int listsize;
}LISTS;
status CreateBiTree(BiTree* T,int i,TElemType definition[]);
status judge(TElemType definition[]);//����������ʱ�жϹؼ����Ƿ��ظ�
status CreateBiTree(BiTree* T,int i,TElemType definition[])
/*���ݴ���֦�Ķ������ȸ���������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK��
�������ͬ�Ĺؼ��֣�����ERROR*/
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
		case 1://����������
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
		case 2://����������
			ans = DestroyBiTree(&T);
			if (ans == OK)
				printf("\t���������ٳɹ���\n");
			else
				printf("\t���Ա����ڣ����Ա�����ʧ�ܣ�\n");
			break;
		case 3://���������
			if (ClearBiTree(&T) == OK)
				printf("	���Ա���ճɹ���\n");
			else
				printf("	���Ա�����!\n");
			break;
		case 4://�������п�
			ans = BiTreeEmpty(T);
			if (!ans)
				printf("\t������Ϊ��");
			else
				printf("\t�������ǿ�");
			break;
		case 5://���������
			depth=BiTreeDepth(T);
			if (depth)
				printf("\t�����������Ϊ��%d\n",depth);
			else
				printf("\t������������\n");
			break;
		case 6://���ҽ��
			printf("\t������������ҵĽڵ�Ĺؼ��֣�");
			scanf("%d", &e);
			p=LocateNode(T, e);
			if (p) 
				printf("\t%d,%s", p->data.key, p->data.others);
			else 
				printf("\t����ʧ��");
			break;
		case 7://��㸳ֵ
			printf("\t������Ҫ�滻�Ľ��Ĺؼ��֣�");
			scanf("%d",&e);
			printf("\t������Ҫ�޸ĵĽ��ֵ:");
			scanf("%d%s", &value.key,value.others);
			ans=Assign(&T, e, value);
			if (ans)
				printf("\tOK");
			else
				printf("\tERROR");
			break;
		case 8://�����ֵܽ��
			printf("\t������Ҫ���ҽ��Ĺؼ��֣�");
			scanf("%d", &e);
			p=GetSibling(T, e);
			if (p)
				printf("\t%d,%s", p->data.key, p->data.others);
			else
				printf("\t���ֵܽ��");
			break;
		case 9://������
			printf("\t��������ؼ��֣�");
			scanf("%d", &e);
			printf("\t0��ʾ��Ϊ���ӽ�㣬1��ʾ��Ϊ�Һ��ӽ�㣬-1��ʾ��Ϊ�������룬�����룺");
			scanf("%d", &LR);
			printf("\t�������������Ĺؼ��ֺͽ��ֵ��");
			scanf("%d%s", &c.key, c.others);
			ans=InsertNode(&T, e, LR, c);
			if (ans)
				printf("\tOK");
			else
				printf("\tERROR");
			break;
		case 10://ɾ�����
			printf("�������ɾ�����Ĺؼ��֣�");
			scanf("%d", &e);
			ans=DeleteNode(&T, e);
			if (ans)
				printf("\tOK");
			else
				printf("\tERROR");
			break;
		case 11://�������
			PreOrderTraverse(T, visit);
			break;
		case 12://�������
			InOrderTraverse(T, visit);
			break;
		case 13://�������
			PostOrderTraverse(T,visit);
			break;
		case 14://�������
			LevelOrderTraverse(T,visit);
			break;
		case 15://�����������浽�ļ���
			printf("\t�������ļ���");
			scanf("%s", name);
			ans=SaveBiTree(T, name);
			if (ans)
				printf("\tOK");
			else
				printf("\tERROR");
			break;
		case 16://�����ļ��е����ݲ�����������
			printf("\t�������ļ���");
			scanf("%s", name);
			ans = LoadBiTree(&T, name);
			if (ans)
				printf("\tOK");
			else
				printf("\tERROR");
			break;
		case 17://���ڵ㵽Ҷ�ӽ������·����
			ans=MaxPathSum(T,sum);
			printf("\t%d", ans);
			break;
		case 18://e1�ڵ��e2�ڵ�������������
			printf("\t������e1�ڵ�Ĺؼ��֣�");
			scanf("%d", &e1);
			printf("\t������e2���Ĺؼ��֣�");
			scanf("%d", &e2);
			p = LowestCommonAncestor(T, e1, e2);
			if (p)
				printf("\t%d,%s", p->data.key, p->data.others);
			else
				printf("\te1��e2��㲻����");
			break;
		case 20://�Զ���еĵ������
			Management(&Lists);
			break;
		case 21://�������Ա�
			printf("\t����������Ա�����֣�");
			scanf("%s", ListName);
			AddList(&Lists,ListName);
			break;
		case 22://�Ƴ����Ա�
			printf("\t����������Ա�����֣�");
			scanf("%s", ListName);
			ans=RemoveList(&Lists,ListName);
			if (ans)
				printf("\tOK");
			else
				printf("\tERROR");
			break;
		case 23://�������Ա�
			printf("\t����������Ա�����֣�");
			scanf("%s", ListName);
			ans = LocateList(Lists, ListName);
			if (ans) {
				printf("\t%s",Lists.elem[ans].name);
				PreOrderTraverse(Lists.elem[ans].T, visit);
			}
			else
				printf("\tERROR");
			break;
		case 24://������
			for (i = 0; i < Lists.length; i++) {
				printf("%s��", Lists.elem[i].name);
				PreOrderTraverse(Lists.elem[i].T, visit);
				putchar('\n');
			}
            *****/
		case 0:
			break;
		}//end of switch
	}//end of while
	printf("			��ӭ�´���ʹ�ñ�ϵͳ��			\n");
}//end of main()
