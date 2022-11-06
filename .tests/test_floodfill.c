#include "../include/filler.h"
#include "../libft/include/libft.h"

int main(void)
{
	t_data		test_data;
	char		*ptr;
	t_dintarr	*source = NULL;
	t_dintarr	*filled;

	test_data.player = 'x';
	ft_getline(0, &test_data.temp);
	init_data(&test_data);
	can_read_board(&test_data);
	ptr = test_data.oboard_ptr;
	while (*ptr != 1)
		ptr++;
	ft_dintarr_add(&source, ptr - test_data.oboard_ptr);
	filled = floodfill(test_data.oboard_ptr, source, 0, 100);
	for (size_t i = 0; i < filled->len; i++)
		test_data.oboard_ptr[filled->arr[i]] = 2;
	debug_print(test_data.oboard_ptr, test_data.width, test_data.height);
	clean_exit(&test_data, "Done", 0);
}
