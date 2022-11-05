#include "../include/filler.h"

int main(void)
{
	t_data	test_data;

	test_data.player = 'x';
	ft_getline(0, &test_data.temp);
	init_data(&test_data);
	can_read_board(&test_data);
}
