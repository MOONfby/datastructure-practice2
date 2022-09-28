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
void visit(VertexType v)
{
    printf(" %d %s",v.key,v.others);
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
}
status DFSTraverse(ALGraph *G,void (*visit)(VertexType));
void dfs(ALGraph G,int v,void (*visit)(VertexType));
int main()
{
ALGraph G;
VertexType V[21];
KeyType VR[100][2],v,w;
int i=0;
do {
    scanf("%d%s",&V[i].key,V[i].others);
} while(V[i++].key!=-1);
i=0;
do {
    scanf("%d%d",&VR[i][0],&VR[i][1]);
   } while(VR[i++][0]!=-1);
CreateCraph(&G,V,VR);
DFSTraverse(&G,visit);
return 1;
}
int visited[MAX_VERTEX_NUM];//标记数组，访问过的标记为1，未访问的标记为0
status DFSTraverse(ALGraph *G,void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    int i;
    for(i=0;i<G->vexnum;i++)//标记数组初始化
        visited[i]=0;
    for(i=0;i<G->vexnum;i++){//不确定图是否连通，从图中的每一个顶点开始访问
        if(!visited[i])
            dfs(*G,i,visit);
    }
    return OK;
}
void dfs(ALGraph G,int v,void (*visit)(VertexType))
{
    ArcNode*p;
    visited[v]=1;
    visit(G.vertices[v].data);//输出数据
    p=G.vertices[v].firstarc;//找邻接点
    while(p)
    {
        if(!visited[p->adjvex])//递归调用
            dfs(G,p->adjvex,visit);
        p=p->nextarc;
    }
}