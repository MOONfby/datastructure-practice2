#include "stdio.h"
#define  MAXSIZE 10000
typedef int ElemType;
typedef struct  {
   int       i,j;//非零元行、列下标
   ElemType    e;
 } Triple;        //三元组定义

typedef struct  {
   Triple  data[MAXSIZE+1];   //三元组从下标1开始存放
   int  mu,nu,tu;         //对于矩阵的行数、列数和非零元素值
 } TSMatrix;              //三元组顺序表的定义
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
//返回矩阵A、B相加的结果
{
    TSMatrix C;
    C.mu=A.mu,C.nu=A.nu;
    int ja,jb,jc,posa[100],posb[100];
    for(ja=1;ja<=A.tu;ja++){
        posa[ja]=4*(A.data[ja].i-1)+A.data[ja].j;//计算行序位置优先函数
    }
    for(jb=1;jb<=B.tu;jb++){
        posb[jb]=4*(B.data[jb].i-1)+B.data[jb].j;//计算行序位置优先函数
    }
    ja=1,jb=1,jc=1;
    while(ja<=A.tu&&jb<=B.tu){//比较位置优先函数，相等时做加法，不等时取最小三元组
        if(posa[ja]<posb[jb]){          //不等
            C.data[jc].i=A.data[ja].i;
            C.data[jc].j=A.data[ja].j;
            C.data[jc].e=A.data[ja].e;
            C.tu++;
            ja++;
            jc++;
        }
        else if(posa[ja]>posb[jb]){     //不等
            C.data[jc].i=B.data[jb].i;
            C.data[jc].j=B.data[jb].j;
            C.data[jc].e=B.data[jb].e;
            C.tu++;
            jb++;
            jc++;
        }
        else{
            C.data[jc].i=A.data[ja].i;    //相等
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