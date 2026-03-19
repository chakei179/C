#include <iostream>
#include <stdio.h>
#define N 5

typedef struct tu{
    int nodes [N];
    int edge[N][N];
    int dingdianshu,bianshu;
}mgraph;

int creatg(mgraph &g){
    int i,j;
    int v1,v2;
    scanf("%d%d",&g.dingdianshu,&g.bianshu);
    for ( i = 0; i < g.dingdianshu; i++)
    {
        g.nodes[i]=i;
    }
    for ( i = 0; i < g.dingdianshu; i++)
    {
        for ( j = 0; j < g.dingdianshu; j++)
        {
            g.edge[i][j]=0;
        }
        
    }
    
    for ( i = 0; i < g.bianshu; i++)
    {
        scanf("%d%d",&v1,&v2);
        g.edge[v1][v2]=1;
        g.edge[v2][v1]=1;
    }
    
    
    return 0;
}

int  DFS(mgraph &g,int i,int visit[]){
    int j,k;
    printf("%d ",g.nodes[i]);
    visit[i]=1;
    for ( j = 0; j < g.dingdianshu; j++)
    {
        if (!visit[j]&&g.edge[i][j])
        {
            DFS(g,j,visit);
        }
        
    }
    return 0;
}





int main(){
    mgraph g={{0,1,2,3,4},
{
    {0,1,0,1,0},
    {1,0,1,0,1},
    {0,1,0,1,1},
    {1,0,1,0,0},
    {0,1,1,0,0}
},
5,6
    };

// mgraph g;
// creatg(g);
int visit[N];
for (int i = 0; i < g.dingdianshu; i++)
{
    visit[i]=0;
}

for (int i = 0; i < g.dingdianshu; i++)
{
    if (!visit[i])
    {
        DFS(g,i,visit);
    }
  
}


return 0 ;
}


