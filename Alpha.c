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
typedef enum {DG,DN,UDG,UDN} GraphKind;//����ͼ��������������ͼ��������
typedef struct {
     KeyType  key;
     char others[20];
} VertexType; //�������Ͷ���
typedef struct ArcNode {         //�������Ͷ���
	 int adjvex;              //����λ�ñ�� 
	 struct ArcNode  *nextarc;	   //��һ������ָ��
} ArcNode;
typedef struct VNode{				//ͷ��㼰���������Ͷ��壨��ͷ��㣩
	 VertexType data;       	//������Ϣ
	 ArcNode *firstarc;      	 //ָ���һ����
	} VNode,AdjList[MAX_VERTEX_NUM];
typedef  struct {  //�ڽӱ�����Ͷ���
    AdjList vertices;     	 //ͷ�������
    int vexnum,arcnum;   	  //������������
    GraphKind  kind;        //ͼ������
   } ALGraph;
status CreateCraph(ALGraph *G,VertexType V[],KeyType VR[][2]);
int LocateVex(ALGraph G,KeyType u);
int main()
{
    ALGraph G;
    VertexType V[30];
    KeyType VR[100][2];//����֮��Ĺ�ϵ
    int i=0,j;
    do {
        scanf("%d%s",&V[i].key,V[i].others);
    } while(V[i++].key!=-1);
    i=0;
    do {
        scanf("%d%d",&VR[i][0],&VR[i][1]);
       } while(VR[i++][0]!=-1);
    if (CreateCraph(&G,V,VR)==ERROR) printf("�������ݴ��޷�����");
    else 
        {
             if (G.arcnum!=i-1) {
         	    printf("�ߵ���Ŀ����\n");
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
/*����V��VR����ͼT������OK�����V��VR����ȷ������ERROR
�������ͬ�Ĺؼ��֣�����ERROR����������ͨ������������������ʵ�ֱ�������*/
{
    int i,j,pos,flag[50][50]={0};
    ArcNode*p,*first;
    if(V[0].key==-1)
        return ERROR;
    for(i=0;V[i].key!=-1;i++){  //�жϹؼ����Ƿ�Ψһ
        for(j=i+1;V[j].key!=-1;j++){
            if(V[i].key==V[j].key){//key��ͬ
                if(strcmp(V[i].others,V[j].others))//others�Ƿ���ͬ
                    return ERROR;
            }
        }
    }
    G->vexnum=i;//ͼ�еĶ�����
    if(G->vexnum>MAX_VERTEX_NUM)//�������
        return ERROR;
    for(i=0;V[i].key!=-1;i++){
        G->vertices[i].data.key=V[i].key;//�����������Ϣ
        strcpy(G->vertices[i].data.others,V[i].others);
        G->vertices[i].firstarc=NULL;
    }
    for(i=0;VR[i][0]!=-1;i++){
        if(VR[i][0]==VR[i][1])//������ͼ�в�������
            continue;
        for(j=0;;j++){
            if(G->vertices[j].data.key==VR[i][0]){//Ѱ�һ�ͷ
                pos=LocateVex(*G,VR[i][1]);//Ѱ�һ�β��λ�ñ��
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
                        return ERROR;//�޴˶��㣬�������ݴ�
                }
                else
                    break;
            }
            if(j==G->vexnum)//�޴˶��㣬�������ݴ�
                return ERROR;
        }
    }
    G->arcnum=i;
    G->kind=UDG; 
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