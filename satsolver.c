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
/*cnf�����洢�Ľṹ�嶨��*/
typedef struct Node {//��������
	int mark;
	int value; //����������
	struct Node * next;//ָ����һ����
}Node;
typedef struct Clause {//�����Ӿ�
	int mark_1;
	int num;//�Ӿ������ֵĸ���
	struct Clause* nextcla;//ָ����һ���־�
	Node* next;//ָ����һ������
}Clause;
typedef struct Venue{//���������Ӿ伯
	int num;//����������
	int cnum;//�Ӿ������
	Clause* root;
    int count[MAXNUM];
	int ans[MAXNUM];//������洢
}Venue;
void Readcnf(Venue* G, char filename[]);//��ȡע�ͼ��Ӿ�
void Initvenue(Venue* G);//��ʼ���Ӿ伯
void printcnf(Venue* G);//��ʾ�Ӿ��ȡ���
void mark(Venue* G);//�Ӿ�����ֱ�ǳ�ʼ��
int isUnitclause(Venue* G);//�ж��Ƿ��ǵ��Ӿ֣�����ǣ��򷵻����֣������ǣ��򷵻�0
int  Deleteclause(Venue* G, int u, int depth);//���ݵ��Ӿ���Ӿ伯
void Addclause(Venue* G, int v);//�����ײ巨�������ĵ��Ӿ�
void DeleteFirstclause(Venue* G);//ɾ�����ӽ����ĵ��Ӿ���л���
void destoryclause(Clause* p);//�����Ӿ�
int selectclause(Venue* G);//ѡȡ��ǰ��Ԫ
void backclause(Venue* G, int depth);//����
int solver(Venue* G, int depth, int v);//SAT�����
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
void Readcnf(Venue* G, char filename[])//��ȡ�ļ�������cnf�ڲ��ṹ
{
	FILE* fp;
	Node* q;
	char ch,cnf[10], txt[2000];
	int i,j,u;//��ȡ����
	fp = fopen(filename, "rb");
	if (!fp) 
		return;
	ch = fgetc(fp);
	printf("\t��cnf������ע��Ϊ��\n");
	while (ch == 'c') {//��ȡע��
		fgets(txt, 2000, fp);
		printf("c %s", txt);
		ch = fgetc(fp);
	}
	fscanf(fp, "%s%d%d", cnf, &G->num, &G->cnum);//��ȡ�����������Ӿ����
	printf("\t����%d��������%d���Ӿ�\n", G->num, G->cnum);
	p = (Clause*)malloc(sizeof(Clause));//pΪָ���־��ָ��
	G->root = p;
	for (i = 0; i < G->cnum; i++) {
		j = 0;//��¼�Ӿ������ֵĸ���
		if (i != 0) //��һ���Ӿ䲻���ٴη���ռ�
		{
			p->nextcla = (Clause*)malloc(sizeof(Clause));
			p = p->nextcla;
		}
		fscanf(fp, "%d", &u);//��������
		q = (Node*)malloc(sizeof(Node));//�����ַ���ռ�
		p->next = q;
		q->value = u;
		j++;//��¼ÿ���Ӿ������ֵĸ���
		G->count[abs(q->value)]++;//��¼�Ӿ伯��ÿ���������ֵĴ���
		while (u) //��u��Ϊ0ʱ��ʾһ���Ӿ仹δ������ѭ����ȡ
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
int isUnitclause(Venue* G)//�ж��ǲ��ǵ��Ӿ䲢��������ֵ
{
	Node* q;
	Clause* p1;
	for (p1 = G->root; p1; p1 = p1->nextcla) {
		if (p1->num == 1&&!p1->mark_1) {//�־������ָ���Ϊ1����Ч
			for (q = p1->next; q; q = q->next) {
				if (!q->mark)//������Ч
					return q->value;
			}
		}
	}
	return 0;
}
int  Deleteclause(Venue* G, int u, int depth)//���ݵ��Ӿ���Ӿ伯
{
	Node* q;
	Clause* p1;
	for (p1 = G->root; p1; p1 = p1->nextcla) {
		if (!p1->mark_1) {//�Ӿ���Ч
			for (q = p1->next; q; q = q->next) {
				if (!q->mark) {//������Ч
					if (q->value == u)//ȥ������u���Ӿ�
					{
						p1->mark_1 = depth;
						G->cnum--;
						for (q = p1->next; q; q = q->next) {//ȥ���Ӿ��е�����
							if (q->mark) continue;
							else {
								q->mark = depth;
								p1->num--;
								G->count[abs(q->value)]--;//���ٱ������ֵĴ���
							}
						}
						break;//ɾ���Ӿ���˳��������ֵ�ѭ��
					}
					if (q->value == -u)//ȥ�������Ӿ��к���-u������
					{
						q->mark = depth;
						p1->num--;
						G->count[abs(q->value)]--;
						if (!p1->num)//�����˿��Ӿ�
							return False;
					}
				}
			}
		}
	}
	return OK;
}
void Addclause(Venue* G, int v)//�����ײ巨�������ĵ��Ӿ�
{
	Clause* newnode;
	Node* p;
	newnode = (Clause*)malloc(sizeof(Clause));
	p = (Node*)malloc(sizeof(Node));
	p->value = v;
	p->next = NULL;
	p->mark = 0;//����ĵ��Ӿ���Ч
	G->count[abs(p->value)]++;//���ӱ������ֵĴ���
	newnode->next = p;
	newnode->mark_1 = 0;//�Ӿ���Ч
	newnode->num = 1;
	newnode->nextcla = G->root;
	G->root = newnode;
	G->cnum++;//�Ӿ�������
	
}
void DeleteFirstclause(Venue* G)//ɾ�����ӽ����ĵ��Ӿ���л���
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
		free(p2);//ɾ������
	}
	free(p);//ɾ���Ӿ�
}
int selectclause(Venue* G)//ѡȡ��ǰ��Ԫ
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
	return 0;//���Ӿ伯������
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
		if (p1->mark_1 == depth) {//�Ӿ�㱻ɾ��
			p1->mark_1 = 0;
			G->cnum++;//�Ӿ�������
			for (q = p1->next; q; q = q->next) {
				if (q->mark == depth) {//�ָ���ɾ��������
					q->mark = 0;
					p1->num++;
					G->count[abs(q->value)]++;
				}
			}
		}
		for (q = p1->next; q; q = q->next) {
			if (q->mark == depth) {//���Ӿ�û�б�ɾ��ʱ���鿴�����Ƿ�ɾ��
				q->mark = 0;
				p1->num++;
				G->count[abs(q->value)]++;
			}
		}
	}
}
int solver(Venue* G, int depth, int v)
{
	int clue;//�ҳ��ĵ��Ӿ�����
	if (!v)
		clue = isUnitclause(G);//���û�и���ѡ���ı�Ԫ���������Ӿ伯��Ѱ�ҵ��Ӿ��е�����
	else
		clue = v;//����������vΪ�����ı�Ԫ
	while (clue)//�Ӿ伯�к��е��Ӿ�
	{
		if (clue > 0)
			G->ans[clue] = Ture;//������Ӿ�Ϊ��ֵ����ֵΪ��
		else
			G->ans[clue] = False;//������Ӿ�Ϊ��ֵ����ֵΪ��
		if (!Deleteclause(G, clue, depth))
			return False;//���Ӿ�֮���г�ͻ��������
		clue = isUnitclause(G);//����Ѱ�ҵ��Ӿ�
	}
	int u;
	u = selectmax(G);
	if (!u)//˵����Ϊ���Ӿ伯���������
		return Ture;
	Addclause(G, u);//����Ԫv��Ϊ���Ӿ�����Ӿ伯
	if (solver(G, depth + 1, u))//u��ֵΪ��
	{
		backclause(G, depth + 1);
		DeleteFirstclause(G);//���Ӿ伯��ɾȥ����ĵ��Ӿ�
		return Ture;
	}
	//���ݲ���u��ֵΪ��
	backclause(G, depth + 1);//���ݵ���һ��
	DeleteFirstclause(G);
	Addclause(G, -u);
	if ((solver(G, depth + 1, -u)))//u��ֵΪ��,��ʱcnf��ʽ�ض�Ϊ�沢��ʼ����
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
		printf("	���������ѡ��");
		scanf("%d", &op);
		switch (op) {
			case 1:
				printf("	������cnf�ļ����ļ�����");
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