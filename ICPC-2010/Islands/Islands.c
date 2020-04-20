#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct Island{
    int x;
    int y;
}IS;

double f[105][105];
IS graph[105];

int main(){
    #ifndef ONLINE_JUDGE
        freopen("data.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif 
    int n,b1,b2;
    int i,j;
    int ans;
    int x,y;
    int count = 0;
    while(1){
        scanf(" %d %d %d",&n,&b1,&b2);
        for(i=0;i<n;i++){
            scanf(" %d %d",&x,&y);
            graph[i].x = x;
            graph[i].y = y;
        }
        /* printf("%d %d %d\n",m,n,w);*/
        ans = DP();
        if(n==0&&b1==0&&b2==0){
            break;
        }
        printf("Case %d: %d\n",++count,ans);
        PRINTPATH();
    }
    return 0;
}
