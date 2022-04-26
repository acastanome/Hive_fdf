/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:40 by acastano          #+#    #+#             */
/*   Updated: 2022/04/26 16:19:41 by acastano         ###   ########.fr       */
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
	else
	{
		ft_putnbr(keysym);
		ft_putstr(" ");
	}
	return (0);
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
	mlx_loop_hook(data.mlx, &render_map, &data);
	mlx_key_hook(data.win, key_action, &data);

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
