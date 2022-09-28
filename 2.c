#include<stdio.h> 
#include<math.h> 
int main()
{
int u,n1;
float d=0.005,n=0.0000183,s=0.0015,p1=981,p2=1.2928,g=9.795,b=0.00823,p=101325;
float x,y,z,w,v,q,e,t,n0;

printf("输⼊电压和时间\n") ; scanf("%d%f",&u,&t) ;


x=sqrt(1/((p1-p2)*g)); y=9*sqrt(2)*d*3.1415926/u; z=sqrt(n*n*n*s*s*s/t/t/t); w=1/(1+b/(p*sqrt(9*n*s/(2*g*t*(p1-p2))))); v=sqrt(w*w*w);

q=x*y*z*v*1E19;


n0=(q/1.6021892); n1=q/1.6021892;

if((n0-n1)>0.5) n1++;



e=q/n1;

printf("电荷q值是：%f\n",q); printf("整数倍n值是：%d\n",n1); printf("所测电荷e值为%f",e) ;
}