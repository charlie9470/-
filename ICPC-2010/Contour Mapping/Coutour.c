#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct triangles{
    long left;
    long right;
    long UOD;/*up or down*/
    int side;/*1 for pointed up 0 for pointed down*/
    int full;
    int R;
    int UD;
}TI;

long max(long a,long b){
    return a>b?a:b;
}
long min(long a,long b){
    return a<b?a:b;
}

TI RE_GRAPH[201][201];
double Cal(TI target,int x,int y,int d,int h){
    double ans = 0.;
    int i;
    long t;
    double length;
    double K;
    double Po,Pt,Pth;/*P_one,P_two*/
    long R_L,R_H;/*range_low,range_high*/
    /*printf("Ti:(L: %d,R: %d,UOD: %d)\n",target.left,target.right,target.UOD);*/
    if(target.left==target.right&&target.right==target.UOD){
        if(target.left%h == 0){
            RE_GRAPH[x][y].full = 1;
            RE_GRAPH[x][y].R=1;
            RE_GRAPH[x][y].UD=1;
            ans += 3*d;
            if(y!=0){
                if(RE_GRAPH[x][y-1].full){
                    ans-=2*d;
                }
                else if(RE_GRAPH[x][y-1].R){
                    ans-=d;
                }
            }
            if(target.side==0&&x!=0){/*check left right up*/
                if(RE_GRAPH[x-1][y].full){
                    ans-=2*d;
                }
                else if(RE_GRAPH[x-1][y].UD){
                    ans-=d;
                }
            }
            /*printf("Case A:[%d,%d] :%lf\n",x,y,ans);*/
            return ans;
        }
        return 0;
    }
    else if(target.left==target.right||target.right==target.UOD||target.left==target.UOD){
        if(target.left==target.right){
            Po = target.UOD;
            Pt = target.left;
            if(target.left%h==0) RE_GRAPH[x][y].UD=1;
        }
        else if(target.right==target.UOD){
            Po = target.left;
            Pt = target.right;
            if(target.right%h==0) RE_GRAPH[x][y].R=1;
        }
        else if(target.left==target.UOD){
            Po = target.right;
            Pt = target.left;
        }
        if(Po>Pt){
            R_L = ceil(Pt/h);
            t = Po;
            if(t%h==0) R_H = Po/h-1;
            else R_H = floor(Po/h);
            length = d*(Po-R_H*h)/(Po-Pt);
            ans+=length*(2*Po-R_L*h-R_H*h)*(R_H-R_L+1)/2/(Po-R_H*h);
        }
        else{
            t = Po;
            if(t%h==0) R_L = Po/h+1;
            else R_L = ceil(Po/h);
            R_H = floor(Pt/h);
            length = d*(R_L*h-Po)/(Pt-Po);
            ans+=length*(R_L*h+R_H*h-2*Po)*(R_H-R_L+1)/2/(R_L*h-Po);
        }
        /*printf("length: %f\n",length);
        printf("R_L: %lf,R_H: %lf,Pt: %lf,Po: %lf\n",R_L,R_H,Pt,Po);*/
        if(y!=0&&RE_GRAPH[x][y-1].R) ans-=d;
        if(x!=0&&target.side==0&&RE_GRAPH[x-1][y].UD) ans-=d;

        /*printf("Case B:[%d,%d] :%lf\n",x,y,ans);*/
        return ans;
    }
    else{
        Po = max(target.UOD,max(target.left,target.right));
        Pth = min(target.UOD,min(target.left,target.right));
        if((Po==target.UOD&&Pth==target.left)||(Po==target.left&&Pth==target.UOD)){
            Pt = target.right;
        }
        else if((Po==target.UOD&&Pth==target.right)||(Po==target.right&&Pth==target.UOD)){
            Pt = target.left;
        }
        else if((Po==target.left&&Pth==target.right)||(Po==target.right&&Pth==target.left)){
            Pt = target.UOD;
        }
        R_L = floor(Pth/h+1);
        R_H = ceil(Po/h-1);
        if(Pt>(Po+Pth)/2) K = d*(Po-Pt)/(Po-Pth);
        else K = d*(Pt-Pth)/(Po-Pth);
        length=sqrt(K*K+d*d-K*d);
        /* printf("length: %.10lf\n",length);
        // length = (length*100000+0.5)/100000;
        // printf("Po: %lf,Pth: %lf,Pt: %lf,length: %lf\n",Po,Pth,Pt,length);
        // printf("R_L: %lf\n",R_L);
        // printf("R_H: %lf\n",R_H);*/
        i = Pt;
        if(i%h==0) ans+=length;
        i = ceil(Pt/h-1);
        /* printf("%d\n",i);*/
        ans+= length*(R_L*h+i*h-2*Pth)*(i-R_L+1)/(2.0*(Pt-Pth));
/*        printf("(%lf * %d + %d * %d -2* %lf )*( %d - %lf +1)/(2.0*( %lf - %lf )) =\n",R_L,h,i,h,Pth,i,R_L,Pt,Pth);
        printf("(%lf)*(%lf)/(%lf) = \n",(double)(R_L*h+i*h-2*Pth),(double)(i-R_L+1));
        printf("%lf/%lf = %lf\n",(double)(R_L*h+i*h-2*Pth)*(double)(i-R_L+1),(double)(2.0*(Pt-Pth)),(double)(R_L*h+i*h-2*Pth)*(double)(i-R_L+1)/(double)(2.0*(Pt-Pth)));*/
        i = floor(Pt/h+1);
        ans+= length*(2*Po-(R_H*h+i*h))*(R_H-i+1)/(2.0*(Po-Pt));
        /* printf("(2*%lf-(%lf*%d+%d*%d))*(%lf-%d+1)/(2.0*(%lf-%lf) =\n",Po,R_H,h,i,h,R_H,i,Po,Pt);
        // printf("(%lf)*(%lf)/(%lf) =\n%lf\n",(double)(2*Po-(R_H*h+i*h)),(double)(R_H-i+1),(double)(2.0*(Po-Pt)),(double)(2*Po-(R_H*h+i*h))*(double)(R_H-i+1)/(double)(2.0*(Po-Pt)));
        // printf("Case C:[%d,%d] :%lf\n",x,y,ans);
        // printf("Case C:[%d,%d] :%lf\n",x,y,ans);
        // printf("length: %.10f\n",length);
        // printf("Case C:[%d,%d] :%lf\n",x,y,ans);*/
        return ans;
    }
    return ans;
}

int main(void){
    int i,j;
    double ans = 0;
    int count = 0;
    int s,p,d,h;
    long GRAPH[200][200];
    #ifndef ONLINE_JUDGE
        freopen("data.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    while(1){
        scanf(" %d",&s);
        if(s==0) return 0;
        for(i=0;i<200;i++){
            for(j=0;j<200;j++){
                RE_GRAPH[i][j].full = 0;
                RE_GRAPH[i][j].R = 0;
                RE_GRAPH[i][j].UD = 0;
            }
        }
        for(i=0;i<200;i++){
            for(j=0;j<200;j++){
                GRAPH[i][j] = 0;
            }
        }
        scanf(" %d %d %d",&p,&d,&h);
        ans = 0;
        count++;
        for(i=0;i<s;i++){
            if(i%2){
                for(j=0;j<p+1;j++){
                    scanf(" %ld",&GRAPH[i][j]);
                }
            }
            else{
                for(j=0;j<p;j++){
                    scanf(" %ld",&GRAPH[i][j]);
                }
            }
        }
        for(i=0;i<s-1;i++){
            for(j=0;j<2*p-1;j++){
                if(i%2){
                    if((i+j)%2){
                        RE_GRAPH[i][j].side = 0;
                        RE_GRAPH[i][j].left = GRAPH[i][j/2];
                        RE_GRAPH[i][j].right = GRAPH[i][j/2+1];
                        RE_GRAPH[i][j].UOD = GRAPH[i+1][j/2];
                    }
                    else{
                        RE_GRAPH[i][j].side = 1;
                        RE_GRAPH[i][j].left = GRAPH[i+1][j/2];
                        RE_GRAPH[i][j].right = GRAPH[i+1][j/2+1];
                        RE_GRAPH[i][j].UOD = GRAPH[i][j/2+1];
                    }
                }
                else{
                    if((i+j)%2){
                        RE_GRAPH[i][j].side = 0;
                        RE_GRAPH[i][j].left = GRAPH[i][j/2];
                        RE_GRAPH[i][j].right = GRAPH[i][j/2+1];
                        RE_GRAPH[i][j].UOD = GRAPH[i+1][j/2+1];
                    }
                    else{
                        RE_GRAPH[i][j].side = 1;
                        RE_GRAPH[i][j].left = GRAPH[i+1][j/2];
                        RE_GRAPH[i][j].right = GRAPH[i+1][j/2+1];
                        RE_GRAPH[i][j].UOD = GRAPH[i][j/2];
                    }
                }
                /*printf("{%d,%d}:L: %d,R: %d,U: %d\n",i,j,RE_GRAPH[i][j].left,RE_GRAPH[i][j].right,RE_GRAPH[i][j].UOD);*/
            }
        }
        for(i=0;i<s-1;i++){
            for(j=0;j<2*p-1;j++){
                ans += Cal(RE_GRAPH[i][j],i,j,d,h);
            }
        }
        printf("Case %d: %.0lf\n",count,(ans*10+0.5)/10);
    }
}
