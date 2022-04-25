/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:40 by acastano          #+#    #+#             */
/*   Updated: 2022/04/25 15:45:24 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>//printf

static int key_action(int keysym)//, t_data *data)
{
	if (keysym == 53 || keysym == 65307)//if (keysym == XK_Escape)//65307)Esc keycode
		exit (0);
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
