/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:40 by acastano          #+#    #+#             */
/*   Updated: 2022/04/29 15:35:07 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>//printf

//if (keysym == XK_Escape)//65307)Esc keycode
//123 arrow left, 124 arrow right, 125 arrow down, 126 arrow up
static int key_action(int keysym, t_data *data)
{
	if (keysym == 53 || keysym == 65307)
		exit (0);
	if (keysym == 17)
		data->projection = TOP;
	if (keysym == 3)
		data->projection = FRONT;
	if (keysym == 34)
		data->projection = ISO;
	if (keysym == 123)
	{
		data->offset_x = data->offset_x - 10;
	}
	if (keysym == 124)
	{
		data->offset_x = data->offset_x + 10;
	}
	if (keysym == 126)
	{
		data->offset_y = data->offset_y - 10;
	}
	if (keysym == 125)
	{
		data->offset_y = data->offset_y + 10;
	}
	if (keysym == 15)//R
	{
		initialize_data(data);
	}
	else
	{
		ft_putnbr(keysym);
		ft_putstr(" ");
	}
	return (0);
}

/*static int mouse_hook(int button, int x, int y, t_data *data)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
	{
		if (button == 1 && data)
		{
			printf("Mouse left click. x is %d and y i s%d\n", x, y);
		}
	}
	return (0);
	}*/

void	initialize_data(t_data *data)
{
	data->offset = 200;
	data->dist = 50;
	data->offset_x = 0;
	data->offset_y = 0;
//	data->offset_x = data->offset + data->offset_x;
//	data->offset_y = data->offset + data->offset_y;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		errors("usage: ./fdf <filename>\n");
	read_file(argv[1], &data);
	data.mlx = mlx_init();
	if (data.mlx == NULL)
		errors("Error: mlx_init() failed.\n");
	data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "Al's fdf");
	if (data.win == NULL)
		errors("mlx_new_window() failed.\n");
	initialize_data(&data);
	mlx_loop_hook(data.mlx, &render_map, &data);
//	mlx_hook(data.win, 4, 0, key_hook, &data);
	mlx_key_hook(data.win, key_action, &data);
//	mlx_hook(data.win, 4, 0, mouse_hook, &data);
//	mlx_mouse_hook(data.win, mouse_hook, &data);

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
