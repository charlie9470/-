#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#define MAX_SIZE 100
int ori[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE];
int visited_ori[MAX_SIZE];
char ans[MAX_SIZE][MAX_SIZE];
void DFS(int size,int cur,int cut){
    if(cut==0) return;
    int i;
    for(i=0;i<size;i++){
        if(i==cut) continue;
        if(ori[cur][i]==1&&visited[i]==0){
            visited[i] = 1;
            DFS(size,i,cut);
        }
    }
}
void PrintAns(int a,int size){
    int i,j;
    printf("Case %d:\n",a);
    printf("+");
    for(i=0;i<size*2-1;i++){
        printf("-");
    }
    printf("+\n");
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            printf("|%c",ans[i][j]);
            if(j==size-1) printf("|\n");
        }
        printf("+");
        for(j=0;j<size*2-1;j++){
            printf("-");
        }
        printf("+\n");
    }
}

int main(){
    int i,j,k;
    #ifndef ONLINE_JUDGE
        freopen("data.test.txt","r",stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int times,size;
    scanf("%d",&times);
    for(i=0;i<times;i++){
        scanf("%d",&size);
        for(j=0;j<size;j++){
            for(k=0;k<size;k++){
                scanf(" %d",&ori[j][k]);
            }
        }
        for(k=1;k<size;k++){
            visited[k] = 0;
        }
        visited[0] = 1;
        DFS(size,0,size);
        for(j=0;j<size;j++) visited_ori[j] = visited[j];
        for(j=0;j<size;j++){
            for(k=1;k<size;k++){
                visited[k] = 0;
            }
            DFS(size,0,j);
            for(k=0;k<size;k++){
                if(visited_ori[k]==visited[k]){
                    ans[j][k] = 'N';
                }
                else{
                    ans[j][k] = 'Y';
                }
            }
        }
        ans[0][0] = 'Y';
        PrintAns(i+1,size);
    }


}
