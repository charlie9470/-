

#include <stdio.h>
#include <stdlib.h>
typedef struct castles{
    int req; /*require*/
    int die;
    int stay;
    int neighbors[100];
    int n_of_nei;
    int color; /*0 for white 1 for grey 2 for black*/
    int need;
    int lost;
    int rest;
}CA;
typedef struct SORTED{
    int N;
    int L;
    int R;
}S;
struct paths{
    int A;
    int B;
};


CA CAs[101];
struct paths PAs[100];
S Sort_array[100];


int max(int a,int b){
    return a>b?a:b;
}
void add_neighbor(struct paths P){
    CAs[P.A].neighbors[CAs[P.A].n_of_nei++] = P.B;
    CAs[P.B].neighbors[CAs[P.B].n_of_nei++] = P.A;
}
void merge(int S,int mid,int E){
    int i;
    int left_index = S,right_index = mid+1,new_index = 0;
    struct SORTED new_array[E-S+1];
    while(left_index<=mid&&right_index<=E){
        if(Sort_array[left_index].L-Sort_array[left_index].N<=Sort_array[right_index].L-Sort_array[right_index].N){
            new_array[new_index] = Sort_array[left_index];
            left_index++;
        }
        else{
            new_array[new_index] = Sort_array[right_index];
            right_index++;
        }
        /* printf("new_array[%d]: %d\n",new_index,new_array[new_index]);*/
        new_index++;
    }
    if(left_index<=mid){
        for(;new_index<=E-S;){
            new_array[new_index] = Sort_array[left_index++];
            /* printf("new_array[%d]: %d\n",new_index,new_array[new_index]);*/
            new_index++;
        }
    }
    else if(right_index<=E){
        for(;new_index<=E-S;){
            new_array[new_index] = Sort_array[right_index++];
            /* printf("new_array[%d]: %d\n",new_index,new_array[new_index]);*/
            new_index++;
        }
    }
    for(i=0;i<=E-S;i++){
        Sort_array[i+S] = new_array[i];
    }
}
void merge_sort(int S,int E){
    if(S<E){
        int mid = (S+E)/2;
        merge_sort(S,mid);
        merge_sort(mid+1,E);
        merge(S,mid,E);
    }
}
void DFS(int index){
    int i;
    int N,L,R;
    struct SORTED sub_ans;
    struct SORTED temp;
    N = max(CAs[index].req,CAs[index].die+CAs[index].stay);
    L = CAs[index].die+CAs[index].stay;
    R = N-L;
    CAs[index].need = N;
    CAs[index].lost = L;
    CAs[index].rest = R;
    CAs[index].color = 1;
    /*printf("(%d,N,L) before DFS: (%d,%d)\n",index,N,L);*/
    for(i=0;i<CAs[index].n_of_nei;i++){
        if(!CAs[CAs[index].neighbors[i]].color)
            DFS(CAs[index].neighbors[i]);
    }
    /* leaf condition*/
    int num_of_subtrees = 0;
    for(i=0;i<CAs[index].n_of_nei;i++){
        if(CAs[CAs[index].neighbors[i]].color==2){
            Sort_array[num_of_subtrees].N = CAs[CAs[index].neighbors[i]].need;
            Sort_array[num_of_subtrees].L = CAs[CAs[index].neighbors[i]].lost;
            Sort_array[num_of_subtrees].R = CAs[CAs[index].neighbors[i]].rest;
            num_of_subtrees++;
        }
    }
    merge_sort(0,num_of_subtrees-1);
    for(i=0;i<num_of_subtrees;i++){
        temp = Sort_array[i];
        if(CAs[index].rest<temp.N){
            /*printf("Add subtree\n");*/
            CAs[index].need += (temp.N-CAs[index].rest);
            CAs[index].rest += (temp.N-CAs[index].rest);
        }
        CAs[index].lost += temp.L;
        CAs[index].rest -= temp.L;
        /*printf("(N,L) after going to subtree: (%d,%d)\n",CAs[index].need,CAs[index].rest);*/
    }
    /*sort all subtrees*/
    /*printf("(N,L,R) after DFS: (%d,%d,%d)\n",CAs[index].need,CAs[index].lost,CAs[index].rest);*/
    CAs[index].color = 2;
}
int main(void){
    int n;
    int i,j;
    int ans;
    int count = 0;
    #ifndef ONLINE_JUDGE
        freopen("data.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    while(1){
        scanf(" %d",&n);
        if(n==0) break;
        ans = 0;
        count++;
        for(i=1;i<=n;i++){
            scanf(" %d %d %d",&CAs[i].req,&CAs[i].die,&CAs[i].stay);
            CAs[i].n_of_nei = 0;
        }
        for(i=0;i<n-1;i++){
            scanf(" %d %d",&PAs[i].A,&PAs[i].B);
            add_neighbor(PAs[i]);
        }
        ans = -1;
        for(i=1;i<=n;i++){
            for(j=1;j<=n;j++){
                CAs[j].color = 0;
            }
            DFS(i);
            if(ans==-1) ans = CAs[i].need;
            else ans = ans<CAs[i].need?ans:CAs[i].need;
            /*printf("ans of start %d is: %d\n",i,ans);*/
        }
        printf("Case %d: %d\n",count,ans);
    }
    return 0;
}
