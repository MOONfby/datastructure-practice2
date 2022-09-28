#include "stdio.h"
#define  MAXSIZE 10000
typedef int ElemType;
typedef struct  {
   int       i,j;//����Ԫ�С����±�
   ElemType    e;
 } Triple;        //��Ԫ�鶨��

typedef struct  {
   Triple  data[MAXSIZE+1];   //��Ԫ����±�1��ʼ���
   int  mu,nu,tu;         //���ھ���������������ͷ���Ԫ��ֵ
 } TSMatrix;              //��Ԫ��˳���Ķ���
TSMatrix ADD(TSMatrix A,TSMatrix B);
int main()
{
	TSMatrix A[3],B,C;
   int i,j;
   for(i=0;i<2;i++)
   {
   		scanf("%d%d%d",&A[i].mu,&A[i].nu,&A[i].tu);
   		for(j=1;j<=A[i].tu;j++)
   		 	scanf("%d%d%d",&A[i].data[j].i,&A[i].data[j].j,&A[i].data[j].e);
   }
   A[2]=ADD(A[0],A[1]);
   printf("%d %d %d\n",A[2].mu,A[2].nu,A[2].tu);
   for(i=1;i<=A[2].tu;i++)
   		printf("%d %d %d     ",A[2].data[i].i,A[2].data[i].j,A[2].data[i].e);
	return 1;
}
TSMatrix ADD(TSMatrix A,TSMatrix B)
//���ؾ���A��B��ӵĽ��
{
    TSMatrix C;
    C.mu=A.mu,C.nu=A.nu;
    int ja,jb,jc,posa[100],posb[100];
    for(ja=1;ja<=A.tu;ja++){
        posa[ja]=4*(A.data[ja].i-1)+A.data[ja].j;//��������λ�����Ⱥ���
    }
    for(jb=1;jb<=B.tu;jb++){
        posb[jb]=4*(B.data[jb].i-1)+B.data[jb].j;//��������λ�����Ⱥ���
    }
    ja=1,jb=1,jc=1;
    while(ja<=A.tu&&jb<=B.tu){//�Ƚ�λ�����Ⱥ��������ʱ���ӷ�������ʱȡ��С��Ԫ��
        if(posa[ja]<posb[jb]){          //����
            C.data[jc].i=A.data[ja].i;
            C.data[jc].j=A.data[ja].j;
            C.data[jc].e=A.data[ja].e;
            C.tu++;
            ja++;
            jc++;
        }
        else if(posa[ja]>posb[jb]){     //����
            C.data[jc].i=B.data[jb].i;
            C.data[jc].j=B.data[jb].j;
            C.data[jc].e=B.data[jb].e;
            C.tu++;
            jb++;
            jc++;
        }
        else{
            C.data[jc].i=A.data[ja].i;    //���
            C.data[jc].j=A.data[ja].j;
            C.data[jc].e=A.data[ja].e+B.data[jb].e;
            if(C.data[jc].e!=0){
                C.tu++;
                jc++;
            }
            ja++;
            jb++;
        }
    }
    if(ja<=A.tu){
        C.data[jc].i=A.data[ja].i;
        C.data[jc].j=A.data[ja].j;
        C.data[jc].e=A.data[ja].e;
        C.tu++;
        jc++;
        ja++;
    }
    if(jb<=B.tu){
        C.data[jc].i=B.data[ja].i;
        C.data[jc].j=B.data[ja].j;
        C.data[jc].e=B.data[jb].e;
        C.tu++;
        jc++;
        jb++;
    }
    return C;
}