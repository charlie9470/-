#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
int main(void){
    srand(time(NULL));
    freopen("test.txt","w",stdout);
    int s,p,d,h;
    int i,j;
    /* scanf(" %d %d %d %d",&s,&p,&d,&h);*/
    s=100;
    p=100;
    d=10;
    h=1;
    printf("%d %d %d %d\n",s,p,d,h);
    for(i=0;i<s;i++){
        if(i%2){
            for(j=0;j<p+1;j++){
                if((i+j)%3==0) printf("1 ");
                else if((i+j)%3==1) printf("500000 ");
                else printf("1000000 ");
            }
            printf("\n");
        }
        else{
            for(j=0;j<p;j++){
                if((i+j)%3==0) printf("1 ");
                else if((i+j)%3==1) printf("500000 ");
                else printf("1000000 ");
            }
            printf("\n");
        }
    }
    printf("0\n");
    return 0;
}
