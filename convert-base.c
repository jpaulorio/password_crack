#include <stdio.h>
#include <stdlib.h>

int skip(int a[], unsigned long length, int base){

	unsigned long m = length;
	unsigned long n = base;
	unsigned long s = 0;
	int count = 0;

	printf("m->%d\n", m);
	printf("n->%d\n", n);

	while (m >= n) {
		s = m % n;
		a[count] = s;
		m = m / n;
		count++;
	}
	a[count] = m;

	return 0;
}

int main() {
	int a[5];
	for (int i = 0; i < 5; i++) {
		a[i] = 0;
	}
	printf("%d %d %d %d %d\n", a[0], a[1], a[2], a[3], a[4]);
	skip(a, 268435455, 128);
	printf("%d %d %d %d %d\n", a[0], a[1], a[2], a[3], a[4]);
}