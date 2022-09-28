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
status DeleteVex(ALGraph *G,KeyType v);
int LocateVex(ALGraph G,KeyType u);
void Deletearc(ALGraph* G,int arc,int pos);
int main()
{
ALGraph G;
VertexType V[21];
KeyType VR[100][2];
int i=0,j,v,del_arcs=0,arcs,vexs;
do {
    scanf("%d%s",&V[i].key,V[i].others);
} while(V[i++].key!=-1);
i=0;
do {
    scanf("%d%d",&VR[i][0],&VR[i][1]);
   } while(VR[i++][0]!=-1);
CreateCraph(&G,V,VR);
scanf("%d",&v);
for(i=0;i<G.vexnum;i++)
    if (G.vertices[i].data.key==v) break;
if (i<G.vexnum)
{
    ArcNode *p;
    arcs=G.arcnum;
    vexs=G.vexnum;
    for(p=G.vertices[i].firstarc;p;p=p->nextarc)
    {
        pm.pused[pm.len_used++]=p;
        del_arcs++;
    }
    for(j=0;j<G.vexnum;j++)
    {
        for(p=G.vertices[j].firstarc;p;p=p->nextarc)
            if (p->adjvex==i)
                pm.pused[pm.len_used++]=p;
    }
}
i=DeleteVex(&G,v);
if (i==OK && G.arcnum==arcs-del_arcs&&vexs==G.vexnum+1&&pm.len_used==pm.len_free)
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
else printf("ɾ���������ʧ��");
return 1;
}
status DeleteVex(ALGraph *G,KeyType v)
//��ͼG��ɾ���ؼ���v��Ӧ�Ķ����Լ���صĻ����ɹ�����OK,���򷵻�ERROR
{
    int pos,i,arc;
    ArcNode*p,*q;
    pos=LocateVex(*G,v);
    if(pos!=-1)
    {
        p=G->vertices[pos].firstarc;//��v��صĻ�
        while(p){
            arc=p->adjvex;
            Deletearc(G,arc,pos);//ɾ����ػ�
            G->arcnum--;
            p=p->nextarc;
        }
        for(i=pos;i<G->vexnum;i++){  //ɾ������
            G->vertices[i]=G->vertices[i+1];
        }
        G->vexnum--;
        for(i=0;i<G->vexnum;i++){//�޸�λ��
            p=G->vertices[i].firstarc;
            for(p;p;p=p->nextarc){
                if(p->adjvex>=pos)
                    p->adjvex--;
            }
        }
        return OK;
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
void Deletearc(ALGraph* G,int arc,int pos)
{
    ArcNode*p,*q;
    p=G->vertices[arc].firstarc->nextarc;
    q=G->vertices[arc].firstarc;
    if(q->adjvex==pos){
        q=p;
        G->vertices[arc].firstarc=q;
    }
    else {
        while(q){
            if(p->adjvex==pos){
                q->nextarc=p->nextarc;
            }
            p=p->nextarc;
            q=q->nextarc;
        }
    }
}
