#include <stdio.h>
#include <stdlib.h>
#include<math.h>
int suanfa(int a[],int n, int arrsize);
int main()
 {
    int k,*a,arrsize;
    scanf("%d%d",&k,&arrsize);
    a=(int *)malloc(arrsize*sizeof(int));
    if (suanfa(a,k,arrsize))
        for(int i=0;i<k;i++)
            printf(" %d",a[i]);
    else printf("ERROR");
    return 1;
 }
int suanfa(int a[],int n, int arrsize)
{
    int i,j,fac;
    if(n>arrsize)
        return 0;
    for(i=1;i<=n;i++){
        fac=1;
        for(j=1;j<=i;j++){
            fac*=j;
        }
        a[i-1]=fac*pow(2.0,(double)i);
        if(a[i-1]<0)
            return 0;
    }
    return 1;
        
}
