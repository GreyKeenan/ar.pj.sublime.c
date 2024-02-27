
#include <stdio.h>

typedef struct I {
	int m;
} I;

typedef struct A {
	I i;
	int x;
	int y;
} A;

typedef struct B {
	I i;
	int x;
	int y;
} B;


typedef union U {
	I i;
	A a;
	B b;
} U;


int main() {

	A myA = { .i.m = 10, .x=3, .y=6 };

	U *ptr = (U *)&myA;

	printf("%d\n", ptr->a.x);

	return 0;
}

