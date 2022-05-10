/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:33:14 by acastano          #+#    #+#             */
/*   Updated: 2022/05/10 12:02:17 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	render_text(t_data *data);
static void	render_map(t_data *data);

int	render(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (data->img == NULL)
		exit_fdf("mlx_new_image() failed.\n");
	data->img_addr = mlx_get_data_addr(data->img, &data->px_bits,
			&data->line_bytes, &data->endian);
	if (data->img_addr == NULL)
		exit_fdf("mlx_get_data_addr() failed.\n");	
	render_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	render_text(data);
	mlx_destroy_image(data->mlx, data->img);
	return (0);
}

static void	render_map(t_data *data)
{
	if (data->win == NULL)
		return ;
	data->y0 = 0;
	while (data->y0 < data->n_rows)
	{
		data->x0 = 0;
		while (data->x0 < data->rows_width[data->y0])
		{
			if ((data->x0 + 1) < data->rows_width[data->y0])
			{
				data->x1 = data->x0 + 1;
				data->y1 = data->y0;
				draw_line(data, 'h');
			}
			if (((data->y0 + 1) < data->n_rows)
				&& (data->x0 < data->rows_width[data->y0 + 1]))
			{
				data->x1 = data->x0;
				data->y1 = data->y0 + 1;
				draw_line(data, 'v');
			}
			data->x0++;
		}
		data->y0++;
	}
}

static void	render_text(t_data *data)
{
	if (data->win != NULL)
    {
		mlx_string_put(data->mlx, data->win, 125, 50, WHITE_PIXEL, "INSTRUCTIONS");
		mlx_string_put(data->mlx, data->win, 25, 90, WHITE_PIXEL, "Mouse wheel: Modify height");
		mlx_string_put(data->mlx, data->win, 25, 130, WHITE_PIXEL, "Keyboard");
		mlx_string_put(data->mlx, data->win, 50, 160, WHITE_PIXEL, "Arrows: Position inside window");
		mlx_string_put(data->mlx, data->win, 50, 180, WHITE_PIXEL, "F: Front view");
		mlx_string_put(data->mlx, data->win, 50, 200, WHITE_PIXEL, "T: Top view");
		mlx_string_put(data->mlx, data->win, 50, 220, WHITE_PIXEL, "I: Isometric view");
		mlx_string_put(data->mlx, data->win, 50, 240, WHITE_PIXEL, "B: Bimetric view");
		mlx_string_put(data->mlx, data->win, 50, 260, WHITE_PIXEL, "R: Reset view");
		mlx_string_put(data->mlx, data->win, 50, 290, WHITE_PIXEL, "Esc: Exit");
		mlx_string_put(data->mlx, data->win, 25, WIN_HEIGHT - 50, WHITE_PIXEL, "Bresenham line algorithm");
    }
}
/* ************************************************************************** */
