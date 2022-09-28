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
status BFSTraverse(ALGraph *G,void (*visit)(VertexType));
void bfs(ALGraph G,int v,void(*visit)(VertexType));
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
BFSTraverse(&G,visit);
return 1;
}
int visited[MAX_VERTEX_NUM];////������飬���ʹ��ı��Ϊ1��δ���ʵı��Ϊ0
status BFSTraverse(ALGraph *G,void (*visit)(VertexType))
//��ͼG���й�������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    int i;
    for(i=0;i<G->vexnum;i++)
        visited[i]=0;
    for(i=0;i<G->vexnum;i++){
        if(!visited[i])
            bfs(*G,i,visit);
    }
    return OK;
}
void bfs(ALGraph G,int v,void(*visit)(VertexType))
{
    int queue[MAX_VERTEX_NUM];
    int front,rear,leader;
    ArcNode*p;
    front=0,rear=0;
    visited[v]=1;
    visit(G.vertices[v].data);//���ʽ��
    queue[rear++]=v;//ͷ������
    while(front<rear)//���зǿ�
    {
        leader=queue[front++];//ͷ������
        p=G.vertices[leader].firstarc;//�ҵ���һ�ڽӵ�
        while(p){
            if(!visited[p->adjvex]){
                visited[p->adjvex]=1;
                visit(G.vertices[p->adjvex].data);
                queue[rear++]=p->adjvex;//�ڽӵ����
            }
            p=p->nextarc;
        }
    }
}