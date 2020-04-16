#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#define MAX_SIZE 20001

#ifndef ONLINE_JUDGE
    #include <conio.h>
#endif
typedef struct node{
    int index;
    int late;
    int visited;
    struct node* next;
    struct node* tail;
}Node;
typedef struct pq_node{
    int index;
    int late;
}PQN;
Node* GRAPH[MAX_SIZE];
typedef struct Heap{
    struct pq_node pq[MAX_SIZE];
    int handle[MAX_SIZE];/*index 0 stores the position of the first element in qp*/
    int size;
}BH;

BH B_H;

int Max(int a,int b){
    return a>b?a:b;
}
PQN Min_Node(PQN a,PQN b){
    return b.late<a.late?b:a;
}

void Insert(PQN A){
    int i;
    PQN temp;
    int tmp;
    B_H.size++;
    B_H.pq[B_H.size] = A;
    B_H.handle[A.index] = B_H.size;
    for(i=B_H.size;i>1;){
        if(B_H.pq[i].late>=B_H.pq[i/2].late) {/*a heap*/
            break;
        }
        else{
            temp = B_H.pq[i];
            B_H.pq[i] = B_H.pq[i/2];
            B_H.pq[i/2] = temp;/*check upward*/
            tmp = B_H.handle[B_H.pq[i].index];
            B_H.handle[B_H.pq[i].index] = B_H.handle[B_H.pq[i/2].index];
            B_H.handle[B_H.pq[i/2].index] = tmp;
            i/=2;
        }
    }
}
void heapify(int index){
    int i;
    int tmp;
    PQN temp;
    PQN min;
    for(i=index;i*2+1<=B_H.size;){
        min = Min_Node(Min_Node(B_H.pq[i],B_H.pq[2*i]),B_H.pq[2*i+1]);
        if(min.index==B_H.pq[i].index&&min.late==B_H.pq[i].late){
            return ;/*already BH*/
        }
        else if(min.index==B_H.pq[2*i].index&&min.late==B_H.pq[2*i].late){
            /*swap with left subtree check leftsubtree*/
            temp = B_H.pq[i];
            B_H.pq[i] = B_H.pq[2*i];
            B_H.pq[2*i] = temp;
            tmp = B_H.handle[B_H.pq[i].index];
            B_H.handle[B_H.pq[i].index] = B_H.handle[B_H.pq[2*i].index];
            B_H.handle[B_H.pq[2*i].index] = tmp;
            i = 2*i;
        }
        else if(min.index==B_H.pq[2*i+1].index&&min.late==B_H.pq[2*i+1].late){
            /*swap with right subtree check rightsubtree*/
            temp = B_H.pq[i];
            B_H.pq[i] = B_H.pq[2*i+1];
            B_H.pq[2*i+1] = temp;
            tmp = B_H.handle[B_H.pq[i].index];
            B_H.handle[B_H.pq[i].index] = B_H.handle[B_H.pq[2*i+1].index];
            B_H.handle[B_H.pq[2*i+1].index] = tmp;
            i = 2*i+1;
        }
    }
    if(i*2==B_H.size){
        if(B_H.pq[i].late>B_H.pq[2*i].late){
            temp = B_H.pq[i];
            B_H.pq[i] = B_H.pq[2*i];
            B_H.pq[2*i] = temp;
            tmp = B_H.handle[B_H.pq[i].index];
            B_H.handle[B_H.pq[i].index] = B_H.handle[B_H.pq[2*i].index];
            B_H.handle[B_H.pq[2*i].index] = tmp;
        }
    }
}
void Extract_Min(){
    if(B_H.size==0) return ;/*empty*/
    B_H.pq[1] = B_H.pq[B_H.size];
    B_H.handle[B_H.pq[1].index] = 1;
    B_H.size-=1;
    if(B_H.size>1) heapify(1);
}
int Get_Min(){
    if(B_H.size==0) return -1;
    return B_H.pq[1].index;
}
int FindPosition(int index){
    return B_H.handle[index];
}
void Decrease_Key(int index,int new_L){
    int i;
    PQN temp;
    int tmp;
    int pos = FindPosition(index);
/*    printf("B_H.handle[%d] = %d\n",index,pos);
    printf("B_H.pq[%d] = %d\n",pos,B_H.pq[pos].index);*/
    B_H.pq[pos].late = new_L;
    for(i=pos;i>1;){
        if(B_H.pq[i].late>B_H.pq[i/2].late) break;/*a heap*/
        else{
            temp = B_H.pq[i];
            B_H.pq[i] = B_H.pq[i/2];
            B_H.pq[i/2] = temp;/*check upward*/
            tmp = B_H.handle[B_H.pq[i].index];
            B_H.handle[B_H.pq[i].index] = B_H.handle[B_H.pq[i/2].index];
            B_H.handle[B_H.pq[i/2].index] = tmp;
            i/=2;
        }
    }
}

int Dijkstra(int S,int T){
    int i;
    Node* tmp;
    PQN temp;
    int next;
    temp.index = S;
    temp.late = 0;
    B_H.size = 0;
    Insert(temp);
    while(1){
/*        for(i=1;i<=B_H.size;i++){
            printf("B_H.pq[%2d]:%3d,B_H.pq[%2d].late: %5d,B_H.handle[%2d]: %d\n",i,B_H.pq[i].index,i,B_H.pq[i].late,B_H.pq[i].index,B_H.handle[B_H.pq[i].index]);
        }*/
        if(GRAPH[T]->visited){
            return GRAPH[T]->late;
        }
        next = Get_Min();
/*        printf("next: %d,GRAPH[%d]: %d\n",next,GRAPH[next]->index,GRAPH[next]->late);*/
        if(next==-1) {return -1;}
        Extract_Min();
/*            printf("size: %d\n",B_H.size);*/
        tmp = GRAPH[next];
/*            printf("(%d,%d)\n",tmp->index,tmp->late);*/
        GRAPH[next]->visited = 1;
        if(next==T) continue;
        while(tmp->next!=NULL){
            tmp = tmp->next;
/*                printf("(%d,%d)\n",tmp->index,tmp->late);
            printf("through %d to %d: %d\n",GRAPH[next]->index,tmp->index,GRAPH[next]->late+tmp->late);*/
            if(GRAPH[tmp->index]->late==-1){
                GRAPH[tmp->index]->late = GRAPH[next]->late+tmp->late;
                temp.index = tmp->index;
                temp.late = GRAPH[next]->late+tmp->late;
                Insert(temp);
/*                    printf("temp (%d,%d) inserted\n",temp.index,temp.late);
                printf("size: %d\n",B_H.size);
*/                }
            else if(GRAPH[tmp->index]->late>GRAPH[next]->late+tmp->late){
                GRAPH[tmp->index]->late = GRAPH[next]->late+tmp->late;
                Decrease_Key(tmp->index,GRAPH[next]->late+tmp->late);
/*                    printf("node(%d) decreased to late: %d\n",tmp->index,GRAPH[tmp->index]->late);
*/                }
/*                for(i=1;i<=B_H.size;i++){
                printf("B_H.pq[%2d]:%3d,B_H.pq[%2d].late: %5d,B_H.handle[%2d]: %d\n",i,B_H.pq[i].index,i,B_H.pq[i].late,B_H.pq[i].index,B_H.handle[B_H.pq[i].index]);
            }*/
        }
    }
}

int main(){
    int N,n,m,S,T;
    int i,j;
    int a,b,laten;
    int ans;
    Node *tmp,*tmp_a,*tmp_b,*temp;
    #ifndef ONLINE_JUDGE
        freopen("data.test.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif

    scanf("%d",&N);
/*    printf("N: %d\n",N);*/
    for(j=0;j<MAX_SIZE;j++){
        GRAPH[j] = (Node*) malloc(sizeof(Node));
        GRAPH[j]->index = j;
    }
    for(i=0;i<N;i++){
        scanf("%d%d%d%d",&n,&m,&S,&T);
/*        printf("n:%d,m:%d,S:%d,T:%d\n",n,m,S,T);*/
        B_H.size = 0;
/*        for(j=0;j<MAX_SIZE;j++){
            B_H.handle[j] = -1;
        }*/
        for(j=0;j<n;j++){
            GRAPH[j]->late = -1;
            GRAPH[j]->next = NULL;
            GRAPH[j]->tail = GRAPH[j];
            GRAPH[j]->visited = 0;
        }
        GRAPH[S]->late = 0;
        GRAPH[S]->visited = 1;
        for(j=0;j<m;j++){
            scanf("%d%d%d",&a,&b,&laten);
            tmp_a = (Node*) malloc(sizeof(Node));
            tmp_a->next = NULL;
            tmp_a->index = b;
            tmp_a->late = laten;
            GRAPH[a]->tail->next = tmp_a;
            GRAPH[a]->tail = tmp_a;
            tmp_b = (Node*) malloc(sizeof(Node));
            tmp_b->next = NULL;
            tmp_b->index = a;
            tmp_b->late = laten;
            temp = GRAPH[b];
            temp->tail->next = tmp_b;
            temp->tail = tmp_b;
        }
/*        for(j=0;j<n;j++){
        	tmp = GRAPH[j];
        	while(tmp->next!=NULL){
        		printf("%d(%d)->",tmp->index,tmp->late);
        		tmp = tmp->next;
			}
			printf("%d(%d)\n",tmp->index,tmp->late);
        }*/
        ans = Dijkstra(S,T);
/*        for(j=0;j<n;j++){
        	tmp = GRAPH[j];
        	while(tmp->next!=NULL){
        		printf("%d(%d)->",tmp->index,tmp->late);
        		tmp = tmp->next;
			}
			printf("%d(%d)\n",tmp->index,tmp->late);
        }
*/        printf("Case #%d: ",i+1);
        if(ans==-1) printf("unreachable\n");
        else printf("%d\n",ans);
    }
/*        for(j=0;j<n;j++){
            tmp = GRAPH[j];
            while(tmp->next!=NULL){
                temp = tmp;
                tmp = tmp->next;
                free(temp);
            }
        }*/
    return 0;
}
