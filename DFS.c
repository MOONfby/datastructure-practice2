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
int visited[MAX_VERTEX_NUM];//������飬���ʹ��ı��Ϊ1��δ���ʵı��Ϊ0
status DFSTraverse(ALGraph *G,void (*visit)(VertexType))
//��ͼG������������������������ζ�ͼ�е�ÿһ������ʹ�ú���visit����һ�Σ��ҽ�����һ��
{
    int i;
    for(i=0;i<G->vexnum;i++)//��������ʼ��
        visited[i]=0;
    for(i=0;i<G->vexnum;i++){//��ȷ��ͼ�Ƿ���ͨ����ͼ�е�ÿһ�����㿪ʼ����
        if(!visited[i])
            dfs(*G,i,visit);
    }
    return OK;
}
void dfs(ALGraph G,int v,void (*visit)(VertexType))
{
    ArcNode*p;
    visited[v]=1;
    visit(G.vertices[v].data);//�������
    p=G.vertices[v].firstarc;//���ڽӵ�
    while(p)
    {
        if(!visited[p->adjvex])//�ݹ����
            dfs(G,p->adjvex,visit);
        p=p->nextarc;
    }
}