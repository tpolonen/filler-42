#include "../include/filler.h"
#include "../libft/include/libft.h"

int main(void)
{
	t_data		*test_data;
	t_dintarr	*shape = get_enemy_shape();
	int			*values;
	t_strat		*strat = get_strat();

	test_data = get_data();
	printf("Enter when ready...\n");
	getchar();
	printf("GO!\n");
	test_data->player = 'x';
	init_data(test_data);
	ft_getline(0, &test_data->temp);
	printf("shape len = %zu, alloced = %zu\n", shape->len, shape->alloced);
	while (ft_strncmp(test_data->temp, "000", 3) != 0)
	{
		ft_memdel((void **)&test_data->temp);
		ft_getline(0, &(test_data->temp));
	}
	can_read_board(test_data, shape);
	printf("shape->len = %zu, shape->arr = %p\n", shape->len, shape->arr);
	for (size_t i = 0; i < shape->len; i++)
	{
		printf("%2zu/%zu = %d\n", i, shape->len, shape->arr[i]);
	}
	values = get_values(test_data->oboard_ptr, shape);
	for (size_t i = 0; i < shape->len; i++)
		test_data->oboard_ptr[shape->arr[i]] = '0' + (char)values[i];
	find_new_target(strat);
	for (size_t i = 0; i < strat->target->len; i++)
		test_data->oboard_ptr[strat->target->arr[i]] = 'T';
	debug_print(test_data->oboard_ptr, test_data->width, test_data->height);
	clean_exit(test_data, "Done", 0);
}
