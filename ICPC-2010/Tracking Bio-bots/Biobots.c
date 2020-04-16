#include<stdio.h>
#include<stdlib.h>
int move[2][2] = {
    {-1,0},
    {0,-1}
};
typedef struct block{
    int status;
    long long size;
}BL;
typedef struct wall_block{
    int x_start;
    int x_end;
    int y_start;
    int y_end;
}WB;
BL map[2005][2005];
WB walls[1005];
struct pos{
    int x;
    int y;
};
struct pos queue[5000000];
int X_array[3000],Y_array[3000];
int front=0,end=0;
int iSempty(){
    if(front==end) return 1;
    else return 0;
}
void Push(struct pos F){
    if(end==4999999){
        queue[end] = F;
        end = 0;
    }
    else{
        queue[end++] = F;
    }
    if(end==front) printf("queue is full\n");
}
void PoP(void){
    struct pos empty = {-1,-1};
    if(front==4999999){
        queue[front] = empty;
        front = 0;
    }
    else{
        queue[front++] = empty;
    }
}
struct pos Front(void){
    return queue[front];
}
void PrintfX(int size){
    int i;
    printf("X_array: ");
    for(i=0;i<size;i++){
        printf("%d ",X_array[i]);
    }
    printf("\n");
}
void PrintfY(int size){
    int i;
    printf("Y_array: ");
    for(i=0;i<size;i++){
        printf("%d ",Y_array[i]);
    }
    printf("\n");
}
int remove_redundant_X(int size){
    int i,j;
    int new_array[3000];
    int newsize=size;
    int index = 1;
    new_array[0] = X_array[0];
    for(i=1;i<size;i++){
        if(X_array[i]!=X_array[i-1]){
            new_array[index++] = X_array[i];
        }
        else newsize--;
    }
    for(i=0;i<size;i++){
        if(i<newsize) X_array[i] = new_array[i];
        else X_array[i] = -1;
    }
    return newsize;
}
int remove_redundant_Y(int size){
    int i,j;
    int new_array[3000];
    int newsize=size;
    int index = 1;
    new_array[0] = Y_array[0];
    for(i=1;i<size;i++){
        if(Y_array[i]!=Y_array[i-1]){
            new_array[index++] = Y_array[i];
        }
        else newsize--;
    }
    for(i=0;i<size;i++){
        if(i<newsize) Y_array[i] = new_array[i];
        else Y_array[i] = -1;
    }
    return newsize;
}
void merge_X(int S,int mid,int E){
    /* printf("Merge (%d,%d,%d)\n",S,mid,E);*/
    int i;
    int left_index = S,right_index = mid+1,new_index = 0;
    int new_array[E-S+1];
    while(left_index<=mid&&right_index<=E){
        if(X_array[left_index]<=X_array[right_index]){
            new_array[new_index] = X_array[left_index];
            left_index++;
        }
        else{
            new_array[new_index] = X_array[right_index];
            right_index++;
        }
        /* printf("new_array[%d]: %d\n",new_index,new_array[new_index]);*/
        new_index++;
    }
    if(left_index<=mid){
        for(;new_index<=E-S;){
            new_array[new_index] = X_array[left_index++];
            /* printf("new_array[%d]: %d\n",new_index,new_array[new_index]);*/
            new_index++;
        }
    }
    else if(right_index<=E){
        for(;new_index<=E-S;){
            new_array[new_index] = X_array[right_index++];
            /* printf("new_array[%d]: %d\n",new_index,new_array[new_index]);*/
            new_index++;
        }
    }
    for(i=0;i<=E-S;i++){
        X_array[i+S] = new_array[i];
    }
}
void merge_sort_X(int S,int E){
    if(S<E){
        int mid = (S+E)/2;
        merge_sort_X(S,mid);
        merge_sort_X(mid+1,E);
        merge_X(S,mid,E);
    }
}
void merge_Y(int S,int mid,int E){
    /* printf("Merge (%d,%d,%d)\n",S,mid,E);*/
    int i;
    int left_index = S,right_index = mid+1,new_index = 0;
    int new_array[E-S+1];
    while(left_index<=mid&&right_index<=E){
        if(Y_array[left_index]<=Y_array[right_index]){
            new_array[new_index] = Y_array[left_index];
            left_index++;
        }
        else{
            new_array[new_index] = Y_array[right_index];
            right_index++;
        }
        /* printf("new_array[%d]: %d\n",new_index,new_array[new_index]);*/
        new_index++;
    }
    if(left_index<=mid){
        for(;new_index<=E-S;){
            new_array[new_index] = Y_array[left_index++];
            /* printf("new_array[%d]: %d\n",new_index,new_array[new_index]);*/
            new_index++;
        }
    }
    else if(right_index<=E){
        for(;new_index<=E-S;){
            new_array[new_index] = Y_array[right_index++];
            /* printf("new_array[%d]: %d\n",new_index,new_array[new_index]);*/
            new_index++;
        }
    }
    for(i=0;i<=E-S;i++){
        Y_array[i+S] = new_array[i];
    }
}
void merge_sort_Y(int S,int E){
    if(S<E){
        int mid = (S+E)/2;
        merge_sort_Y(S,mid);
        merge_sort_Y(mid+1,E);
        merge_Y(S,mid,E);
    }
}
int Binary_search_X(int source,int begin,int end){
    int index;
    int B = begin;
    int E = end;
    if(X_array[begin] == source) return begin;
    if(X_array[end] == source) return end;
    while(B!=E){
        index = (B+E)/2;
        if(X_array[index] == source) return index;
        if(X_array[index]>source){
            E = index;
        }
        if(X_array[index]<source){
            B = index;
        }
    }
    printf("not in array\n");
}
int Binary_search_Y(int source,int begin,int end){
    int index;
    int B = begin;
    int E = end;
    if(Y_array[begin] == source) return begin;
    if(Y_array[end] == source) return end;
    while(B!=E){
        index = (B+E)/2;
        if(Y_array[index] == source) return index;
        if(Y_array[index]>source){
            E = index;
        }
        if(Y_array[index]<source){
            B = index;
        }
    }
    printf("not in array\n");
}
void init_walls(int w){
    int i;
    for(i=0;i<w;i++){
        walls[i].x_start = 0;
        walls[i].x_end = 0;
        walls[i].y_start = 0;
        walls[i].y_end = 0;
    }
}
void init_graph(int m,int n){
    int i,j;
    for(i=0;i<=2004;i++){
        for(j=0;j<=2004;j++){
            map[i][j].status = 0;
            map[i][j].size = 0;
        }
    }
}
void init_array(void){
    int i;
    for(i=0;i<3000;i++){
        X_array[i] = -1;
        Y_array[i] = -1;
    }
}
void BFS(struct pos P){
/*    printf("pos:(%d,%d,%d)\n",P.x,P.y,map[P.x][P.y].status);*/
    int x;
    struct pos n_pos;
    struct pos temp;
    if(map[P.x][P.y].status==-1) return;
    map[P.x][P.y].status=1;
    Push(P);
    /* printf("Start (%d,%d)\n",P.x,P.y);*/
    while(!iSempty()){
        n_pos = Front();
        /* printf("n_pos: (%d,%d),     %d,%d,size: %d\n",n_pos.x,n_pos.y,end,front,end-front);*/
        PoP();
        for(x=0;x<2;x++){
            temp.x = n_pos.x+move[x][0];
            temp.y = n_pos.y+move[x][1];
            if(map[temp.x][temp.y].status==0){
                map[temp.x][temp.y].status=1;
                Push(temp);
            }
        }
    }
}
long long calculate(int m,int n){
    long long ans=0;
    int count=0;
    int i,j;
    for(i=0;i<=m;i++){
        for(j=0;j<=n;j++){
            if(map[i][j].status==0){
                ans+=map[i][j].size;
                /* printf("(%d,%d)%lld,%lld\n",i,j,map[i][j].size,ans);*/
            }
        }
    }
    return ans;
}
void PRINTG(int m,int n){
    int i,j;
/*    for(i=0;i<=m;i++){
        for(j=0;j<=n;j++){
            printf("%2d ",map[i][j].status);
        }
        printf("\n");
    }*/
    for(i=0;i<=m;i++){
        for(j=0;j<=n;j++){
            printf("%lld ",map[i][j].size);
        }
        printf("\n");
    }
}
int main(){
    #ifndef ONLINE_JUDGE
        freopen("data.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    int m,n,w,i,j;
    int count;
    long long ans,cal_X,cal_Y;
    int wall_count;
    int x_a,x_b,y_a,y_b;
    int index_x,index_y_start,index_y_end;
    while(1){
        scanf(" %d %d %d",&m,&n,&w);
        /* printf("%d %d %d\n",m,n,w);*/
        if(m==0&n==0&w==0){
            break;
        }
        init_walls(w);
        init_graph(m,n);
        init_array();
        count++;
        wall_count = 0;
        ans = 0;
        X_array[0] = 0;
        Y_array[0] = 0;
        X_array[1] = m;
        Y_array[1] = n;
        for(i=1;i<(2*w);){
            scanf(" %d %d %d %d",&y_a,&x_a,&y_b,&x_b);
            i++;
            X_array[i] = x_a;
            Y_array[i] = y_a;
            i++;
            X_array[i] = x_b+1;
            Y_array[i] = y_b+1;
            walls[wall_count].x_start = x_a;
            walls[wall_count].x_end = x_b+1;
            walls[wall_count].y_start = y_a;
            walls[wall_count].y_end = y_b+1;
            wall_count++;
        }
        int i_x = i+1;
        int i_y = i+1;
        /* PrintfX(i_x);*/
        merge_sort_X(0,i_x-1);
        /* PrintfX(i_x);*/
        merge_sort_Y(0,i_y-1);
        /* PrintfX(i_x);*/
        /* PrintfY(i_y);*/
        i_x = remove_redundant_X(i_x);
        i_y = remove_redundant_Y(i_y);
/*        PrintfX(i_x);
        PrintfY(i_y);*/
        for(i=0;i<2*w+5;i++){
            for(j=0;j<2*w+5;j++){
                map[i][j].status = -1;
                map[i][j].size = 0;
            }
        }
        for(i=1;i<i_x;i++){
                cal_X = X_array[i]-X_array[i-1];
            for(j=1;j<i_y;j++){
                cal_Y = Y_array[j]-Y_array[j-1];
                /* printf("(%d,%d)X: %lld,Y: %lld,size: %lld\n",i,j,cal_X,cal_Y,cal_X*cal_Y);*/
                map[i][j].status = 0;
                map[i][j].size = cal_X*cal_Y;
            }
        }
        /*walls*/
        /* PRINTG(i_x,i_y);
        /* printf("\n-------------------\n\n");*/
        for(i=0;i<wall_count;i++){
/*            printf("wall_count: %d,i= %d\n",wall_count,i);
            printf("(%d,%d,%d,%d)\n",walls[i].x_start,walls[i].x_end,walls[i].y_start,walls[i].y_end);*/
            index_x = Binary_search_X(walls[i].x_start,0,i_x-1);
            index_y_start = Binary_search_Y(walls[i].y_start,0,i_y-1);
            index_y_end = Binary_search_Y(walls[i].y_end,0,i_y-1);
/*            printf("%d\n",i_y-1);
            printf("(%d,%d)\n",index_y_start,index_y_end);
            printf("(%d)\n",index_x);*/
            for(j=index_y_start;j<index_y_end;j++){
                map[index_x+1][j+1].status = -1;
                map[index_x+1][j+1].size = 0;
            }
        }
        /* PRINTG(i_x,i_y);*/
/*        printf("--------------------------\n");*/
        /*BFS*/
        /* printf("before enter BFS\n");*/
        struct pos E = {i_x-1,i_y-1};
        BFS(E);
        /*Calculate ans*/
        /* PRINTG(i_x,i_y);*/
        ans = calculate(i_x,i_y);
        printf("Case %d: %lld\n",count,ans);
        /* printf("----------------------------------------------------------\n");*/
    }
    return 0;
}
