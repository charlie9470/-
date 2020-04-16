#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#define MAX_SIZE 35
char MAP[MAX_SIZE][MAX_SIZE][MAX_SIZE];
int available[MAX_SIZE][MAX_SIZE][MAX_SIZE];/*0 for available 1 for unavailable*/
int dist[MAX_SIZE][MAX_SIZE][MAX_SIZE];
int h[MAX_SIZE][MAX_SIZE][MAX_SIZE];
typedef struct{
    int l;
    int r;
    int c;
}Co_Or;

const Co_Or emp = {-1,-1,-1};

typedef struct{
    Co_Or q[30000];
    int front;
    int end;
}Queue;


Queue queue;
int i;

Queue init(Queue Q){
    /*printf("%d %d %d\n",emp.l,emp.r,emp.c);*/
     /*for(i=0;i<29999;i++){
        Q.q[i] = emp;
    }*/
     Q.front = -1;
    Q.end = -1;
    return Q;
}
Queue Push(Queue Q,Co_Or A){
    if(Q.end!=29999) Q.end+=1;
    else Q.end=0;
/*    if(Q.end==Q.front+1&&Q.q[Q.end].l!=emp.l){
        printf("queue is full\nplease think of another way.\n");
        printf("%d %d\n",Q.front,Q.end);
        printf("%d %d %d\n",Q.q[Q.end].l,Q.q[Q.end].r,Q.q[Q.end].c);
    }
    else{
*/        Q.q[Q.end] = A;
/*    }*/
    return Q;
}
Queue Pop(Queue Q){
    if(Q.front!=29999) Q.front+=1;
    else Q.front = 0;
/*    if(Q.q[Q.front].l==emp.l&&Q.q[Q.front].r==emp.r&&Q.q[Q.front].c==emp.c){
        printf("Queue is empty\n");
    }
    else{
        Q.q[Q.front] = emp;
/*    }*/
    return Q;
}
bool Isempty(Queue Q){
    if(Q.q[Q.front+1].l==emp.l) 
        return true;

    return false;    
}

Co_Or Front(Queue Q){
    return Q.q[Q.front+1];
}

int length(Queue Q){
    if(Isempty(Q)) return 0;
    return Q.end-Q.front;
}

void PrintQueue(Queue Q){
        for(i=Q.front+1;i<=Q.end;i++){
            printf("(%d,%d,%d,%d)",Q.q[i].l,Q.q[i].r,Q.q[i].c,dist[Q.q[i].l][Q.q[i].r][Q.q[i].c]);
            if(i!=Q.end) printf("->");
            else printf("\n");
        }
}


#ifndef ONLINE_JUDGE
   #include <conio.h>
#endif

int BFS(Co_Or S,int boudn_L,int boudn_R,int boudn_C,Co_Or E){
    double time_s,time_e;
    int count = 0;
    Co_Or tmp,tmp_u,tmp_d,tmp_l,tmp_r,tmp_f,tmp_b;
    queue = init(queue);
/*    printf("%d %d\n",queue.front,queue.end);*/
    queue = Push(queue,S);
    available[S.l][S.r][S.c] = 0;
/*    printf("%d %d\n",queue.front,queue.end);*/
    while(!Isempty(queue)){
        tmp = Front(queue);
        queue = Pop(queue);
        count++;
        printf("%d-th tmp: (%d,%d,%d,%d)\n",count,tmp.l,tmp.r,tmp.c,dist[tmp.l][tmp.r][tmp.c]);
        time_s = clock();
/*        printf("length before search = %d\n",length(queue));*/
        if(tmp.l+1<boudn_L&&available[tmp.l+1][tmp.r][tmp.c]){
                tmp_u.l = tmp.l+1;
                tmp_u.r = tmp.r;
                tmp_u.c = tmp.c;
                /*printf("up: (%d,%d,%d)\n",tmp_u.l,tmp_u.r,tmp_u.c);*/
                dist[tmp_u.l][tmp_u.r][tmp_u.c] = dist[tmp.l][tmp.r][tmp.c]+1;
                if(tmp_u.l==E.l&&tmp_u.r==E.r&&tmp_u.c==E.c) return dist[tmp_u.l][tmp_u.r][tmp_u.c];
                queue = Push(queue,tmp_u);
                available[tmp_u.l][tmp_u.r][tmp_u.c] = 0;
/*                printf("%d\n",length(queue));*/
        }
        if(tmp.l-1>=0&&available[tmp.l-1][tmp.r][tmp.c]){
                tmp_d.l = tmp.l-1;
                tmp_d.r = tmp.r;
                tmp_d.c = tmp.c;
                /*printf("down: (%d,%d,%d)\n",tmp_d.l,tmp_d.r,tmp_d.c);*/
                dist[tmp_d.l][tmp_d.r][tmp_d.c] = dist[tmp.l][tmp.r][tmp.c]+1;
                if(tmp_d.l==E.l&&tmp_d.r==E.r&&tmp_d.c==E.c) return dist[tmp_d.l][tmp_d.r][tmp_d.c];
                queue = Push(queue,tmp_d);
                available[tmp_d.l][tmp_d.r][tmp_d.c] = 0;
/*                printf("%d\n",length(queue));*/
        }
        if(tmp.r+1<boudn_R&&available[tmp.l][tmp.r+1][tmp.c]) {
                tmp_r.l = tmp.l;
                tmp_r.r = tmp.r+1;
                tmp_r.c = tmp.c;
                /*printf("right: (%d,%d,%d)\n",tmp_r.l,tmp_r.r,tmp_r.c);*/
                dist[tmp_r.l][tmp_r.r][tmp_r.c] = dist[tmp.l][tmp.r][tmp.c]+1;
                if(tmp_r.l==E.l&&tmp_r.r==E.r&&tmp_r.c==E.c) return dist[tmp_r.l][tmp_r.r][tmp_r.c];
                queue = Push(queue,tmp_r);
                available[tmp_r.l][tmp_r.r][tmp_r.c] = 0;
/*                printf("%d\n",length(queue));*/
        }
        if(tmp.r-1>=0&&available[tmp.l][tmp.r-1][tmp.c]) {
                tmp_l.l = tmp.l;
                tmp_l.r = tmp.r-1;
                tmp_l.c = tmp.c;
                /*printf("left: (%d,%d,%d)\n",tmp_l.l,tmp_l.r,tmp_l.c);*/
                dist[tmp_l.l][tmp_l.r][tmp_l.c] = dist[tmp.l][tmp.r][tmp.c]+1;
                if(tmp_l.l==E.l&&tmp_l.r==E.r&&tmp_l.c==E.c) return dist[tmp_l.l][tmp_l.r][tmp_l.c];
                queue = Push(queue,tmp_l);
                available[tmp_l.l][tmp_l.r][tmp_l.c] = 0;
/*                printf("%d\n",length(queue));*/
        }
        if(tmp.c+1<boudn_C&&available[tmp.l][tmp.r][tmp.c+1]){
                tmp_f.l = tmp.l;
                tmp_f.r = tmp.r;
                tmp_f.c = tmp.c+1;
                /*printf("front: (%d,%d,%d)\n",tmp_f.l,tmp_f.r,tmp_f.c);*/
                dist[tmp_f.l][tmp_f.r][tmp_f.c] = dist[tmp.l][tmp.r][tmp.c]+1;
                if(tmp_f.l==E.l&&tmp_f.r==E.r&&tmp_f.c==E.c) return dist[tmp_f.l][tmp_f.r][tmp_f.c];
                queue = Push(queue,tmp_f);
                available[tmp_f.l][tmp_f.r][tmp_f.c] = 0;
/*                printf("%d\n",length(queue));*/
        }
        if(tmp.c-1>=0&&available[tmp.l][tmp.r][tmp.c-1]){
                tmp_b.l = tmp.l;
                tmp_b.r = tmp.r;
                tmp_b.c = tmp.c-1;
                /*printf("back: (%d,%d,%d)\n",tmp_b.l,tmp_b.r,tmp_b.c);*/
                dist[tmp_b.l][tmp_b.r][tmp_b.c] = dist[tmp.l][tmp.r][tmp.c]+1;
                if(tmp_b.l==E.l&&tmp_b.r==E.r&&tmp_b.c==E.c) return dist[tmp_b.l][tmp_b.r][tmp_b.c];
                queue = Push(queue,tmp_b);
                available[tmp_b.l][tmp_b.r][tmp_b.c] = 0;
/*                printf("%d\n",length(queue));*/
        }
        time_e = clock();
/*        printf("Time used in one node: %f\n",(time_e-time_s)/CLOCKS_PER_SEC);*/
    }
    return 0;
}

int main(){
    int ans;
    Co_Or source;
    Co_Or goal;
    double START,FIN;
#ifndef ONLINE_JUDGE
    freopen("data.test.txt","r",stdin);
/*    freopen("output.txt", "w", stdout);*/
#endif
    int L=1,R=1,C=1;
    int i,j,k;
    START = clock();
    while(1){
        scanf("%d%d%d",&L,&R,&C);
/*        printf("%d %d %d\n",L,R,C);*/
        if(L==0&&R==0&&C==0) break;
/*        for(i=0;i<L;i++){
            for(j=0;j<R;j++){
                for(k=0;k<C;k++){
                    MAP[i][j][k] = '#';
                    available[i][j][k] = 1;
                    dist[i][j][k] = -1;
                }
            }
        }
*/        for(i=0;i<L;i++){
            for(j=0;j<R;j++){
                for(k=0;k<C;k++){
                    scanf(" %c",&MAP[i][j][k]);
                    dist[i][j][k] = -1;
                    if(MAP[i][j][k]=='S') {
                        source.l = i;
                        source.r = j;
                        source.c = k;
                        dist[i][j][k] = 0;
                        available[i][j][k] = 1;
                    }
                    else if(MAP[i][j][k]=='E'){
                        goal.l = i;
                        goal.r = j;
                        goal.c = k;
                        available[i][j][k] = 1;
                    }
                    else if(MAP[i][j][k]=='#') available[i][j][k] = 0;
                    else available[i][j][k] = 1;
                }
            }
        }
/*        printf("source: %d %d %d\n",source.l,source.r,source.c);
        for(i=0;i<L;i++){
            for(j=0;j<R;j++){
                for(k=0;k<C;k++){
                    printf("%d",available[i][j][k]);
                    if(k==C-1) printf("\n");
                    else printf(" ");
                }
                if(j==R-1) printf("\n");
            }
        }
        for(i=0;i<L;i++){
            for(j=0;j<R;j++){
                for(k=0;k<C;k++){
                    printf("%d",dist[i][j][k]);
                    if(k==C-1) printf("\n");
                    else printf(" ");
                }
                if(j==R-1) printf("\n");
            }
        }
*/
        ans = BFS(source,L,R,C,goal);
/*        for(i=0;i<L;i++){
            for(j=0;j<R;j++){
                for(k=0;k<C;k++){
                    printf("%d",available[i][j][k]);
                    if(k==C-1) printf("\n");
                    else printf(" ");
                }
                if(j==R-1) printf("\n");
            }
        }

        for(i=0;i<L;i++){
            for(j=0;j<R;j++){
                for(k=0;k<C;k++){
                    printf("%d",dist[i][j][k]);
                    if(k==C-1) printf("\n");
                    else printf(" ");
                }
                if(j==R-1) printf("\n");
            }
        }*/
        if(ans>0) printf("Escaped in %d minute(s).\n",ans);
        else printf("Trapped!\n");
        /* printf("%d %d %d\n",source.l,source.r,source.c);*/
    }
    FIN = clock();
    printf("CLOCKS_PER_SEC: %d\n",CLOCKS_PER_SEC);
    printf("time:%f\n",(FIN-START)/CLOCKS_PER_SEC);
    system("pause");
    return 0;
}
