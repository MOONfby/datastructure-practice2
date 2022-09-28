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
   void free0(void  *p);
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
    G->arcnum=i-1;
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
        pm.pused[pm.len_used++]=p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=two;p->nextarc=G->vertices[one].firstarc;G->vertices[one].firstarc=p;
        pm.pused[pm.len_used++]=p=(ArcNode*)malloc(sizeof(ArcNode));
        p->adjvex=one;p->nextarc=G->vertices[two].firstarc;G->vertices[two].firstarc=p;
        i++;
    }
    G->arcnum=i;
}
status DestroyGraph(ALGraph *G);
int main()
{
    ALGraph G;
    VertexType V[21];
    KeyType VR[100][2];
    int i=0,j;
    do {
        scanf("%d%s",&V[i].key,V[i].others);
    } while(V[i++].key!=-1);
    i=0;
    do {
        scanf("%d%d",&VR[i][0],&VR[i][1]);
       } while(VR[i++][0]!=-1);
    CreateCraph(&G,V,VR);  
    DestroyGraph(&G);
    if (G.vexnum==0 && G.arcnum==0)
    {
        for(i=0;i<pm.len_used;i++)
        {
            for(j=0;j<pm.len_free;j++)
                if (pm.pused[i]==pm.pfree[j]) break;
            if (j>=pm.len_free)
            {
                printf("δ��ȷ�ͷű���");
                return 1;
            }
        }
        printf("OK");
    }
    else printf("ERROR");
return 1;
}
status DestroyGraph(ALGraph *G)
/*��������ͼG,ɾ��G��ȫ������ͱ�*/
{
    int i;
    ArcNode *p,*q;
    for(i=0;i<G->vexnum;i++){
        p=G->vertices[i].firstarc;
        while(p){
            q=p;
            p=p->nextarc;
            free(q);
        }
    }
    G->arcnum=0;
    G->vexnum=0;
    return OK;
}

