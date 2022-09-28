#include<stdio.h>
#include<stdlib.h>
int main()
{
    int i,j,n;
    long long int h[20];
    scanf("%d",&n);
    h[0]=h[1]=1;
    for(i=2;i<=n;i++){
        h[i]=h[i-1]*(4*i-2)/(i+1);
    }
    printf("%d",h[n]);
    return 0;
}
