	#include "stdio.h"
	#include "stdlib.h"
    #include"string.h"
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
status PutVex(ALGraph *G,KeyType u,VertexType value);
int LocateVex(ALGraph G,KeyType u);
int main()
{
ALGraph G;
VertexType V[21],value;
KeyType VR[100][2];
int i=0,u;
do {
    scanf("%d%s",&V[i].key,V[i].others);
} while(V[i++].key!=-1);
i=0;
do {
    scanf("%d%d",&VR[i][0],&VR[i][1]);
   } while(VR[i++][0]!=-1);
scanf("%d",&u);   
scanf("%d%s",&value.key,value.others);
CreateCraph(&G,V,VR);
i=PutVex(&G,u,value);
if (i==OK)
   for(i=0;i<G.vexnum;i++)
     printf(" %d %s",G.vertices[i].data.key,G.vertices[i].data.others);
else
	printf("��ֵ����ʧ��");
return 1;
}
status PutVex(ALGraph *G,KeyType u,VertexType value)
//����u��ͼG�в��Ҷ��㣬���ҳɹ����ö���ֵ�޸ĳ�value������OK��
//�������ʧ�ܻ�ؼ��ֲ�Ψһ������ERROR
{
    int pos,new;
    pos=LocateVex(*G,u);
    new=LocateVex(*G,value.key);
    if(pos!=-1){
        if(new!=-1){
            if(strcmp(value.others,G->vertices[new].data.others))
                return ERROR;
        }
        G->vertices[pos].data.key=value.key;
        strcpy(G->vertices[pos].data.others,value.others);
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