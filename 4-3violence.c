#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
	char *ch;
   int length;
} HString;
void Replace(HString* S,HString T,HString V);
int main()
{
    HString S[3];
    char buf[100],i,j;
    for(i=0;i<3;i++)
    {
        fgets(buf,100,stdin);
        S[i].length=strlen(buf)-1;  //-1��ȥ���س�����
        S[i].ch=(char *)malloc(S[i].length);
        for(j=0;j<S[i].length; j++)
            S[i].ch[j]=*(buf+j);
    }
    Replace(&S[0],S[1],S[2]);
    printf("S�ĳ���:%d\n",S[0].length);
    for(i=0;i<S[0].length;i++)
        putchar(S[0].ch[i]);
    return 1;
}
void Replace(HString* S,HString T,HString V)
{
    int i,j,m,n;
    char *p,*q;
    i=0;
    for(i=0;i<S->length;i++){
        for(j=0,m=i;j<T.length;j++,m++){
            if(S->ch[m]!=T.ch[j])
                break;
        }
        if(j==T.length){  //ƥ��ɹ�
            m-=j;
            if(T.length==V.length){//���滻�Ӵ����滻���������
                for(n=0;n<V.length;n++){
                    S->ch[m]=V.ch[n];  
                    m++;    
                }
            }
            else if(T.length<V.length){//���滻�Ӵ����滻�Ӵ���
                q=&S->ch[m+T.length];
                for(p=&S->ch[S->length-1];p>=q;p--){//����
                    *(p+V.length-T.length)=*p;
                }
                for(n=0;n<V.length;n++){
                    S->ch[m]=V.ch[n];
                    m++;      
                }
                S->length=S->length+V.length-T.length;
            }
            else{                     //���滻�Ӵ����滻�Ӵ���
                q=&S->ch[S->length-1];
                for(p=&S->ch[i+T.length];p<=q;p++){//ǰ��
                    *(p-T.length+V.length)=*p;
                }
                for(n=0;n<V.length;n++){
                    S->ch[m]=V.ch[n];   
                    m++;   
                }
                S->length=S->length-T.length+V.length;
            }
        }
    }
}
