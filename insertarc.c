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
status InsertArc(ALGraph *G,KeyType v,KeyType w);
int LocateVex(ALGraph G,KeyType u);
int main()
{
ALGraph G;
VertexType V[21];
KeyType VR[100][2],v,w,arcs;
int i=0;
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
i=InsertArc(&G,v,w);
if (i==OK && G.arcnum==arcs+1)  {
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
}
else printf("���뻡����ʧ��");
return 1;
}
status InsertArc(ALGraph *G,KeyType v,KeyType w)
//��ͼG�����ӻ�<v,w>���ɹ�����OK,���򷵻�ERROR
{
   int i,pos_1,pos_2,flag[50][50]={0};
   ArcNode*p,*q,*first,*first_1;
   for(i=0;i<G->vexnum;i++){
       p=G->vertices[i].firstarc;
       while(p){
           flag[G->vertices[i].data.key][G->vertices[p->adjvex].data.key]=1;
           p=p->nextarc;
       }
   }
   if(!flag[v][w]){
        pos_1=LocateVex(*G,v);
        pos_2=LocateVex(*G,w);
        if(pos_1!=-1&&pos_2!=-1){
            first=G->vertices[pos_1].firstarc;
            p=(ArcNode*)malloc(sizeof(ArcNode));
            p->adjvex=pos_2;
            G->vertices[pos_1].firstarc=p;
            p->nextarc=first;
            first_1=G->vertices[pos_2].firstarc;
            q=(ArcNode*)malloc(sizeof(ArcNode));
            q->adjvex=pos_1;
            G->vertices[pos_2].firstarc=q;
            q->nextarc=first_1;
            G->arcnum++;
            return OK;
        }
        else
            return ERROR;
    }
   else
    return ERROR;
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