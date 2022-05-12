/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:40 by acastano          #+#    #+#             */
/*   Updated: 2022/05/12 18:58:44 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_action(int keysym, t_data *data);
static int	mouse_hook(int button, int x, int y, t_data *data);

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
	mlx_key_hook(data.win, key_action, &data);
	mlx_hook(data.win, 4, 0, mouse_hook, &data);
	mlx_hook(data.win, ON_DESTROY_X11, 0, exit_fdf, &data);
	mlx_loop(data.mlx);
	return (0);
}

void	initialize_data(t_data *data)
{
	data->colour = WHITE;
	data->proj = TOP;
	data->offset_x = 600;
	data->dist = (WIN_WIDTH - data->offset_x) / data->rows_width_max;
	data->offset_y = (WIN_HEIGHT - (data->n_rows * data->dist)) / 2;
	data->h_extra = 1;
}

static int	key_action(int keysym, t_data *data)
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
		data->dist = data->dist * 2;
	if ((keysym == KEY_MINUS || keysym == 27) && data->dist >= 2)
		data->dist = data->dist / 2;
	if (keysym == KEY_R)
		initialize_data(data);
	return (render(data));
}

static int	mouse_hook(int button, int x, int y, t_data *data)
{
	if (button == 4 && x && y)
		data->h_extra = data->h_extra + 0.1;
	if (button == 5)
		data->h_extra = data->h_extra - 0.1;
	if (button == 1)
	{
		if (data->colour != 0x0000ff)
			data->colour = data->colour >> 8;
		else
			data->colour = WHITE;
	}
	if (button == 2)
	{
		if (data->colour != 0xff0000)
			data->colour = (data->colour & 0x00ffff) << 8;
		else
			data->colour = WHITE;
	}
	if (button == 1 || button == 2 || button == 4 || button == 5)
		render(data);
	return (0);
}
