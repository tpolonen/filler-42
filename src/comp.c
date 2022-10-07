#include "filler.h"

int comp1(char *ptr1, char *ptr2, size_t n)
{
	while (n-- > 0)
	{
		if (ptr1[n] & ptr2[n])
			return (1);
	}
	return (0);
}

int comp2(char *ptr1, char *ptr2, size_t n)
{
	void	*p1;
	void	*p2;

	p1 = ptr1;
	p2 = ptr2;
	while (n >= sizeof(long long) && !(*(long long *)p1 & *(long long *)p2))
	{
		p1 += sizeof(long long);
		p2 += sizeof(long long);
		n -= sizeof(long long);
	}
	while (n >= sizeof(int) && !(*(int *)p1 & *(int *)p2))
	{
		p1 += sizeof(int);
		p2 += sizeof(int);
		n -= sizeof(int);
	}
	return (comp1((char *)p1, (char *)p2, n));
}

int comp(char *ptr1, char *ptr2, size_t n)
{
	if (n > sizeof(long long))
		return (comp2(ptr1, ptr2, n));
	return (comp1(ptr1, ptr2, n));
}
