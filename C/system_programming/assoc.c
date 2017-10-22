#include <stdio.h>

int main(void)
{
	double x = 0.1 + (0.2 + 0.3);
	double y = (0.1 + 0.2) + 0.3;
	double v = 0.1 * (0.2 * 0.3);
	double w = (0.1 * 0.2) * 0.3;

	printf("0.1 + (0.2 + 0.3) == %lf\n", x);
	printf("(0.1 + 0.2) + 0.3 == %lf\n", y);
	printf("x == y ? %d\n", x==y);
	printf("x - y = %lf\n", x-y);

	printf("0.1 * (0.2 * 0.3) == %lf\n", v);
	printf("(0.1 * 0.2) * 0.3 == %lf\n", w);
	printf("v == w ? %d\n", v==w);
	printf("v - w = %lf\n", v-w);

	return 0;
}
