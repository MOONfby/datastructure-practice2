#include "stdio.h"
	#include "stdlib.h"
	#define TRUE 1
	#define FALSE 0
	#define OK 1
	#define ERROR 0
	#define INFEASIBLE -1
	#define OVERFLOW -2
	#define MAX_VERTEX_NUM 20
	typedef int status;
	typedef int KeyType; 
   typedef enum {DG,DN,UDG,UDN} GraphKind;
	typedef struct {
         KeyType  key;
         char others[20];
	} VertexType; //�������Ͷ���


	typedef struct ArcNode {         //�������Ͷ���
   		 int adjvex;              //����λ�ñ�� 
    	 struct ArcNode  *nextarc;	   //��һ������ָ��
	} ArcNode;
	typedef struct VNode{				//ͷ��㼰���������Ͷ���
   		 VertexType data;       	//������Ϣ
    	 ArcNode *firstarc;      	 //ָ���һ����
    	} VNode,AdjList[MAX_VERTEX_NUM];
	typedef  struct {  //�ڽӱ�����Ͷ���
        AdjList vertices;     	 //ͷ�������
        int vexnum,arcnum;   	  //������������
        GraphKind  kind;        //ͼ������
       } ALGraph;
#include "ctype.h"
#include "string.h"
#define free free0
#undef free

struct ptr{
    void *pused[100],*pfree[100];
    int len_used,len_free;
    } pm;
void free0(void *p)
{
    pm.pfree[pm.len_free++]=p;
    memset(p,0,sizeof(ArcNode));
    free(p);
}


status CreateCraph(ALGraph *G,VertexType V[],KeyType VR[][2])
{
int i=0,j,one,two;
VertexType e;
do {
    G->vertices[i].data=V[i];
    G->vertices[i].firstarc=NULL;
} while (V[i++].key!=-1);
G->vexnum=i-1;
i=0;
while (VR[i][0]!=-1) {
    ArcNode *p;
    for(j=0;j<G->vexnum;j++)
        if (VR[i][0]==G->vertices[j].data.key)
        {
            one=j; break;
        }
    for(j=0;j<G->vexnum;j++)
        if (VR[i][1]==G->vertices[j].data.key)
        {
            two=j; break;
        }
    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=two;p->nextarc=G->vertices[one].firstarc;G->vertices[one].firstarc=p;
    p=(ArcNode*)malloc(sizeof(ArcNode));
    p->adjvex=one;p->nextarc=G->vertices[two].firstarc;G->vertices[two].firstarc=p;
    i++;
}
G->arcnum=i;
}
status DeleteArc(ALGraph *G,KeyType v,KeyType w);
int LocateVex(ALGraph G,KeyType u);
int main()
{
ALGraph G;
VertexType V[21];
KeyType VR[100][2],v,w;
int i=0,j,k,arcs;
ArcNode *p;
do {
    scanf("%d%s",&V[i].key,V[i].others);
} while(V[i++].key!=-1);
i=0;
do {
    scanf("%d%d",&VR[i][0],&VR[i][1]);
   } while(VR[i++][0]!=-1);
CreateCraph(&G,V,VR);
arcs=G.arcnum;
scanf("%d%d",&v,&w);
for(i=0;i<G.vexnum;i++)
    if (G.vertices[i].data.key==v) break;
for(j=0;j<G.vexnum;j++)
    if (G.vertices[j].data.key==w) break;
if (i<G.vexnum && j<G.vexnum)
{
    for(p=G.vertices[i].firstarc;p;p=p->nextarc)
        if (p->adjvex==j)
            pm.pused[pm.len_used++]=p;
    for(p=G.vertices[j].firstarc;p;p=p->nextarc)
        if (p->adjvex==i)
            pm.pused[pm.len_used++]=p;
}
i=DeleteArc(&G,v,w);

    for(i=0;i<G.vexnum;i++)
	{
     p=G.vertices[i].firstarc;
     printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
     while (p)
     {
         printf(" %d",p->adjvex);
         p=p->nextarc;
     }
     printf("\n");
}
return 1;
}
status DeleteArc(ALGraph *G,KeyType v,KeyType w)
//��ͼG��ɾ����<v,w>���ɹ�����OK,���򷵻�ERROR
{
    int pos_1,pos_2,flag;
    ArcNode*p,*q;
    flag=0;
    if((pos_1=LocateVex(*G,v))==-1)
        return ERROR;
    if((pos_2=LocateVex(*G,w))==-1)
        return ERROR;
    q=G->vertices[pos_1].firstarc;
    p=G->vertices[pos_1].firstarc->nextarc;
    while(q){
        if(q->adjvex==pos_2)
            flag=1;
        q=q->nextarc;
    }
    if(!flag)//v��w֮��û�б�
        return ERROR;
    if(q->adjvex==pos_2){
        q=p;
        G->vertices[pos_1].firstarc=q;
        free(p);
    }
    else {
        while(q&&p){
            if(p->adjvex==pos_2){
                q->nextarc=p->nextarc;
                free(p);
            }
            p=p->nextarc;
            q=q->nextarc;
        }
    }
    q=G->vertices[pos_2].firstarc;
    p=G->vertices[pos_2].firstarc->nextarc;
    if(q->adjvex==pos_1){
        q=p;
        G->vertices[pos_2].firstarc=q;
        free(p);
    }
    else {
        while(q&&p){
            if(p->adjvex==pos_1){
                q->nextarc=p->nextarc;
                free(p);
            }
            p=p->nextarc;
            q=q->nextarc;
        }
    }
    return OK;
}
int LocateVex(ALGraph G,KeyType u)
//����u��ͼG�в��Ҷ��㣬���ҳɹ�����λ�򣬷��򷵻�-1��
{
   int i;
   for(i=0;i<G.vexnum;i++){
       if(G.vertices[i].data.key==u)
            return i;
   }
   return -1;
}


