void foo(int *a, int *b, int *x)
{
	*a += *x;
	*b += *x;
	/*
	 * movl	(%rdx), %eax
	 * addl	%eax, (%rdi)
	 * movl	(%rdx), %eax
	 * addl	%eax, (%rsi)
	 */
}

void bar(int *restrict a, int *restrict b, int *restrict x)
{
	*a += *x;
	*b += *x;
	/*
	 * movl	(%rdx), %eax
	 * addl	%eax, (%rdi)
	 * addl	%eax, (%rsi)
	 */
}

/* The followings seem not to work properly. */

void mult_array(int *dest, int *src1, int *src2, unsigned n)
{
	for (unsigned i = 0; i < n; i++)
	{
		dest[i] = src1[i] * src2[i];
	}
}

void mult_array_res(int *restrict dest, int *restrict src1, int *restrict src2, unsigned n)
{
	for (unsigned i = 0; i < n; i++)
	{
		dest[i] = src1[i] * src2[i];
	}
}

void bang(char *p1, char *p2)
{
	for (int i = 0; i < 50; i++)
	{
		p1[i] = 4;
		p2[i] = 9;
	}
}
void spam(char *restrict p1, char *restrict p2)
{
	for (int i = 0; i < 50; i++)
	{
		p1[i] = 4;
		p2[i] = 9;
	}
}
