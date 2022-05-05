/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:40 by acastano          #+#    #+#             */
/*   Updated: 2022/05/05 19:46:56 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>//printf

//if (keysym == XK_Escape)//65307)Esc keycode
//123 arrow left, 124 arrow right, 125 arrow down, 126 arrow up
static int key_action(int keysym, t_data *data)
{
	if (keysym > 2 && keysym < 130)
	{
		if (keysym == 53 || keysym == 65307)
			exit (0);
		if (keysym == 17)//T
			data->projection = TOP;
		if (keysym == 3)//F
			data->projection = FRONT;
		if (keysym == 34)//I
			data->projection = ISO;
		if (keysym == 11)//B
			data->projection = BIMETRIC;
		if (keysym == 123)
			data->offset_x = data->offset_x - data->dist;
		if (keysym == 124)
			data->offset_x = data->offset_x + data->dist;
		if (keysym == 126)
			data->offset_y = data->offset_y - data->dist;
		if (keysym == 125)
			data->offset_y = data->offset_y + data->dist;
		if ((keysym == 69 || keysym == 24) && data->dist < 5000)//+
			data->dist = data->dist + 10;
		if ((keysym == 78 || keysym == 27) && data->dist >= 10)//-
			data->dist = data->dist - 10;
		if (keysym == 15)//R
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

//static void mouse_hook(int button, int x, int y, t_data *data)//up 4, down 5
static int mouse_hook(int button, int x, int y, t_data *data)//up 4, down 5
{
	if (button == 4 && x && y)
	{
		data->h_extra = data->h_extra + 0.1;
		render(data);
	}
//		printf("Mouse left click. x is %d and y i s%d\n", x, y);
	if (button == 5)
	{
		data->h_extra = data->h_extra - 0.1;
		render(data);
	}
/*	if (button == 1)
	{
		data->mouse_x = x;
		data->mouse_y = y;
		}*/
	return (0);
}

void	initialize_data(t_data *data)
{
	data->offset = 200;
	data->dist = 50;
	data->offset_x = 0;
	data->offset_y = 0;
	data->h_extra = 1;
//	data->offset_x = data->offset + data->offset_x;
//	data->offset_y = data->offset + data->offset_y;
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
	data.img = mlx_new_image(data.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (data.img == NULL)
		exit_fdf("mlx_new_image() failed.\n");
	data.img_addr = mlx_get_data_addr(data.img, &data.px_bits, &data.line_bytes, &data.endian);
	if (data.win == NULL)
		exit_fdf("mlx_get_data_addr() failed.\n");
	initialize_data(&data);
	render(&data);
//	mlx_loop_hook(data.mlx, &render, &data);
//	mlx_loop_hook(data.mlx, &render_map, &data);
//	mlx_hook(data.win, 4, 0, key_hook, &data);
	mlx_key_hook(data.win, key_action, &data);
	mlx_hook(data.win, 4, 0, mouse_hook, &data);
//	mlx_mouse_hook(data.win, mouse_hook, &data);
	mlx_hook(data.win, 17, 0, exit_fdf, &data);//ON_DESTROY X11
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
