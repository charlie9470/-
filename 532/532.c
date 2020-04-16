#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>
#define MAX_SIZE 35

typedef struct{
    int l,r,c;
    int d;
}Co_Or;
    Co_Or queue[30000];
    int front,end;
    