#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#ifndef ONLINE_JUDGE
    #include<conio.h>
#endif
char strings_code[12][6]={
    "00001",
    "10001",
    "01001",
    "11000",
    "00101",
    "10100",
    "01100",
    "00011",
    "10010",
    "10000",
    "00100",
    "00110"
};
char ans_string[50];
int Process(int size,int* target){
    int i,j;
    int buf_index=6;
    int ans_index=0;
    char IN[150];
    char buf[6];
    int c=0,k=0,C=0,K=0;
    strcpy(IN,"");
    for(i=0;i<size;i++){
        if(target[i]==0) IN[i] = '0';
        else if(target[i]==1) IN[i] = '1';
    }
    IN[size] = '\0';
    int length = (size+1)/6;
    strcpy(buf,"");
    for(j=0;j<5;j++){
        buf[j] = IN[j];
    }
    buf[5] = '\0';
/*    printf("buf: %s\n",buf);
    printf("START symbol: %s\n",strings_code[11]);
    printf("buf==START: %d\n",!strcmp(buf,strings_code[11]));*/
    if(strcmp(buf,strings_code[11])!=0) return 0;/*START*/
    if(IN[5]!='0') return 0;/*seperate*/
    for(i=0;i<length-2;i++){
        for(j=0;j<5;j++){
            buf[j] = IN[buf_index+j];
        }
        for(j=0;j<11;j++){
            if(!strcmp(buf,strings_code[j])){
                if(j==10) ans_string[ans_index] = '-';
                else ans_string[ans_index] = j+'0';
/*              printf("ans_string[%d]: %c\n",ans_index,ans_string[ans_index]);*/
                ans_index++;
                break;
            }
            if(j==10){
                return 0; /*Undefined code or START/STOP in middle*/
            }
        }
        buf_index+=5;
        if(IN[buf_index]!='0') return 0;/*seperate 0*/
        buf_index++;
        ans_string[ans_index] = '\0';
    }
/*    printf("%s\n",ans_string);*/
    for(j=0;j<5;j++){
        buf[j] = IN[buf_index+j];
    }
    if(strcmp(buf,strings_code[11])!=0) return 0; /*STOP*/
    if(ans_string[ans_index-1]=='-') K = 10;
    else K = ans_string[ans_index-1]-'0';
    if(ans_string[ans_index-2]=='-') C = 10;
    else C = ans_string[ans_index-2]-'0';
/*    printf("K=%d,C=%d\n",K,C);*/
    c=0;
    k=0;
    for(i=1;i<ans_index;i++){
        if(ans_string[i-1]=='-'){
            c+=((length-4-i)%10+1)*10;
        }
        else{
            c+=((length-4-i)%10+1)*(ans_string[i-1]-'0');
        }
        c%=11;
    }
/*    printf("%d,%d\n",c,C);*/
    if(c!=C) return 2;/*BAD C*/
    for(i=1;i<ans_index;i++){
        if(ans_string[i-1]=='-'){
            k+=((length-4-i+1)%9+1)*10;
        }
        else{
            k+=((length-4-i+1)%9+1)*(ans_string[i-1]-'0');
        }
        k%=11;
    }
/*    printf("%d,%d\n",k,K);*/
    if(k!=K) return 3;/*BAD K*/
    ans_string[ans_index-2] = '\n';
    ans_string[ans_index-1] = '\0';
    return 1;
}
int main(){
    int N,n,i;
    int ans;
    int count = 0;
    int zero,one,B_zero,S_zero,B_one,S_one;
    float range_one_floor,range_one_ceil,range_zero_floor,range_zero_ceil;
    float split;
    int codes[200],re_codes[200];
    #ifndef ONLINE_JUDGE
        freopen("data.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    while(1){
        scanf(" %d",&N);
        if(N==0) return 0;
        count++;
        for(i=0;i<150;i++){
            codes[i] = 0;
            re_codes[i] = 0;
        }
        for(i=0;i<N;i++){
            scanf(" %d",&codes[i]);
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
        if(N%6!=5||N<29){
            printf("Case %d: bad code\n",count);
            continue;
        }
        range_one_ceil = (float)S_one/0.95;
        range_one_floor = (float)B_one/1.05;
        range_zero_ceil = (float)S_zero/0.95;
        range_zero_floor = (float)B_zero/1.05;
/*        printf("%f,%f,%f,%f\n",range_zero_floor,range_zero_ceil,range_one_floor,range_one_ceil);*/
        ans = 0;
        if(S_zero*21<B_zero*19||S_one*21<B_one*19/*range_zero_ceil<range_zero_floor||range_one_ceil<range_one_floor/**/||2*range_zero_ceil<range_one_floor||2*range_zero_floor>range_one_ceil/*||S_zero<1||B_one>200*/){
            printf("Case %d: bad code\n",count);
            /* printf("Out of 5 percent bound\nOr no possible width\nOr out of bound\n");*/
            continue;
        }
        for(i=0;i<N;i++){
            if(codes[i]<split) codes[i] = 0;
            else if(codes[i]>split) codes[i] = 1;
        }
        for(i=0;i<N;i++){
            re_codes[i] = codes[N-i-1];
        }
        strcpy(ans_string,"");
        ans = Process(N,codes)+Process(N,re_codes);
        printf("Case %d: ",count);
        if(ans==0) printf("bad code\n");
        else if(ans==1) printf("%s",ans_string);
        else if(ans==2) printf("bad C\n");
        else if(ans==3) printf("bad K\n");
    }
}
