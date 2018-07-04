#include <stdio.h>

struct test{
        int a;
        int b;
        int c;
        int d;
}

main(){
        struct test t;
        t.a=t.b=t.c=t.d=1;
        sub(&t);
        printf("t.a=%d\n", t.a);
}
sub(struct test *x)
{
        x->a=7;	//Different notation

}

