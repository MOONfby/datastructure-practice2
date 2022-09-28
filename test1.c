#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2

typedef int status; 
typedef int ElemType; //数据元素类型定义

#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10
#define INFEASIBLE -1

typedef struct Sqlist{  //顺序表（顺序结构）的定义
	ElemType * elem;
	int length;
	int listsize;
}SqList;

typedef struct{  //线性表的管理表定义
struct { char name[30];
    SqList L;	
    } elem[10];
    int length;
    int listsize;
}LISTS;

status InitList(SqList *L);
status DestroyList(SqList *L);
status ClearList(SqList *L);
status ListEmpty(SqList L);
status ListLength(SqList L);
status GetElem(SqList L,int i,ElemType *e);
status LocateElem(SqList L,ElemType e);
status PriorElem(SqList L,ElemType cur,ElemType *pre_e);
status NextElem(SqList L,ElemType cur,ElemType *next_e);
status ListInsert(SqList *L,int i,ElemType e);
status ListDelete(SqList *L,int i,ElemType *e);
status ListTrabverse(SqList L);
status SaveList(SqList L,char FileName[]);
status LoadList(SqList *L,char FileName[]);
status AddList(LISTS *Lists,char ListName[]);
status RemoveList(LISTS *Lists,char ListName[]);
int LocateList(LISTS Lists,char ListName[]);
void mmm(LISTS *Lists);
void ListsTraverse(LISTS Lists); 


int main()
{
SqList L;
LISTS Lists;  
int op=1;
L.elem=NULL;
Lists.length=0;
while(op){
printf("      Menu for Linear Table On Sequence Structure \n");
printf("-------------------------------------------------\n");
printf("    	  1. InitList         7. LocateElem\n");
printf("    	  2. DestroyList      8. PriorElem\n");
printf("    	  3. ClearList        9. NextElem \n");
printf("    	  4. ListEmpty        10. ListInsert\n");
printf("    	  5. ListLength       11. ListDelete\n");
printf("    	  6. GetElem          12. ListTrabverse\n");
printf("          13.SaveList         14.LoadList\n");
printf("          15.AddList          16.RemoveList\n");
printf("          17.LocateList       18.mmm\n");
printf("    	  0. Exit\n");
printf("-------------------------------------------------\n");
printf("    请选择你的操作[0~12]:");
scanf("%d",&op);
int i=1,j,c,e=1,pre,next,n;
char name[30];
switch(op)
{
    case 1:
    if(InitList(&L)==OK)
    printf("线性表创建成功！\n");
    else
    printf("线性表创建失败！\n");
    break;

    case 2:
    if(DestroyList(&L)==OK)
    printf("线性表销毁成功！\n");
    else
    printf("线性表销毁失败！\n");
    break;

    case 3:
    if(ClearList(&L)==OK)
    printf("线性表清空成功！\n");
    else
    printf("线性表清空失败！\n");
    break;

    case 4:
    if(ListEmpty(L)==OK)
    printf("线性表为空！\n");
    else
    printf("线性表不为空！\n");
    break;

    case 5:
	j=ListLength(L);
	if(j==INFEASIBLE)
		printf("线性表不存在");
	else 
		printf("线性表的长度为%d", j);
    break;

    case 6:
    printf("你要查找第几个元素？");
	scanf("%d",&i);
	j=GetElem(L,i,&e);
	if(j==OK) printf("第%d个元素是%d",i,j);
	if(j==ERROR) printf("无法查找");
    break;

    case 7:
    printf("你要查找哪个元素？");
	scanf("%d",&e);
	j=LocateElem(L,e);
	if(j==ERROR) printf("无法查找");
	else printf("元素%d在第%d位",e,j);
    break;

    case 8:
    printf("你要获取谁的前驱？");
	scanf("%d",&e);
	if(e==L.elem[0])
	printf("此元素无前驱");
	else{
		j=PriorElem(L,e,&pre);
	if(j==ERROR) printf("无法获取");
	if(j==OK) printf("元素%d的前驱是%d",e,pre);
	}
    break;

    case 9:
    printf("你要获取谁的后继？");
	scanf("%d",&e);
	if(e==L.elem[L.length-1])
	printf("此元素无后继");
	else{
			j=NextElem(L,e,&next);
	if(j==ERROR) printf("无法获取");
	if(j==OK) printf("元素%d的后继是%d",e,next);
	}
    break;

    case 10:
    printf("请输入要插入的位置和元素");
    scanf("%d%d",&i,&e);
    j=ListInsert(&L,i,e);
    if(j==ERROR) printf("错误\n");
	if(j==OK)
    {
        for(i=0;i<L.length;i++)
        printf("%d ",L.elem[i]);
    }
    break;

    case 11:
    printf("请输入要删除的元素");
	scanf("%d",&i);
	j=ListDelete(&L,i,&e);
	if(j==ERROR) printf("错误\n");
	if(j==OK)
    {
        for(i=0;i<L.length;i++)
        printf("%d ",L.elem[i]);
    }
    break;

    case 12:
	j=ListTrabverse(L);
    break;

    case 13:
    printf("请输入要保存的文件名");
    scanf("%s",name);
    j=SaveList(L,name);
    break;
    
    case 14:
    printf("请输入要读入的文件名");
    scanf("%s",name);
    j=LoadList(&L,name);
    break;

    case 15:
    
    printf("你要添加几个线性表？");
	scanf("%d", &n);
	while(n--)
    {
    	printf("线性表的名字是什么？"); 
    	scanf("%s",name);
   		AddList(&Lists,name);
    }
    
    break;

    case 16:
    printf("线性表的名字是什么？");
	scanf("%s",name);
    if (RemoveList(&Lists,name)==OK)
	printf("OK");
    else printf("删除失败");
    break;

    case 17:
    printf("线性表的名字是什么？");
    scanf("%s",name);
    if (n=LocateList(Lists,name))
   		{
   		   printf("%s ",Lists.elem[n-1].name);
   		   ListTrabverse(Lists.elem[n-1].L);
           putchar('\n');
   		}
    else printf("查找失败");
    break;
    
    case 18:
    mmm(&Lists);
    break;
    case 19:
    ListsTraverse(Lists); 
}
}
return 0;
}


status InitList(SqList *L)
{
if(L->elem)
return INFEASIBLE;
else 
L->elem=(ElemType*)malloc(LIST_INIT_SIZE*sizeof(ElemType));
L->length=0;
L->listsize=LIST_INIT_SIZE;
return OK;
}

status DestroyList(SqList *L)
{
if(L->elem)
{
    free(L->elem);
    L->elem=NULL;
    L->length=0;
    L->listsize=0;
    return OK;
}
else
return INFEASIBLE;
}

status ClearList(SqList *L)
{
if(L->elem)
{
    L->length=0;
    return OK;
}
else return INFEASIBLE;
}


status ListEmpty(SqList L)
{
if(L.elem)
{
    if(L.length==0)
    return TRUE;
    else
    return FALSE;
}
else
return INFEASIBLE;
}

status ListLength(SqList L)
{
if(L.elem)
{
    return L.length;
}
else
return INFEASIBLE;
}

status GetElem(SqList L,int i,ElemType *e)
{
if(L.elem)
{
    if(i<1||i>L.length)
    return ERROR;
    else 
    {
        *e=L.elem[i-1];
        return OK;
    }
}
else return INFEASIBLE;
}

int LocateElem(SqList L,ElemType e)
{
if(L.elem)
{
    int i=0;
    while(i<L.length&&L.elem[i]!=e)
    i++;
    if(i<L.length)
    {
        i++;
        return i;
    }
    else return ERROR;
}
else return INFEASIBLE;
}

status PriorElem(SqList L,ElemType e,ElemType *pre)
{
if(L.elem)
{
    int i=1;
    while(i<L.length&&L.elem[i]!=e)
    i++;
    if(i<L.length)
    {
        *pre=L.elem[i-1];
        return OK;
    }
    else return ERROR;
}
else return INFEASIBLE;
}

status NextElem(SqList L,ElemType e,ElemType *next)
{
    if(L.elem)
    {
        int i=1;
        while(i<L.length&&L.elem[i]!=e)
        i++;
        if(i<(L.length-1))
        {
            *next=L.elem[i+1];
            return OK;
        }
        else return ERROR;
    }
    else 
        return INFEASIBLE;
}

status ListInsert(SqList *L,int i,ElemType e)
{
if(L->elem)
{
    ElemType *newbase;
    ElemType *p,*q;
    
    if(L->length>=L->listsize)
    {
        newbase=(ElemType *)realloc(L->elem,(L->listsize+LISTINCREMENT)*sizeof(ElemType));
        if(!newbase)
        exit(OVERFLOW);
        L->elem=newbase;
        L->listsize += LISTINCREMENT;
    }
    if(i<1||i>(L->length+1))
    return ERROR;
    q=&L->elem[i-1];
    for(p=&L->elem[L->length-1];p>=q;p--)
    *(p+1)=*p;
    *q=e;
    L->length++;
    return OK;
}
else return INFEASIBLE;
}

status ListDelete(SqList *L,int i,ElemType *e)
{
if(L->elem)
{
    ElemType *p,*q;
    if(i<1||i>L->length)
    return ERROR;
    p=&(L->elem[i-1]);
    *e=*p;
    q=L->elem+L->length-1;
    for(p++;p<=q;p++)
    *(p-1)=*p;
    L->length--;
    return OK;
}
else return INFEASIBLE;
}

status ListTrabverse(SqList L)
{
if(L.elem)
{
    int i=0;
    if(L.length==0)
    printf("线性表为空\n");
    while(i<L.length)
    {
        if(i<L.length-1)
        printf("%d ",L.elem[i]);
        else
        printf("%d",L.elem[i]);
        i++;
    }
    return OK;
}
else 
printf("线性表不存在\n");
return INFEASIBLE;
}


status  SaveList(SqList L,char FileName[])
{
    FILE *fp;
    int i=0;
    if(L.elem)
    {
       
        fp=fopen(FileName,"wb");
        if(!fp)
        {
            return ERROR;
        }
        for(i=0;i<L.length;i++)
        fprintf(fp,"%d ",L.elem[i]);
	   fclose(fp);
        return OK;
    }else return INFEASIBLE;
}


status  LoadList(SqList *L,char FileName[])
{
    FILE *fp;
    int i=0; 
	if(L->elem)
		return INFEASIBLE;
	else
	{
		L->elem=(ElemType *) malloc(sizeof(ElemType)*LIST_INIT_SIZE);
        L->length=0;
       	L->listsize= LIST_INIT_SIZE;
		if((fp=fopen(FileName,"rb"))!=NULL)
		{
			while((fscanf(fp,"%d ",&L->elem[i]))!=EOF)
            {
                L->length++;
                i++;
            } 
		}
		fclose(fp);
		return OK;
	}
}

status AddList(LISTS *Lists,char ListName[])
{
Lists->listsize=LIST_INIT_SIZE;
if(Lists->length<Lists->listsize)
{
    int i;
    for(i=0;ListName[i]!='\0';i++)
        Lists->elem[Lists->length-1].name[i]=ListName[i];
    Lists->length++;
    InitList(&Lists->elem[Lists->length-1].L);
}
getchar();
return OK;                
}

status RemoveList(LISTS *Lists,char ListName[])
{
int i,j,k,flag=0;
for(i=0;i<Lists->length;i++)
{
    for(j=0;Lists->elem[i].name[j]&&ListName[k];j++,k++)
    {
        flag=0;
        if(Lists->elem[i].name[j]!=ListName[k])
        {
            flag=1;
            break;  
        }
       
    }
    if(flag==0)
        break;
}
if(flag==0)
{
    for( ;i<Lists->length-1;i++)
    Lists->elem[i]=Lists->elem[i+1];
    Lists->elem[Lists->length-1].name[30]='0';
    Lists->elem[Lists->length-1].L.elem=NULL;
    Lists->elem[Lists->length-1].L.length=0;
    Lists->elem[Lists->length-1].L.listsize=1;
    free(Lists->elem[Lists->length-1].L.elem);
    Lists->length--;
    return OK;
}
else return ERROR;           
}

int LocateList(LISTS Lists,char ListName[])
{
int i,j,k,flag=0;
for(i=0;i<Lists.length;i++)
{
    for(j=0;Lists.elem[i].name[j]&&ListName[k];j++,k++)
    {
        flag=0;
        if(Lists.elem[i].name[j]!=ListName[k])
        {
            flag=1;
            break;  
        }
       
    }
    if(flag==0)
        break;
}
if(flag==0)
return i+1;
else return 0;
}


void mmm(LISTS *Lists)
{
 int fg=-1;int op=1;int i;
 char listname[30];
 printf("你想操作哪个线性表？");
 scanf("%s",listname);
 for(i=0;i<Lists->length;i++)
 {
     	if(!strcmp(Lists->elem[i].name,listname))
     	fg=i;
     }
     if(fg==-1)
     printf("线性表不存在\n");
     else
    {
    
    while(op){
    printf("      Menu for Linear Table On Sequence Structure \n");
    printf("-------------------------------------------------\n");
    printf("    	  1. InitList         7. LocateElem\n");
    printf("    	  2. DestroyList      8. PriorElem\n");
    printf("    	  3. ClearList        9. NextElem \n");
    printf("    	  4. ListEmpty        10. ListInsert\n");
    printf("    	  5. ListLength       11. ListDelete\n");
    printf("    	  6. GetElem          12. ListTrabverse\n");
    printf("          13.SaveList         14.LoadList\n");
    printf("    	  0. Exit\n");
    printf("-------------------------------------------------\n");
    printf("    请选择你的操作[0~12]:");
    scanf("%d",&op);
    int i=1,c,j,e=1,pre,next,n;
    LISTS Lists;
    char name[30];
    switch(op)
    {
        case 1:
        if(InitList(&Lists.elem[fg].L)==OK)
        printf("线性表创建成功！\n");
        else
        printf("线性表创建失败！\n");
        break;

        case 2:
        if(DestroyList(&Lists.elem[fg].L)==OK)
        printf("线性表销毁成功！\n");
        else
        printf("线性表销毁失败！\n");
        break;

        case 3:
        if(ClearList(&Lists.elem[fg].L)==OK)
        printf("线性表清空成功！\n");
        else
        printf("线性表清空失败！\n");
        break;

        case 4:
        if(ListEmpty(Lists.elem[fg].L)==OK)
        printf("线性表为空！\n");
        else
        printf("线性表不为空！\n");
        break;

        case 5:
    	j=ListLength(Lists.elem[fg].L);
    	if(j==INFEASIBLE)
    		printf("线性表不存在");
    	else 
    		printf("线性表的长度为%d", j);
        break;

        case 6:
        printf("你要查找第几个元素？\n");
    	scanf("%d",&i);
    	j=GetElem(Lists.elem[fg].L,i,&e);
    	if(j==OK) printf("第%d个元素是%d",i,j);
    	if(j==ERROR) printf("无法查找\n");
        break;

        case 7:
        printf("你要查找哪个元素？\n");
    	scanf("%d",&e);
    	j=LocateElem(Lists.elem[fg].L,e);
    	if(j==ERROR) printf("无法查找");
    	else printf("元素%d在第%d位",e,j);
        break;

        case 8:
        printf("你要获取谁的前驱？");
    	scanf("%d",&e);
    	if(e==Lists.elem[fg].L.elem[0])
    	printf("此元素无前驱");
    	else{
    		j=PriorElem(Lists.elem[fg].L,e,&pre);
    	if(j==ERROR) printf("无法获取");
    	if(j==OK) printf("元素%d的前驱是%d",e,pre);
    	}
        break;

        case 9:
        printf("你要获取谁的后继？");
    	scanf("%d",&e);
    	if(e==Lists.elem[fg].L.elem[Lists.elem[fg].L.length-1])
    	printf("此元素无后继");
    	else{
    			j=NextElem(Lists.elem[fg].L,e,&next);
    	if(j==ERROR) printf("无法获取");
    	if(j==OK) printf("元素%d的后继是%d",e,next);
    	}
        break;

        case 10:
        printf("请输入要插入的位置和元素");
        scanf("%d%d",&i,&e);
        j=ListInsert(&Lists.elem[fg].L,i,e);
        if(j==ERROR) printf("错误\n");
    	if(j==OK)
        {
            for(i=0;i<Lists.elem[fg].L.length;i++)
            printf("%d ",Lists.elem[fg].L.elem[i]);
        }
        break;

        case 11:
        printf("请输入要删除的元素");
    	scanf("%d",&i);
    	j=ListDelete(&Lists.elem[fg].L,i,&e);
    	if(j==ERROR) printf("错误\n");
    	if(j==OK)
        {
            for(i=0;i<Lists.elem[fg].L.length;i++)
            printf("%d ",Lists.elem[fg].L.elem[i]);
        }
        break;

        case 12:
    	j=ListTrabverse(Lists.elem[fg].L);
        break;

        case 13:
        printf("请输入要保存的文件名");
        scanf("%s",name);
        j=SaveList(Lists.elem[fg].L,name);
        break;

        case 14:
        printf("请输入要读入的文件名");
        scanf("%s",name);
        j=LoadList(&Lists.elem[fg].L,name);
        break;
    }
    }
    }
    }
    void ListsTraverse(LISTS Lists)
    {
    	int n;
    	 for(n=0;n<Lists.length;n++)
       		{
       			printf("%s ",Lists.elem[n].name);
       			ListTrabverse(Lists.elem[n].L);
            	putchar('\n');
       		}
    }