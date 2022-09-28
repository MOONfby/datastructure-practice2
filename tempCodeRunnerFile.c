FILE *fp;
    int i,m,arc,VR[100]={0},flag[50][50]={0};
    ArcNode *p;
    m=0,arc=0;
    if((fp=fopen(FileName,"wb"))==NULL)
        return ERROR;
    for(i=0;i<G.vexnum;i++){
        fprintf(fp,"%d %s ",G.vertices[i].data.key,G.vertices[i].data.others);
    }
    fprintf(fp,"-1 nil ");
    for(i=0;i<G.vexnum;i++)
    {
        p=G.vertices[i].firstarc;
        while(p)
        {
            if(!flag[G.vertices[i].data.key][G.vertices[p->adjvex].data.key]){
                VR[m++]=G.vertices[i].data.key;
                VR[m++]=G.vertices[p->adjvex].data.key;
                arc=arc+2;
                flag[G.vertices[i].data.key][G.vertices[p->adjvex].data.key]=1;
                flag[G.vertices[p->adjvex].data.key][G.vertices[i].data.key]=1;
            }
            p=p->nextarc;
        }
    }
    for(i=0;i<arc;i++)
    {
        fprintf(fp,"%d ",VR[i]);
    }
    fprintf(fp,"-1 -1 ");
    fclose(fp);
    return OK;