#include <stdio.h>
#include <stdbool.h>

void show_bytes(void *ptr, size_t size);
bool is_litend();

int main(void)
{
	int x = 123;
	printf("int x = 0x%.*x (address: %p)\n",
			(int)(2*sizeof(int)), x, &x);
	show_bytes(&x, sizeof(x));
	if (is_litend())
	{
		puts("It is little-endian.");
	}
	else
	{
		puts("It is big-endian.");
	}

	return 0;
}

void show_bytes(void *ptr, size_t size)
{
	unsigned char *end = (unsigned char *)ptr + size;
	unsigned char *byte = (unsigned char *)ptr;
	while (byte < end)
	{
		printf("%p\t0x%.2x\n", byte, *byte);
		byte++;
	}
}
bool is_litend()
{
	int x = 1;
	return *(unsigned char *)&x == x;
}
