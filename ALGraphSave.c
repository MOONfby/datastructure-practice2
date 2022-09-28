	#include "stdio.h"
	#include "stdlib.h"
    #include "string.h"
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
status LoadGraph(ALGraph *G, char FileName[]);
status SaveGraph(ALGraph G, char FileName[]);
int main()
{
    ALGraph G,G1;
    G1.vexnum=0;
    VertexType V[21];
    KeyType VR[100][2];
    char FileName[20];
    scanf("%s",FileName);
    int i=0;
    do {
        scanf("%d%s",&V[i].key,V[i].others);
    } while(V[i++].key!=-1);
    i=0;
    do {
        scanf("%d%d",&VR[i][0],&VR[i][1]);
       } while(VR[i++][0]!=-1);
    CreateCraph(&G,V,VR);
    SaveGraph(G,FileName);
    //G.vexnum=0;
    LoadGraph(&G1,FileName);
    for(i=0;i<G1.vexnum;i++)
    {
         ArcNode *p=G1.vertices[i].firstarc;
         printf("%d %s",G1.vertices[i].data.key,G1.vertices[i].data.others);
         while (p)
         {
             printf(" %d",p->adjvex);
             p=p->nextarc;
         }
         printf("\n");
    }
return 1;
}
status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    FILE *fp;
    int i,m,arc,VR[100]={0},flag[50][50]={0};
    ArcNode *p;
    m=0,arc=0;
    if((fp=fopen(FileName,"wb"))==NULL)
        return ERROR;
    for(i=0;i<G.vexnum;i++){
        fprintf(fp,"%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
    }
    fprintf(fp,"-1 nil ");
    for(i=0;i<G.vexnum;i++)
    {
        p=G.vertices[i].firstarc;
        while(p)
        {
            if(!flag[G.vertices[i].data.key][G.vertices[p->adjvex].data.key]){
                VR[m++]=G.vertices[i].data.key;
                VR[m++]=G.vertices[p->adjvex].data.key;
                arc=arc+2;
                flag[G.vertices[i].data.key][G.vertices[p->adjvex].data.key]=1;
                flag[G.vertices[p->adjvex].data.key][G.vertices[i].data.key]=1;
            }
            p=p->nextarc;
        }
    }
    for(i=0;i<arc;i++)
    {
        fprintf(fp,"%d ",VR[i]);
    }
    fprintf(fp,"-1 -1 ");
    fclose(fp);
    return OK;
}
status LoadGraph(ALGraph *G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    FILE *fp;
    int i=0;
    VertexType V[MAX_VERTEX_NUM];
    int VR[100][2];
    fp=fopen(FileName,"rb");
        do {
            fscanf(fp,"%d%s",&V[i].key,V[i].others);
        } while(V[i++].key!=-1);
        i=0;
        while(VR[i++][0]!=-1){
            fscanf(fp,"%d%d",&VR[i][0],&VR[i][1]);
        } 
    CreateCraph(G,V,VR);
    return OK;
}
