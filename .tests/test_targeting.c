#include "../include/filler.h"
#include "../libft/include/libft.h"

int main(void)
{
	t_data		*test_data;
	t_dintarr	*shape = get_enemy_shape();
	t_values	*values;
	t_strat		*strat = get_strat();
	char		*output;
	char		*combined_board;
	size_t		board_size;

	test_data = get_data();
	printf("Enter when ready...\n");
	getchar();
	printf("GO!\n");
	test_data->player = 'x';
	init_data(test_data);
	ft_getline(0, &test_data->temp);
	while (ft_strncmp(test_data->temp, "000", 3) != 0)
	{
		ft_memdel((void **)&test_data->temp);
		ft_getline(0, &(test_data->temp));
	}
	can_read_board(test_data, shape);
	board_size = get_data()->width * get_data()->height;
	combined_board = (char *)xalloc(board_size);
	for (size_t i = 0; i < board_size; i++)
		combined_board[i] = (strat->enemy[i] | strat->player[i]) != 0;
	values = get_values(combined_board, shape);
	output = xalloc(board_size);
	for (size_t i = 0; i < shape->len; i++)
		output[shape->arr[i]] = '0' + (char)values->arr[i];
	ft_memdel((void **)&values->arr);
	find_new_target(strat);
	for (size_t i = 0; i < strat->target->len; i++)
		output[strat->target->arr[i]] = 'T';
	ft_putendl("Result:");
	debug_print(output, test_data->width, test_data->height);
	clean_exit(test_data, "Done", 0);
}
