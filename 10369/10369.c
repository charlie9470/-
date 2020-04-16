#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#define MAX_SIZE 20001

#ifndef ONLINE_JUDGE
    #include <conio.h>
#endif
typedef struct pq_node{
    int index;
    int late;
}PQN;
int dist[MAX_SIZE];
int g[MAX_SIZE][MAX_SIZE];
bool visited[MAX_SIZE];
typedef struct Heap{
    struct pq_node pq[20000];
    int size;
}BH;
PQN Min_Node(PQN a,PQN b){
    return b.late<a.late?b:a;
}
BH Insert(BH B_H,PQN A){
    int i;
    PQN temp;
    int tmp;
    B_H.size++;
    B_H.pq[B_H.size] = A;
    for(i=B_H.size;i>1;){
        if(B_H.pq[i].late>=B_H.pq[i/2].late) {/*a heap*/
            break;
        }
        else{
            temp = B_H.pq[i];
            B_H.pq[i] = B_H.pq[i/2];
            B_H.pq[i/2] = temp;/*check upward*/
            i/=2;
        }
    }
    return B_H;
}
BH heapify(BH B_H,int index){
    int i;
    int tmp;
    PQN temp;
    PQN min;
    for(i=index;i*2+1<=B_H.size;){
        min = Min_Node(Min_Node(B_H.pq[i],B_H.pq[2*i]),B_H.pq[2*i+1]);
        if(min.index==B_H.pq[i].index&&min.late==B_H.pq[i].late){
            break;/*already BH*/
        }
        else if(min.index==B_H.pq[2*i].index&&min.late==B_H.pq[2*i].late){
            /*swap with left subtree check leftsubtree*/
            temp = B_H.pq[i];
            B_H.pq[i] = B_H.pq[2*i];
            B_H.pq[2*i] = temp;
            i = 2*i;
        }
        else if(min.index==B_H.pq[2*i+1].index&&min.late==B_H.pq[2*i+1].late){
            /*swap with right subtree check rightsubtree*/
            temp = B_H.pq[i];
            B_H.pq[i] = B_H.pq[2*i+1];
            B_H.pq[2*i+1] = temp;
            i = 2*i+1;
        }
    }
    if(i*2==B_H.size){
        if(B_H.pq[i].late>B_H.pq[2*i].late){
            temp = B_H.pq[i];
            B_H.pq[i] = B_H.pq[2*i];
            B_H.pq[2*i] = temp;
        }
    }
    return B_H;
}
BH Extract_Min(BH B_H){
    if(B_H.size==0) return B_H;/*empty*/
    B_H.pq[1] = B_H.pq[B_H.size];
    B_H.size-=1;
    if(B_H.size>1) B_H = heapify(B_H,1);
    return B_H;
}
int Get_Min(BH B_H){
    if(B_H.size==0) return -1;
    return B_H.pq[1].index;
}
int FindPosition(BH B_H,int index){
    int i;
    for(i=1;i<=B_H.size;i++){
        if(B_H.pq[i].index==index) return i;
    }
    return -1;
}

BH Decrease_Key(BH B_H,int index,int new_L){
    int i;
    PQN temp;
    int tmp;
    int pos = FindPosition(B_H,index);
    B_H.pq[pos].late = new_L;
    for(i=pos;i>1;){
        if(B_H.pq[i].late>=B_H.pq[i/2].late) break;/*a heap*/
        else{
            temp = B_H.pq[i];
            B_H.pq[i] = B_H.pq[i/2];
            B_H.pq[i/2] = temp;/*check upward*/
            i/=2;
        }
    }
    return B_H;
}

int Dijkstra(BH B_H,int n,int S,int T){
    int i;
    PQN temp;
    int next;
    temp.index = S;
    temp.late = 0;
    B_H.size = 0;
    B_H = Insert(B_H,temp);
    while(1){
        if(visited[T]){
            return dist[T];
        }
        next = Get_Min(B_H);
/*        printf("next: %d,dist[next]: %d\n",next,dist[next]);*/
        B_H = Extract_Min(B_H);
/*            printf("size: %d\n",B_H.size);*/
        if(next==-1) {return -1;}
        for(i=0;i<n;i++){
            if(visited[next]) break;
            if(i==next) continue;
            if(dist[i]>dist[next]+g[next][i]){
                dist[i] = dist[next]+g[next][i];
/*                printf("i: %d,dist[i]: %d\n",i,dist[i]);*/
                temp.index = i;
                temp.late = dist[i];
                B_H = Insert(B_H,temp);
/*                printf("(%d,%d)inserted\n",i,dist[i]);*/
            }
        }
        visited[next] = true;
    }
}

int main(){
    int N,n,m,S,T;
    int i,j,k;
    int a,b,laten;
    int ans;
    BH B_H;
    #ifndef ONLINE_JUDGE
        freopen("data.test.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    scanf("%d",&N);
/*    printf("N: %d\n",N);*/
    for(i=0;i<N;i++){
        scanf("%d%d%d%d",&n,&m,&S,&T);
/*        printf("n:%d,m:%d,S:%d,T:%d\n",n,m,S,T);*/
        B_H.size = 0;
        for(j=0;j<n;j++){
            visited[j] = false;
            dist[j] = 100000;
            for(k=0;k<n;k++){
                if(j==k) g[j][k] = 0;
                else g[j][k] = 100000;
            }
        }
        dist[S] = 0;
        for(j=0;j<m;j++){
            scanf("%d%d%d",&a,&b,&laten);
            if(laten<g[a][b]){
                g[a][b] = laten;
                g[b][a] = laten;
            }
        }
        ans = Dijkstra(B_H,n,S,T);
        printf("Case #%d: ",i+1);
        if(ans==-1) printf("unreachable\n");
        else printf("%d\n",ans);
    }
    return 0;
}
