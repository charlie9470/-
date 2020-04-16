#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int main(){
    int N,n,i;
    int count = 0;
    int zero,one,B_zero,S_zero,B_one,S_one;
    float range_one_floor,range_one_ceil,range_zero_floor,range_zero_ceil;
    float split;
    int codes[200],re_codes[200];
    freopen("data.txt","r",stdin);
    freopen("debug.txt","w",stdout);
    while(1){
        scanf(" %d",&N);
        if(N==0) return 0;
        count++;
        for(i=0;i<150;i++){
            codes[i] = 0;
            re_codes[i] = 0;
        }
        printf("Case %d: ",count);
        for(i=0;i<N;i++){
            scanf(" %d",&codes[i]);
            printf("%d",codes[i]);
            if(i==N-1) printf("\n");
            else printf(" ");
            if(i==0){
                S_zero = codes[i];
                B_zero = codes[i];
                zero = codes[i];
                split = codes[i]*1.5;
                /*printf("split: %f\n",split);*/
            }
            else if(i==2){
                S_one = codes[i];
                B_one = codes[i];
                one = codes[i];
            }
            else if(codes[i]<split){
                if(codes[i]<S_zero){
                    S_zero = codes[i];
                }
                else if(codes[i]>B_zero){
                    B_zero = codes[i];
                }
            }
            else if(codes[i]>split){
                if(codes[i]<S_one){
                    S_one = codes[i];
                }
                else if(codes[i]>B_one){
                    B_one = codes[i];
                }
            }
        }

        range_one_ceil = (float)S_one/0.95;
        range_one_floor = (float)B_one/1.05;
        range_zero_ceil = (float)S_zero/0.95;
        range_zero_floor = (float)B_zero/1.05;
        printf("S_zero = %d, B_zero = %d, S_one = %d, B_one = %d\n",S_zero,B_zero,S_one,B_one);
        printf("min_Zero: %f, Max_Zero: %f, min_One: %f, Max_One: %f\n",range_zero_floor,range_zero_ceil,range_one_floor,range_one_ceil);
    }
}
