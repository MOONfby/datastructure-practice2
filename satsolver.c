#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#define OK 1
#define ERROR 0
#define Ture 1
#define False 0
#define ERROR 0
#define MAXNUM 1000
#define MAXCNUM 2000
/*cnf算例存储的结构体定义*/
typedef struct Node {//保存文字
	int mark;
	int value; //保存文字名
	struct Node * next;//指向下一文字
}Node;
typedef struct Clause {//保存子句
	int mark_1;
	int num;//子句中文字的个数
	struct Clause* nextcla;//指向下一个字句
	Node* next;//指向下一个文字
}Clause;
typedef struct Venue{//保存整个子句集
	int num;//变量的数量
	int cnum;//子句的数量
	Clause* root;
    int count[MAXNUM];
	int ans[MAXNUM];//求解结果存储
}Venue;
void Readcnf(Venue* G, char filename[]);//读取注释及子句
void Initvenue(Venue* G);//初始化子句集
void printcnf(Venue* G);//显示子句读取结果
void mark(Venue* G);//子句和文字标记初始化
int isUnitclause(Venue* G);//判断是否是单子局，如果是，则返回文字；若不是，则返回0
int  Deleteclause(Venue* G, int u, int depth);//根据单子句简化子句集
void Addclause(Venue* G, int v);//采用首插法加入假设的单子句
void DeleteFirstclause(Venue* G);//删除添加进来的单子句进行回溯
void destoryclause(Clause* p);//销毁子句
int selectclause(Venue* G);//选取当前变元
void backclause(Venue* G, int depth);//回溯
int solver(Venue* G, int depth, int v);//SAT求解器
void DPLL(Venue* G);

extern Venue G;
extern Clause* p;
char txt[2000];
void Initvenue(Venue* G)
{
	int i = 1,j = 1;
	G->cnum = 0;
	G->num = 0;
	G->root = NULL;
	for (i = 1,j=1; i <= MAXCNUM; i++) {
		G->ans[i] = 0;
		G->count[j] = 0;
	}
}
void Readcnf(Venue* G, char filename[])//读取文件并建立cnf内部结构
{
	FILE* fp;
	Node* q;
	char ch,cnf[10], txt[2000];
	int i,j,u;//读取文字
	fp = fopen(filename, "rb");
	if (!fp) 
		return;
	ch = fgetc(fp);
	printf("\t该cnf算例的注释为：\n");
	while (ch == 'c') {//读取注释
		fgets(txt, 2000, fp);
		printf("c %s", txt);
		ch = fgetc(fp);
	}
	fscanf(fp, "%s%d%d", cnf, &G->num, &G->cnum);//读取变量个数及子句个数
	printf("\t共有%d个变量，%d个子句\n", G->num, G->cnum);
	p = (Clause*)malloc(sizeof(Clause));//p为指向字句的指针
	G->root = p;
	for (i = 0; i < G->cnum; i++) {
		j = 0;//记录子句中文字的个数
		if (i != 0) //第一个子句不用再次分配空间
		{
			p->nextcla = (Clause*)malloc(sizeof(Clause));
			p = p->nextcla;
		}
		fscanf(fp, "%d", &u);//读入文字
		q = (Node*)malloc(sizeof(Node));//给文字分配空间
		p->next = q;
		q->value = u;
		j++;//记录每个子句中文字的个数
		G->count[abs(q->value)]++;//记录子句集中每个变量出现的次数
		while (u) //当u不为0时表示一个子句还未结束则循环读取
		{
			fscanf(fp, "%d", &u);
			if (u) {
				q->next = (Node*)malloc(sizeof(Node));
				q = q->next;
				q->value = u;
				j++;
				G->count[abs(q->value)]++;
			}
		}
		p->num = j;
		q->next = NULL;
	}
	p->nextcla = NULL;
	fclose(fp);
	mark(G);
}
void mark(Venue* G)
{
	Node* q;
	Clause* p1;
	for (p1 = G->root; p1; p1 = p1->nextcla) {
		p1->mark_1 = 0;
		for (q = p1->next; q; q = q->next) {
			q->mark = 0;
		}
	}
}
void printcnf(Venue* G)
{
	Node* q;
	Clause* p1;
	p1 = G->root;
	while (p1) {
		q = p1->next;
		while (q) {
			printf("%d ", q->value);
			q = q->next;
		}
		putchar('\n');
		p1 = p1->nextcla;
	}
}
int isUnitclause(Venue* G)//判断是不是单子句并返回文字值
{
	Node* q;
	Clause* p1;
	for (p1 = G->root; p1; p1 = p1->nextcla) {
		if (p1->num == 1&&!p1->mark_1) {//字句中文字个数为1且有效
			for (q = p1->next; q; q = q->next) {
				if (!q->mark)//文字有效
					return q->value;
			}
		}
	}
	return 0;
}
int  Deleteclause(Venue* G, int u, int depth)//根据单子句简化子句集
{
	Node* q;
	Clause* p1;
	for (p1 = G->root; p1; p1 = p1->nextcla) {
		if (!p1->mark_1) {//子句有效
			for (q = p1->next; q; q = q->next) {
				if (!q->mark) {//文字有效
					if (q->value == u)//去掉含有u的子句
					{
						p1->mark_1 = depth;
						G->cnum--;
						for (q = p1->next; q; q = q->next) {//去掉子句中的文字
							if (q->mark) continue;
							else {
								q->mark = depth;
								p1->num--;
								G->count[abs(q->value)]--;//减少变量出现的次数
							}
						}
						break;//删除子句后退出遍历文字的循环
					}
					if (q->value == -u)//去掉其他子句中含有-u的文字
					{
						q->mark = depth;
						p1->num--;
						G->count[abs(q->value)]--;
						if (!p1->num)//出现了空子句
							return False;
					}
				}
			}
		}
	}
	return OK;
}
void Addclause(Venue* G, int v)//采用首插法加入假设的单子句
{
	Clause* newnode;
	Node* p;
	newnode = (Clause*)malloc(sizeof(Clause));
	p = (Node*)malloc(sizeof(Node));
	p->value = v;
	p->next = NULL;
	p->mark = 0;//插入的单子句有效
	G->count[abs(p->value)]++;//增加变量出现的次数
	newnode->next = p;
	newnode->mark_1 = 0;//子句有效
	newnode->num = 1;
	newnode->nextcla = G->root;
	G->root = newnode;
	G->cnum++;//子句数增加
	
}
void DeleteFirstclause(Venue* G)//删除添加进来的单子句进行回溯
{
	Clause* p1;
	p1 = G->root;
	G->root = p1->nextcla;
	destoryclause(p1);
}
void destoryclause(Clause* p)
{
	Node* p1, * p2;
	for (p1 = p->next; p1;) {
		p2 = p1;
		p1 = p1->next;
		free(p2);//删除文字
	}
	free(p);//删除子句
}
int selectclause(Venue* G)//选取当前变元
{
	Clause* p1;
	Node* q;
	for (p1 = G->root; p1; p1 = p1->nextcla) {
		if (!p1->mark_1) {
			for (q = p1->next; q; q = q->next) {
				if (!q->mark) {
					return q->value;
				}
			}
		}
	}
	return 0;//空子句集可满足
}
int selectmax(Venue* G)
{
	int max, i, result;
	max = 0, result = 0;
	for (i = 1; i <= G->num; i++)
	{
		if (G->count[i] > max) {
			max = G->count[i];
			result = i;
		}
	}
	return result;
}
void backclause(Venue* G, int depth)
{
	Node* q;
	Clause* p1;
	for (p1 = G->root; p1; p1 = p1->nextcla) {
		if (p1->mark_1 == depth) {//子句层被删除
			p1->mark_1 = 0;
			G->cnum++;//子句数增加
			for (q = p1->next; q; q = q->next) {
				if (q->mark == depth) {//恢复被删除的文字
					q->mark = 0;
					p1->num++;
					G->count[abs(q->value)]++;
				}
			}
		}
		for (q = p1->next; q; q = q->next) {
			if (q->mark == depth) {//当子句没有被删除时，查看文字是否被删除
				q->mark = 0;
				p1->num++;
				G->count[abs(q->value)]++;
			}
		}
	}
}
int solver(Venue* G, int depth, int v)
{
	int clue;//找出的单子句文字
	if (!v)
		clue = isUnitclause(G);//如果没有给出选出的变元，则在则子句集中寻找单子句中的文字
	else
		clue = v;//若给出，则v为给定的变元
	while (clue)//子句集中含有单子句
	{
		if (clue > 0)
			G->ans[clue] = Ture;//如果单子句为正值，则赋值为真
		else
			G->ans[clue] = False;//如果单子句为负值，则赋值为假
		if (!Deleteclause(G, clue, depth))
			return False;//单子句之间有冲突，则不满足
		clue = isUnitclause(G);//继续寻找单子句
	}
	int u;
	u = selectmax(G);
	if (!u)//说明已为空子句集，则可满足
		return Ture;
	Addclause(G, u);//将变元v作为单子句加入子句集
	if (solver(G, depth + 1, u))//u赋值为真
	{
		backclause(G, depth + 1);
		DeleteFirstclause(G);//在子句集中删去加入的单子句
		return Ture;
	}
	//回溯并将u赋值为假
	backclause(G, depth + 1);//回溯到上一步
	DeleteFirstclause(G);
	Addclause(G, -u);
	if ((solver(G, depth + 1, -u)))//u赋值为假,此时cnf范式必定为真并开始回溯
	{
		backclause(G, depth + 1);
		DeleteFirstclause(G);
		return Ture;
	}
	backclause(G, depth + 1);
	DeleteFirstclause(G);
	return False;
}


char filename[200];
Venue G;
Clause* p;
int main()
{
	int op=1,a;
	while (op) {
		printf("\n\n");
		printf("	Menu for SAT and Sudoku solver on DPLL\n");
		printf("----------------------------------------------\n");
		printf("	1.SAT		2.Sudoku	0.Exit\n");
		printf("	请输入你的选择：");
		scanf("%d", &op);
		switch (op) {
			case 1:
				printf("	请输入cnf文件的文件名：");
				scanf("%s", filename);
				Readcnf(&G,filename);
				break;
			case 2:
				DPLL(&G);
				break;
			case 0:
				break;
		}
	}
	return 0;
}