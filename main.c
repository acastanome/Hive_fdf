/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:40 by acastano          #+#    #+#             */
/*   Updated: 2022/05/10 11:24:07 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int key_action(int keysym, t_data *data)
{
	if (keysym > 2 && keysym < 130)
	{
		if (keysym == KEY_ESC_MAC || keysym == KEY_ESC_LINUX)
			exit (0);
		if (keysym == KEY_T)
			data->proj = TOP;
		if (keysym == KEY_F)
			data->proj = FRONT;
		if (keysym == KEY_I)
			data->proj = ISO;
		if (keysym == KEY_B)
			data->proj = BIMETRIC;
		if (keysym == KEY_ARROW_LEFT)
			data->offset_x = data->offset_x - data->dist;
		if (keysym == KEY_ARROW_RIGHT)
			data->offset_x = data->offset_x + data->dist;
		if (keysym == KEY_ARROW_TOP)
			data->offset_y = data->offset_y - data->dist;
		if (keysym == KEY_ARROW_DOWN)
			data->offset_y = data->offset_y + data->dist;
		if ((keysym == KEY_PLUS || keysym == 24) && data->dist < 5000)
			data->dist = data->dist + 10;
		if ((keysym == KEY_MINUS || keysym == 27) && data->dist >= 10)
			data->dist = data->dist - 10;
		if (keysym == KEY_R)
			initialize_data(data);
		render(data);
	}
	else
	{
		ft_putnbr(keysym);
		ft_putstr(" ");
	}
	return (0);
}

static int mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 4 && x && y)
	{
		data->h_extra = data->h_extra + 0.1;
		render(data);
	}
	if (button == 5)
	{
		data->h_extra = data->h_extra - 0.1;
		render(data);
	}
	return (0);
}

void	initialize_data(t_data *data)
{
	data->dist = WIN_WIDTH / data->rows_width_max;
	data->offset = 	WIN_WIDTH - (data->dist * data->rows_width_max);
	data->offset_x = 0;
	data->offset_y = 0;
	data->h_extra = 1;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		exit_fdf("usage: ./fdf <filename>\n");
	read_file(argv[1], &data);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		exit_fdf("Error: mlx_init() failed.\n");
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Al's fdf");
	if (data.win == NULL)
		exit_fdf("mlx_new_window() failed.\n");
	initialize_data(&data);
	render(&data);
//	mlx_loop_hook(data.mlx, &render, &data);
//	mlx_loop_hook(data.mlx, &render_map, &data);
//	mlx_hook(data.win, 4, 0, key_hook, &data);
	mlx_key_hook(data.win, key_action, &data);
	mlx_hook(data.win, 4, 0, mouse_hook, &data);
//	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_hook(data.win, ON_DESTROY_X11, 0, exit_fdf, &data);
	mlx_loop(data.mlx);

/*test printing
	int j;
	data.i = 0;
	while (data.i < data.n_rows)
	{
		j = 0;
		while (j < data.rows_width[data.i])
		{
			printf("%d\t", data.map[data.i][j]);
			j++;
		}
		printf("\n");
		data.i++;
	}
*/
	return (0);
}
