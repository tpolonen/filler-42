#include "../include/filler.h"
#include "../libft/include/libft.h"

int main(void)
{
	t_data		*test_data;
	t_dintarr	*source = NULL;
	t_dintarr	*shape = get_enemy_shape();
	t_dintarr	*filled;

	test_data = get_data();
	test_data->player = 'x';
	init_data(test_data);
	printf("board width = %d, height = %d\n", test_data->width, test_data->height);
	ft_getline(0, &test_data->temp);
	printf("buffer contents: %s\n", test_data->temp);
	while (ft_strncmp(test_data->temp, "000", 3) != 0)
	{
		ft_memdel((void **)&test_data->temp);
		ft_getline(0, &(test_data->temp));
	}
	printf("buffer contents: %s\n", test_data->temp);
	can_read_board(test_data, shape);
	printf("shape->len = %zu, shape->arr = %p\n", shape->len, shape->arr);
	for (size_t i = 0; i < shape->len; i++)
	{
		printf("%2zu/%zu = %d\n", i + 1, shape->len, shape->arr[i]);
	}
	ft_dintarr_add(&source, shape->arr[0]);
	filled = floodfill(&source, test_data->oboard_ptr, 1, 50);
	for (size_t i = 0; i < filled->len; i++)
		test_data->oboard_ptr[filled->arr[i]] = '2';
	debug_print(test_data->oboard_ptr, test_data->width, test_data->height);
	clean_exit(test_data, "Done", 0);
}
