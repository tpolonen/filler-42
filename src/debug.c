#include "filler.h"

void debug_print(char* ptr, int width, int height)
{
	int row;
	int col;

	row = 0;
	while (row < height)
	{
		col = 0;
		ft_putnbr(row);
		ft_putstr("\t");
		while (col < width)
		{
			if (ptr[(row * width) + col])
				ft_putchar('*');
			else
				ft_putchar('.');
			col++;
		}
		ft_putendl("");
		row++;
	}
}
