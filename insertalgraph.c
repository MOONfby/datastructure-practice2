	#include "stdio.h"
	#include "stdlib.h"
    #include<string.h>
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
}
status InsertVex(ALGraph *G,VertexType v);
int main()
{
ALGraph G;
VertexType V[21],v;
KeyType VR[100][2];
int i=0;
do {
    scanf("%d%s",&V[i].key,V[i].others);
} while(V[i++].key!=-1);
i=0;
do {
    scanf("%d%d",&VR[i][0],&VR[i][1]);
   } while(VR[i++][0]!=-1);

scanf("%d%s",&v.key,v.others);

CreateCraph(&G,V,VR);
i=InsertVex(&G,v);
if (i==OK)
	for(i=0;i<G.vexnum;i++)
	{
     ArcNode *p=G.vertices[i].firstarc;
     printf("%d %s",G.vertices[i].data.key,G.vertices[i].data.others);
     while (p)
     {
         printf(" %d",p->adjvex);
         p=p->nextarc;
     }
     printf("\n");
	}
else printf("插入操作失败");
return 1;
}
status InsertVex(ALGraph *G,VertexType v)
//在图G中插入顶点v，成功返回OK,否则返回ERROR
{
    int i;
    for(i=0;i<G->vexnum;i++){
        if(G->vertices[i].data.key==v.key){
            if(strcmp(G->vertices[i].data.others,v.others))
                return ERROR;
        }
    }
    G->vertices[i].data.key=v.key;
    strcpy(G->vertices[i].data.others,v.others);
    G->vertices[i].firstarc=NULL;
    G->vexnum++;
    return OK;
}
