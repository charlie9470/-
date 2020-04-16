#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#define MAX_SIZE 35
char MAP[MAX_SIZE][MAX_SIZE][MAX_SIZE];
bool available[MAX_SIZE][MAX_SIZE][MAX_SIZE];/*1 for available 0 for unavailable*/
int dist[MAX_SIZE][MAX_SIZE][MAX_SIZE];
int h[MAX_SIZE][MAX_SIZE][MAX_SIZE];

typedef struct{
    int l;
    int r;
    int c;/*coordinates*/
    float f;/* f(n) = g(n) + h(n)*/
}Co_Or;

const Co_Or emp = {-1,-1,-1,-1.0};

typedef struct{
    Co_Or q[30000];
    int size;
}Pri_Queue;

Pri_Queue pq;
int i;

Pri_Queue heapify(Pri_Queue pq,int index){
    Co_Or tmp;
    while(2*index+2<pq.size){
        if(pq.q[index].f<=pq.q[2*index+1].f&&pq.q[index].f<=pq.q[2*index+2].f){/*already a binary heap*/
            break;
        }
        else if(pq.q[2*index+1].f<=pq.q[index].f&&pq.q[2*index+1].f<=pq.q[2*index+2].f){/*heapify left subtree*/
            tmp = pq.q[2*index+1];
            pq.q[2*index+1] = pq.q[index];
            pq.q[index] = tmp;
            /*printf("index:%d\n",index*2+1);*/
            index=index*2+1;
            /*printf("index:%d %d\n",index,index*2+1);*/
        }
        else if(pq.q[2*index+2].f<=pq.q[index].f&&pq.q[2*index+2].f<=pq.q[2*index+1].f){/*heapify right subtree*/
            tmp = pq.q[2*index+2];
            pq.q[2*index+2] = pq.q[index];
            pq.q[index] = tmp;
            /*printf("index:%d\n",index*2+2);*/
            index=index*2+2;
            /*printf("index:%d\n",index);*/
        }
        else{
            printf("(%.2f,%.2f,%.2f)\n",pq.q[index].f,pq.q[2*index+1].f,pq.q[2*index+2].f);
        }
    }
    if(2*index+1<pq.size){
        if(pq.q[2*index+1].f<pq.q[index].f){
            tmp = pq.q[2*index+1];
            pq.q[2*index+1] = pq.q[index];
            pq.q[index] = tmp;
        }
    }
    return pq;
}
Pri_Queue BuildHeap(Pri_Queue pq){
    for(i = pq.size/2;i>=0;i--){
        pq = heapify(pq,i);
    }
    return pq;
}

Pri_Queue init(Pri_Queue Q){
    for(i=0;i<29999;i++){
        Q.q[i] = emp;
    }
    Q.size = 0;
    return Q;
}
Pri_Queue Insert(Pri_Queue Q,Co_Or A){
    Co_Or tmp;
    int index;
    Q.q[Q.size] = A;
    index = Q.size;
    Q.size+=1;
    while(1){
        if((index-1)/2>=0){
            if(Q.q[(index-1)/2].f<=Q.q[index].f){
                return Q;
            }
            else{
                tmp = Q.q[(index-1)/2];
                Q.q[(index-1)/2] = Q.q[index];
                Q.q[index] = tmp;
                index = (index-1)/2;
            }            
        }
        else return Q;
    }
}
bool Isempty(Pri_Queue Q){
    if(Q.size==0){
        return true;
    }
    return false;
}
Pri_Queue ExtractMin(Pri_Queue Q){
    if(!Isempty(Q)){
        Q.size-=1;
        Q.q[0] = Q.q[Q.size];
        Q.q[Q.size] = emp;
        Q = heapify(Q,0);
        return Q;
    }
    else printf("PQ is empty!\n");
}
Co_Or GetMin(Pri_Queue Q){
    if(!Isempty(Q)) return Q.q[0];
    else printf("PQ is empty!\n");
}

int max(int a,int b){
    return a>b?a:b;
}

int max_three(int a,int b,int c){
    return a>max(b,c)?a:max(b,c);
}

int Cheby_dist(Co_Or A,Co_Or B){
    return max_three(abs(A.l-B.l),abs(A.r-B.r),abs(A.c-B.c));
}

#ifndef ONLINE_JUDGE
   #include <conio.h>
#endif


int Astar(Co_Or S,int boudn_L,int boudn_R,int boudn_C,Co_Or E){
    Co_Or tmp,tmp_u,tmp_d,tmp_r,tmp_l,tmp_f,tmp_b;
    int count=0;
    pq = init(pq);
    pq = Insert(pq,S);
    available[S.l][S.r][S.c] = 0;
/*    printf("S:(%d,%d,%d,%.2f)\n",S.l,S.r,S.c,S.f);
    printf("pq.top:(%d,%d,%d,%.2f)\n",pq.q[0].l,pq.q[0].r,pq.q[0].c,pq.q[0].f);
*/    while(!Isempty(pq)){
        count++;
        tmp = GetMin(pq);
        pq = ExtractMin(pq);
        printf("%d-th tmp:(%d,%d,%d,%.2f)\n",count,tmp.l,tmp.r,tmp.c,tmp.f);
/*        printf("size: %d\n",pq.size);
        for(i=0;i<pq.size;i++){
            printf("(%d,%d,%d,%.2f)",pq.q[i].l,pq.q[i].r,pq.q[i].c,pq.q[i].f);
            if(i==pq.size-1) printf("\n");
            else printf("->");
        }*/
        if(tmp.l+1<=boudn_L){
            if(available[tmp.l+1][tmp.r][tmp.c]){
                tmp_u.l = tmp.l+1;
                tmp_u.r = tmp.r;
                tmp_u.c = tmp.c;
                dist[tmp_u.l][tmp_u.r][tmp_u.c] = dist[tmp.l][tmp.r][tmp.c]+1;
                if(tmp_u.l==E.l&&tmp_u.r==E.r&&tmp_u.c==E.c){
                    return dist[tmp_u.l][tmp_u.r][tmp_u.c];
                }
                tmp_u.f = Cheby_dist(tmp_u,S) + Cheby_dist(tmp_u,E);
/*                tmp_u.f = dist[tmp_u.l][tmp_u.r][tmp_u.c] + h[tmp_u.l][tmp_u.r][tmp_u.c];
/*                tmp_u.f = sqrt((tmp_u.l-S.l)*(tmp_u.l-S.l)+(tmp_u.r-S.r)*(tmp_u.r-S.r)+(tmp_u.c-S.c)*(tmp_u.c-S.c)) + sqrt((tmp_u.l-E.l)*(tmp_u.l-E.l)+(tmp_u.r-E.r)*(tmp_u.r-E.r)+(tmp_u.c-E.c)*(tmp_u.c-E.c));*/
                /*printf("up: (%d,%d,%d,%.2f)\n",tmp_u.l,tmp_u.r,tmp_u.c,tmp_u.f);*/

                pq = Insert(pq,tmp_u);
                available[tmp_u.l][tmp_u.r][tmp_u.c] = 0;
                /*printf("size: %d\n",pq.size);*/
            }
        }
        if(tmp.l-1>=0){
            if(available[tmp.l-1][tmp.r][tmp.c]){
                tmp_d.l = tmp.l-1;
                tmp_d.r = tmp.r;
                tmp_d.c = tmp.c;
                dist[tmp_d.l][tmp_d.r][tmp_d.c] = dist[tmp.l][tmp.r][tmp.c]+1;
                if(tmp_d.l==E.l&&tmp_d.r==E.r&&tmp_d.c==E.c){
                    return dist[tmp_d.l][tmp_d.r][tmp_d.c];
                }
                tmp_d.f = Cheby_dist(tmp_d,S) + Cheby_dist(tmp_d,E);
/*                tmp_d.f = dist[tmp_d.l][tmp_d.r][tmp_d.c] + h[tmp_d.l][tmp_d.r][tmp_d.c];
/*                tmp_d.f = sqrt((tmp_d.l-S.l)*(tmp_d.l-S.l)+(tmp_d.r-S.r)*(tmp_d.r-S.r)+(tmp_d.c-S.c)*(tmp_d.c-S.c)) + sqrt((tmp_d.l-E.l)*(tmp_d.l-E.l)+(tmp_d.r-E.r)*(tmp_d.r-E.r)+(tmp_d.c-E.c)*(tmp_d.c-E.c));*/
                /*printf("down: (%d,%d,%d,%.2f)\n",tmp_d.l,tmp_d.r,tmp_d.c,tmp_d.f);*/
                pq = Insert(pq,tmp_d);
                available[tmp_d.l][tmp_d.r][tmp_d.c] = 0;
                /*printf("%d\n",pq.size);*/
            }
        }
        if(tmp.r+1<=boudn_R) {
            if(available[tmp.l][tmp.r+1][tmp.c]){
                tmp_r.l = tmp.l;
                tmp_r.r = tmp.r+1;
                tmp_r.c = tmp.c;
                dist[tmp_r.l][tmp_r.r][tmp_r.c] = dist[tmp.l][tmp.r][tmp.c]+1;
                if(tmp_r.l==E.l&&tmp_r.r==E.r&&tmp_r.c==E.c){
                    return dist[tmp_r.l][tmp_r.r][tmp_r.c];
                }
                tmp_r.f = Cheby_dist(tmp_r,S) + Cheby_dist(tmp_r,E);
/*                tmp_r.f = dist[tmp_r.l][tmp_r.r][tmp_r.c] + h[tmp_r.l][tmp_r.r][tmp_r.c];
/*                tmp_r.f = sqrt((tmp_r.l-S.l)*(tmp_r.l-S.l)+(tmp_r.r-S.r)*(tmp_r.r-S.r)+(tmp_r.c-S.c)*(tmp_r.c-S.c)) + sqrt((tmp_r.l-E.l)*(tmp_r.l-E.l)+(tmp_r.r-E.r)*(tmp_r.r-E.r)+(tmp_r.c-E.c)*(tmp_r.c-E.c));*/
                /*printf("right: (%d,%d,%d,%.2f)\n",tmp_r.l,tmp_r.r,tmp_r.c,tmp_r.f);*/
                pq = Insert(pq,tmp_r);
                available[tmp_r.l][tmp_r.r][tmp_r.c] = 0;
                /*printf("%d\n",pq.size);*/
            }
        }
        if(tmp.r-1>=0) {
            if(available[tmp.l][tmp.r-1][tmp.c]){
                tmp_l.l = tmp.l;
                tmp_l.r = tmp.r-1;
                tmp_l.c = tmp.c;
                dist[tmp_l.l][tmp_l.r][tmp_l.c] = dist[tmp.l][tmp.r][tmp.c]+1;
                if(tmp_l.l==E.l&&tmp_l.r==E.r&&tmp_l.c==E.c){
                    return dist[tmp_l.l][tmp_l.r][tmp_l.c];
                }
                tmp_l.f = Cheby_dist(tmp_l,S) + Cheby_dist(tmp_l,E);
/*                tmp_l.f = dist[tmp_l.l][tmp_l.r][tmp_l.c] + h[tmp_l.l][tmp_l.r][tmp_l.c];
/*                tmp_l.f = sqrt((tmp_l.l-S.l)*(tmp_l.l-S.l)+(tmp_l.r-S.r)*(tmp_l.r-S.r)+(tmp_l.c-S.c)*(tmp_l.c-S.c)) + sqrt((tmp_l.l-E.l)*(tmp_l.l-E.l)+(tmp_l.r-E.r)*(tmp_l.r-E.r)+(tmp_l.c-E.c)*(tmp_l.c-E.c));*/
                /*printf("left: (%d,%d,%d,%.2f)\n",tmp_l.l,tmp_l.r,tmp_l.c,tmp_l.f);*/
                pq = Insert(pq,tmp_l);
                available[tmp_l.l][tmp_l.r][tmp_l.c] = 0;
                /*printf("%d\n",pq.size);*/
            }
        }
        if(tmp.c+1<=boudn_C) {
            if(available[tmp.l][tmp.r][tmp.c+1]){
                tmp_f.l = tmp.l;
                tmp_f.r = tmp.r;
                tmp_f.c = tmp.c+1;
                dist[tmp_f.l][tmp_f.r][tmp_f.c] = dist[tmp.l][tmp.r][tmp.c]+1;
                if(tmp_f.l==E.l&&tmp_f.r==E.r&&tmp_f.c==E.c){
                    return dist[tmp_f.l][tmp_f.r][tmp_f.c];
                }
                tmp_f.f = Cheby_dist(tmp_f,S) + Cheby_dist(tmp_f,E);
/*                tmp_f.f = dist[tmp_f.l][tmp_f.r][tmp_f.c] + h[tmp_f.l][tmp_f.r][tmp_f.c];
/*                tmp_f.f = sqrt((tmp_f.l-S.l)*(tmp_f.l-S.l)+(tmp_f.r-S.r)*(tmp_f.r-S.r)+(tmp_f.c-S.c)*(tmp_f.c-S.c)) + sqrt((tmp_f.l-E.l)*(tmp_f.l-E.l)+(tmp_f.r-E.r)*(tmp_f.r-E.r)+(tmp_f.c-E.c)*(tmp_f.c-E.c));*/
                /*printf("front: (%d,%d,%d,%.2f)\n",tmp_f.l,tmp_f.r,tmp_f.c,tmp_f.f);*/
                pq = Insert(pq,tmp_f);
                available[tmp_f.l][tmp_f.r][tmp_f.c] = 0;
                /*printf("%d\n",pq.size);*/
            }
        }
        if(tmp.c-1>=0) {
            if(available[tmp.l][tmp.r][tmp.c-1]){
                tmp_b.l = tmp.l;
                tmp_b.r = tmp.r;
                tmp_b.c = tmp.c-1;
                dist[tmp_b.l][tmp_b.r][tmp_b.c] = dist[tmp.l][tmp.r][tmp.c]+1;
                if(tmp_b.l==E.l&&tmp_b.r==E.r&&tmp_b.c==E.c){
                    return dist[tmp_b.l][tmp_b.r][tmp_b.c];
                }
                tmp_b.f = Cheby_dist(tmp_b,S) + Cheby_dist(tmp_b,E);
/*                tmp_b.f = dist[tmp_b.l][tmp_b.r][tmp_b.c] + h[tmp_b.l][tmp_b.r][tmp_b.c];
/*                tmp_b.f = sqrt((tmp_b.l-S.l)*(tmp_b.l-S.l)+(tmp_b.r-S.r)*(tmp_b.r-S.r)+(tmp_b.c-S.c)*(tmp_b.c-S.c)) + sqrt((tmp_b.l-E.l)*(tmp_b.l-E.l)+(tmp_b.r-E.r)*(tmp_b.r-E.r)+(tmp_b.c-E.c)*(tmp_b.c-E.c));*/
                /*printf("back: (%d,%d,%d,%.2f)\n",tmp_b.l,tmp_b.r,tmp_b.c,tmp_b.f);*/
                pq = Insert(pq,tmp_b);
                available[tmp_b.l][tmp_b.r][tmp_b.c] = 0;
                /*printf("%d\n",pq.size);*/
            }
        }
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
    freopen("output.txt", "w", stdout);
#endif
    int L=1,R=1,C=1;
    int i,j,k;
    START = clock();
    while(1){
        scanf("%d%d%d",&L,&R,&C);
/*        printf("%d %d %d\n",L,R,C);*/
        if(L==0&&R==0&&C==0) return 0;
        for(i=0;i<L;i++){
            for(j=0;j<R;j++){
                for(k=0;k<C;k++){
                    MAP[i][j][k] = '#';
                    available[i][j][k] = 0;
                    dist[i][j][k] = -1;
                }
            }
        }
        for(i=0;i<L;i++){
            for(j=0;j<R;j++){
                scanf("%s",MAP[i][j]);
            }
        }
        for(i=0;i<L;i++){
            for(j=0;j<R;j++){
                for(k=0;k<C;k++){
                    if(MAP[i][j][k]=='S') {
                        source.l = i;
                        source.r = j;
                        source.c = k;
                        dist[i][j][k] = 0;
                    }
                    if(MAP[i][j][k]=='E'){
                        goal.l = i;
                        goal.r = j;
                        goal.c = k;
                    }
                    if(MAP[i][j][k]=='#') available[i][j][k] = 0;
                    else available[i][j][k] = 1;
                }
            }
        }
        for(i=0;i<L;i++){
            for(j=0;j<R;j++){
                for(k=0;k<C;k++){
                    h[i][j][k] = max_three(abs(i-goal.l),abs(j-goal.r),abs(k-goal.c));
                }
            }
        }
        source.f = h[source.l][source.r][source.c];
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
                    printf("%.2f",h[i][j][k]);
                    if(k==C-1) printf("\n");
                    else printf(" ");
                }
                if(j==R-1) printf("\n");
            }
        }
*/
        ans = Astar(source,L,R,C,goal);
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
*//*
        for(i=0;i<L;i++){
            for(j=0;j<R;j++){
                for(k=0;k<C;k++){
                    printf("%d",max_three(abs(i-source.l),abs(j-source.r),abs(k-source.c))+max_three(abs(i-goal.l),abs(j-goal.r),abs(k-goal.c)));
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
    printf("time:%.2f\n",(FIN-START)/CLOCKS_PER_SEC);
    system("pause");
    return 0;
}
