#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

typedef struct Island{
    int x;
    int y;
}IS;

double f[105][105];
IS graph[105];

float dist(IS I1,IS I2){
    return sqrt((I1.x-I2.x)*(I1.x-I2.x) + (I1.y-I2.y)*(I1.y-I2.y));
}
int Max(int i,int j){
    return i>j?i:j;
}
float Min(float a,float b){
    return a>b?b:a;
}
void PRINTFDP(int n){
    int i,j;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(f[i][j]>=3000) printf("X ");
            else printf("%.2f ",f[i][j]);
        }
        printf("\n");
    }
}
float DP(int n,int b1,int b2){
    int i,j,k;
    float min;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            min = 3000.0;
            if(i==j||j==b1||i==b2||(j<b2&&b2<=i)||(i<b1&&b1<=j)) f[i][j] = 3000;
            else if((i==0&&j==1)||(i==1&&j==0)) f[i][j] = dist(graph[i],graph[j]);
            else if(Max(i,j)<b1){
                if(j==i-1){
                    for(k=0;k<j;k++){
                        min = Min(min,f[i-1][k]+dist(graph[k],graph[i]));
                    }
                    min = Min(min,f[i-2][j]+dist(graph[i],graph[i-2]));
                    f[i][j] = min;
                }
                else if(i==j-1){
                    for(k=0;k<i;k++){
                        min = Min(min,f[k][j-1]+dist(graph[k],graph[j]));
                    }
                    if(f[i-2][j]!=-1){
                        min = Min(min,f[i][j-2]+dist(graph[j],graph[j-2]));
                    }
                    f[i][j] = min;
                }
                else {
                    if(i>j){
                        f[i][j] = f[i-1][j]+dist(graph[i],graph[i-1]);
                    }
                    else{
                        f[i][j] = f[i][j-1]+dist(graph[j],graph[j-1]);
                    }
                }
            }
            else if(i==b1){
                if(i<j){
                    if(j==b1+1){
                        f[i][j] = f[i][j-2]+dist(graph[j],graph[j-2]);
                    }
                    else{
                        f[i][j] = f[i][j-1]+dist(graph[j],graph[j-1]);
                    }
                }
                else{
                    f[i][j] = f[i-1][j]+dist(graph[i],graph[i-1]);
                }
            }
            else if(j==b2){
                if(i>j){
                    if(i==b2+1){
                        f[i][j] = f[i-2][j]+dist(graph[i],graph[i-2]);
                    }
                    else{
                        f[i][j] = f[i-1][j]+dist(graph[i],graph[i-1]);
                    }
                }
                else{
                    f[i][j] = f[i][j-1]+dist(graph[j],graph[j-1]);
                }
            }
            else{
                if(i>j){
                    if(i-2>=0&&f[i-2][j]==3000){
                        min = Min(min,f[i-2][j]+dist(graph[i-2],graph[i]));
                    }
                    min = Min(min,f[i-1][j]+dist(graph[i-1],graph[i]));
                }
                else{
                    if(j-2>=0&&f[i][j-2]==3000){
                        min = Min(min,f[i][j-2]+dist(graph[j-2],graph[j]));
                    }
                    min = Min(min,f[i][j-1]+dist(graph[j-1],graph[j]));
                }
                f[i][j] = min;
            }
        }
    }
}

int main(){
    #ifndef ONLINE_JUDGE
        freopen("data.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    int n,b1,b2;
    int i,j;
    float ans;
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
        if(n==0&&b1==0&&b2==0){
            break;
        }
        ans = DP(n,b1,b2);
        PRINTFDP(n);
        printf("Case %d: %d\n",++count,ans);
/*        PRINTPATH();*/
    }
    return 0;
}
