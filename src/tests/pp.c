#include <stdio.h>

int main(){
    int** p;
    int* t;
    int a = 10;

//    t = &a;

    printf("%d", *t);

    p = &t;

    printf("%d", **p);

 //   *p = t;
 //   printf("%d", **p);

    return 0;
}