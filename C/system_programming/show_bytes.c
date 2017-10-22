#include <stdio.h>
#include <stdbool.h>

void show_bytes(void *ptr, size_t size);
bool is_litend();

int main(void)
{
	int x = 123;
	show_bytes(&x, sizeof(x));
	printf("%d\n", is_litend());

	return 0;
}

void show_bytes(void *ptr, size_t size)
{
	unsigned char *end = (unsigned char*)ptr + size;
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
