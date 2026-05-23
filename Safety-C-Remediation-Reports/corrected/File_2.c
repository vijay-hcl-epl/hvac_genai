#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MAX 10
#define ANSWER_TO_LIFE 42

/* #define UNUSED_MACRO 100   // Violation 1: Unused macro */

static int globalVar = 0;         /* Violation 2: Non-static global variable fixed */

void delay(void)
{
    int i;
    for(i = 0; i < 100000; i++)
    {
        /* Intentional delay - consider using a hardware timer or comment */
    }
}

int add(int a, int b)
{
    /* Validate inputs as required */
    return a + b;
}

void unsafeFunction(void)
{
    int x = 0;
    int arr[5];

    /* arr[10] = 5; */           /* Violation 5: Out-of-bounds access fixed */

    if(x == 5)             /* x initialized to 0 */
    {
        printf("x is 5\n");
    }

    /* int y = 10 / 0; */        /* Violation 7: Division by zero fixed */

    char data = 10;
    char *ptr = &data;
    *ptr = 10;             /* Violation 8: NULL pointer dereference fixed */
}

void pointerMisuse(void)
{
    int a = 10;
    int *p = &a;

    /* free(p); */               /* Violation 9: Freeing stack memory fixed */
    (void)p;                     /* To avoid unused variable warning */
}

void implicitConversion(void)
{
    int a = 300;
    char b = (char)a;            /* Violation 10: Implicit narrowing conversion fixed */
    (void)b;
}

void magicNumber(void)
{
    int x = ANSWER_TO_LIFE;      /* Violation 11: Magic number usage fixed */
    (void)x;
}

void unusedVariable(void)
{
    /* int x = 5; */             /* Violation 12: Unused variable fixed */
}

void recursionFunction(int n)
{
    /* Violation 13: Recursion in embedded system fixed by using iteration */
    int i;
    for(i = n; i > 0; i--)
    {
        /* Do something */
    }
}

void multipleReturn(int a)
{
    /* Refactor to single exit point */
    (void)a;
    /* ... */
    return;
}

void noConstUsage(void)
{
    int x = 10;
    const int *p = &x;           /* Violation 15: Pointer should be const fixed */
    (void)p;
}

void dangerousCast(void)
{
    float f = 10.5F;
    /* int *p = (int*)&f; */     /* Violation 16: Dangerous type casting fixed */
    (void)f;
}

void uninitializedPointer(void)
{
    int value = 5;
    int *p = &value;
    *p = 5;                      /* Violation 17: Use of uninitialized pointer fixed */
}

void deadCode(void)
{
    return;
    /* int x = 5; */             /* Violation 18: Dead code fixed */
}

void noDefaultSwitch(int x)
{
    switch(x)
    {
        case 1:
            break;
        case 2:
            break;
        default:
            break;
    }
}

void undeclaredFunction(void);   /* Violation 20: Function used without declaration fixed */

void functionWithoutPrototype(void)
{
    undeclaredFunction();
}

void undeclaredFunction(void)
{
    /* Implementation */
}

void volatileMissing(void)
{
    volatile int flag = 0;       /* Violation 21: Missing volatile for shared variable fixed */

    while(flag == 0)
    {
        /* wait */
    }
}

int main(void)
{
    unsafeFunction();
    pointerMisuse();
    implicitConversion();
    magicNumber();
    unusedVariable();
    recursionFunction(5);
    multipleReturn(1);
    noConstUsage();
    dangerousCast();
    uninitializedPointer();
    deadCode();
    noDefaultSwitch(1);
    functionWithoutPrototype();
    volatileMissing();

    return 0;
}
