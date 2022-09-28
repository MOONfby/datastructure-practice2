#include<stdio.h>
#include<stdlib.h>
typedef int ElemType;
void ShiftRightCircular(ElemType *A,int n,int k);
int main()
{
    int n,i,k;
    ElemType *p;
    scanf("%d%d",&n,&k);
    p=(int *)malloc(n*sizeof(int));
    for(i=0;i<n;i++)
        p[i]=i+1;
    ShiftRightCircular(p,n,k);
    for(i=0;i<n;i++)
        printf(" %d",p[i]);
    return 1;
}
void ShiftRightCircular(ElemType *A,int n,int k)
{
    ElemType *q;
    int i,j;
    if(k>0){
        if(k>n)
            k-=n;
        q=(int *)malloc((n-k)*sizeof(int));
        for(i=0,j=0;i<n-k;i++,j++){
            *(q+j)=*(A+i); //��ǰn-kλԪ�ر�����q������
        }
        for(i=n-k,j=0;i<n;i++,j++){
            *(A+j)=*(A+i);  
        }
        for(i=k,j=0;i<n;i++,j++){
            *(A+i)=*(q+j);
        }
    }
    else if(k<0){
        k=abs(k);
        if(k>n)
            k-=n;
        q=(int *)malloc((n-k)*sizeof(int));
        for(i=0;i<k;i++){
            *(q+i)=*(A+i);//����ǰkλԪ��
        }
        for(i=0,j=k;j<n;i++,j++){
            *(A+i)=*(A+j);//�ƶ�n-kλԪ��
        }
        for(i=n-k,j=0;i<n;i++,j++){
            *(A+i)=*(q+j);//�Ѻ�kλ�Ƶ�ǰ��
        }
    }
}