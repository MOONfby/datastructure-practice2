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
} VertexType; //顶点类型定义
typedef struct ArcNode {         //表结点类型定义
	 int adjvex;              //顶点位置编号 
	 struct ArcNode  *nextarc;	   //下一个表结点指针
} ArcNode;
typedef struct VNode{				//头结点及其数组类型定义
	 VertexType data;       	//顶点信息
	 ArcNode *firstarc;      	 //指向第一条弧
	} VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
    AdjList vertices;     	 //头结点数组
    int vexnum,arcnum;   	  //顶点数、弧数
    GraphKind  kind;        //图的类型
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
                printf("未正确释放表结点");
                return 1;
            }
        }
        printf("OK");
    }
    else printf("ERROR");
return 1;
}
status DestroyGraph(ALGraph *G)
/*销毁无向图G,删除G的全部顶点和边*/
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

