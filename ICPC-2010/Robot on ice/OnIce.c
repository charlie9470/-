#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
int move[4][2] = {
    {1,0},
    {0,1},
    {-1,0},
    {0,-1}
};
typedef struct pos{
    int x;
    int y;
}P;

int size;
int num;
int ans;
P cp1,cp2,cp3;
bool grid[10][10];
bool T_grid[10][10];
bool _1passed;
bool _2passed;
bool _3passed;

void T(int m,int n,int x,int y){
    int i;
    P next;
    for(i=0;i<4;i++){
        next.x = x+move[i][0];
        next.y = y+move[i][1];
        if(T_grid[next.x][next.y]==0){
            T(m,n,next.x,next.y);
        }
        T_grid[x][y] = 1;
    }
}

void DFS(int m,int n,P pos,int S_count/*step count*/){
    num++;
    int i,j;
    /* printf("(%d,%d,%d)\n",pos.x,pos.y,S_count);*/
/*    _1passed = false;
    _2passed = false;
    _3passed = false;
    if(S_count>=size/4) _1passed = true;
    if(S_count>=size/2) _2passed = true;
    if(S_count>=size*3/4) _3passed = true;*/
    for(i=0;i<10;i++){
        for(j=0;j<10;j++){
            T_grid[i][j] = grid[i][j];
        }
    }
    T(m,n,pos.x,pos.y);
    for(i=1;i<=m;i++){
        for(j=1;j<=n;j++){
            if(T_grid[i][j]==0) return;
        }
    }
    if(S_count<size/4){
        if(abs(cp1.x-pos.x)+abs(cp1.y-pos.y)>size/4-S_count) return;
    }
    else if(S_count<size/2){
        if(abs(cp2.x-pos.x)+abs(cp2.y-pos.y)>size/2-S_count) return;
    }
    else if(S_count<size*3/4){
        if(abs(cp3.x-pos.x)+abs(cp3.y-pos.y)>size*3/4-S_count) return;
    }
    else{
        if(abs(1-pos.x)+abs(2-pos.y)>size-S_count) return;
    }
    P next;
    grid[pos.x][pos.y] = 1;
    if(_2passed){
        if(grid[m][1]==false){
            grid[pos.x][pos.y] = 0;
            return;
        }
    }
    if(_3passed){
        if(grid[m][1]==false&&grid[m][n]==false){
            grid[pos.x][pos.y] = 0;
            return;
        }
    }
    if(S_count==size/4){
        if(pos.x!=cp1.x||pos.y!=cp1.y){
            grid[pos.x][pos.y] = 0;
            /* printf("failed and returned from (%d,%d)\n",pos.x,pos.y);*/
            return ;
        }
        /* else printf("Pass through 1st CP\n");*/
    }
    if(S_count==size/2){
        if(pos.x!=cp2.x||pos.y!=cp2.y){
            grid[pos.x][pos.y] = 0;
            /* printf("failed and returned from (%d,%d)\n",pos.x,pos.y);*/
            return ;
        }
        /* else printf("Pass through 2nd CP\n");*/
    }
    if(S_count==size*3/4){
        if(pos.x!=cp3.x||pos.y!=cp3.y){
            grid[pos.x][pos.y] = 0;
            /* printf("failed and returned from (%d,%d)\n",pos.x,pos.y);*/
            return ;
        }
        /* else printf("Pass through 3rd CP\n");*/
    }
    if(pos.x==1&&pos.y==2) {
        if(S_count==size){
            ans++;
        }
        grid[pos.x][pos.y] = 0;
        return ;
    }
    if(pos.x==cp1.x&&pos.y==cp1.y){
        if(S_count!=size/4){
            grid[pos.x][pos.y] = 0;
            /* printf("failed and returned from (%d,%d)\n",pos.x,pos.y);*/
            return ;
        }
    }
    if(pos.x==cp2.x&&pos.y==cp2.y){
        if(S_count!=size/2){
            grid[pos.x][pos.y] = 0;
            /* printf("failed and returned from (%d,%d)\n",pos.x,pos.y);*/
            return ;
        }
    }
    if(pos.x==cp3.x&&pos.y==cp3.y){
        if(S_count!=size*3/4){
            grid[pos.x][pos.y] = 0;
            /* printf("failed and returned from (%d,%d)\n",pos.x,pos.y);*/
            return ;
        }
    }
    for(i=0;i<4;i++){
        next.x = pos.x+move[i][0];
        next.y = pos.y+move[i][1];
        if(!grid[next.x][next.y]){
            DFS(m,n,next,S_count+1);
        }
    }
    grid[pos.x][pos.y] = 0;
    /* printf("returned to (%d,%d), paths through: %d\n",pos.x,pos.y,ans);*/
    return ;
}
int main(){
    #ifndef ONLINE_JUDGE
        freopen("data.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    int m,n;
    int i,j;
    P start;
    start.x = 1;
    start.y = 1;
    int count = 0;
    while(1){
        scanf(" %d %d",&m,&n);
        /* printf("%d %d %d\n",m,n,w);*/
        if(m==0&&n==0){
            break;
        }
        num = 0;
        ans = 0;
        for(i=0;i<10;i++){
            for(j=0;j<10;j++){
                if(i==0||j==0||i>m||j>n) grid[i][j] = 1;
                else grid[i][j] = 0;
            }
        }
        _1passed = false;
        _2passed = false;
        _3passed = false;
        scanf(" %d %d",&cp1.x,&cp1.y);
        scanf(" %d %d",&cp2.x,&cp2.y);
        scanf(" %d %d",&cp3.x,&cp3.y);
        cp1.x++;
        cp1.y++;
        cp2.x++;
        cp2.y++;
        cp3.x++;
        cp3.y++;
        size = m*n;
        if(abs(cp1.x-1)+abs(cp1.y-1)>size/4-1) ans = 0;
        if(abs(cp1.x-cp2.x)+abs(cp1.y-cp2.y)>size/4-1) ans = 0;
        if(abs(cp2.x-cp3.x)+abs(cp2.y-cp3.y)>size/4-1) ans = 0;
        if(abs(1-cp2.x)+abs(2-cp2.y)>size/4-1) ans = 0;
        DFS(m,n,start,1);
        /*printf("%d\n",num);*/
        printf("Case %d: %d\n",++count,ans);
        /*printf("----------------------------------------------------------\n");*/
    }
    return 0;
}
