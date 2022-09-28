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
typedef enum {DG,DN,UDG,UDN} GraphKind;//有向图，有向网，无向图，无向网
typedef struct {
     KeyType  key;
     char others[20];
} VertexType; //顶点类型定义
typedef struct ArcNode {         //表结点类型定义
	 int adjvex;              //顶点位置编号 
	 struct ArcNode  *nextarc;	   //下一个表结点指针
} ArcNode;
typedef struct VNode{				//头结点及其数组类型定义（表头结点）
	 VertexType data;       	//顶点信息
	 ArcNode *firstarc;      	 //指向第一条弧
	} VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
    AdjList vertices;     	 //头结点数组
    int vexnum,arcnum;   	  //顶点数、弧数
    GraphKind  kind;        //图的类型
   } ALGraph;
status CreateCraph(ALGraph *G,VertexType V[],KeyType VR[][2]);
int LocateVex(ALGraph G,KeyType u);
int main()
{
    ALGraph G;
    VertexType V[30];
    KeyType VR[100][2];//顶点之间的关系
    int i=0,j;
    do {
        scanf("%d%s",&V[i].key,V[i].others);
    } while(V[i++].key!=-1);
    i=0;
    do {
        scanf("%d%d",&VR[i][0],&VR[i][1]);
       } while(VR[i++][0]!=-1);
    if (CreateCraph(&G,V,VR)==ERROR) printf("输入数据错，无法创建");
    else 
        {
             if (G.arcnum!=i-1) {
         	    printf("边的数目错误！\n");
                return 0; 
            }
            for(j=0;j<G.vexnum;j++)
    	    {
                ArcNode *p=G.vertices[j].firstarc;
                printf("%d %s",G.vertices[j].data.key,G.vertices[j].data.others);
                while (p)
                {
                    printf(" %d",p->adjvex);
                    p=p->nextarc;
                }
                printf("\n");
    	    }
        }
    return 1;
}
status CreateCraph(ALGraph *G,VertexType V[],KeyType VR[][2])
/*根据V和VR构造图T并返回OK，如果V和VR不正确，返回ERROR
如果有相同的关键字，返回ERROR。此题允许通过增加其它函数辅助实现本关任务*/
{
    int i,j,pos,flag[50][50]={0};
    ArcNode*p,*first;
    if(V[0].key==-1)
        return ERROR;
    for(i=0;V[i].key!=-1;i++){  //判断关键字是否唯一
        for(j=i+1;V[j].key!=-1;j++){
            if(V[i].key==V[j].key){//key相同
                if(strcmp(V[i].others,V[j].others))//others是否相同
                    return ERROR;
            }
        }
    }
    G->vexnum=i;//图中的顶点数
    if(G->vexnum>MAX_VERTEX_NUM)//数组溢出
        return ERROR;
    for(i=0;V[i].key!=-1;i++){
        G->vertices[i].data.key=V[i].key;//各个顶点的信息
        strcpy(G->vertices[i].data.others,V[i].others);
        G->vertices[i].firstarc=NULL;
    }
    for(i=0;VR[i][0]!=-1;i++){
        if(VR[i][0]==VR[i][1])//简单无向图中不包含环
            continue;
        for(j=0;;j++){
            if(G->vertices[j].data.key==VR[i][0]){//寻找弧头
                pos=LocateVex(*G,VR[i][1]);//寻找弧尾的位置编号
                if(!flag[VR[i][0]][VR[i][1]]||!flag[VR[i][1]][VR[i][0]]){
                    if(pos>0||!pos){
                        if(!G->vertices[j].firstarc){
                            G->vertices[j].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
                            G->vertices[j].firstarc->adjvex=pos;
                            G->vertices[j].firstarc->nextarc=NULL;
                        }
                        else{
                            first=G->vertices[j].firstarc;
                            p=(ArcNode*)malloc(sizeof(ArcNode));
                            p->adjvex=pos;
                            G->vertices[j].firstarc=p;
                            p->nextarc=first;
                        }
                        if(!G->vertices[pos].firstarc){
                            G->vertices[pos].firstarc=(ArcNode*)malloc(sizeof(ArcNode));
                            G->vertices[pos].firstarc->adjvex=j;
                            G->vertices[pos].firstarc->nextarc=NULL;
                        }
                        else{
                            first=G->vertices[pos].firstarc;
                            p=(ArcNode*)malloc(sizeof(ArcNode));
                            p->adjvex=j;
                            G->vertices[pos].firstarc=p;
                            p->nextarc=first;
                        }
                        flag[VR[i][0]][VR[i][1]]=1;
                        flag[VR[i][1]][VR[i][0]]=1;
                        break;
                    }
                    else 
                        return ERROR;//无此顶点，输入数据错
                }
                else
                    break;
            }
            if(j==G->vexnum)//无此顶点，输入数据错
                return ERROR;
        }
    }
    G->arcnum=i;
    G->kind=UDG; 
}
int LocateVex(ALGraph G,KeyType u)
//根据u在图G中查找顶点，查找成功返回位序，否则返回-1；
{
   int i;
   for(i=0;i<G.vexnum;i++){
       if(G.vertices[i].data.key==u)
            return i;
   }
   return -1;
}