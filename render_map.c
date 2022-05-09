/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:33:14 by acastano          #+#    #+#             */
/*   Updated: 2022/05/09 18:31:33 by acastano         ###   ########.fr       */
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
	data->img_addr = mlx_get_data_addr(data->img, &data->px_bits, &data->line_bytes, &data->endian);
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
			if (((data->y0 + 1) < data->n_rows) && (data->x0 < data->rows_width[data->y0 + 1]))
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

/*
 * transform() modifies the starting and ending points of the line to draw from
 * TOP to the requested projection
 */
void	transform(t_data *data)
{
	int	tempRx0;
	int	tempRy0;
	int	tempRx1;
	int	tempRy1;

	if (data->proj == ISO)
	{
		tempRx0 = (data->Rx0 - data->Ry0) * COS_30;
		tempRy0 = -data->z0 + (data->Rx0 + data->Ry0) * SIN_30;
		tempRx1 = (data->Rx1 - data->Ry1) * COS_30;
		tempRy1 = -data->z1 + (data->Rx1 + data->Ry1) * SIN_30;
	}
	else if (data->proj == FRONT)
	{
		tempRx0 = data->Rx0;
		tempRy0 = -(data->z0);
		tempRx1 = data->Rx1;
		tempRy1 = -(data->z1);
	}
	else// if (data->proj == BIMETRIC)
	{
		tempRx0 = (data->Rx0 - data->Ry0) * COS_60;
		tempRy0 = -data->z0 + (data->Rx0 + data->Ry0) * SIN_30;
		tempRx1 = (data->Rx1 - data->Ry1) * COS_60;
		tempRy1 = -data->z1 + (data->Rx1 + data->Ry1) * SIN_30;
	}
	data->Rx0 = tempRx0;
	data->Ry0 = tempRy0;
	data->Rx1 = tempRx1;
	data->Ry1 = tempRy1;
}

static void	render_text(t_data *data)
{
	if (data->win != NULL)
    {
		mlx_string_put(data->mlx, data->win, WIN_WIDTH - 350, 20, WHITE_PIXEL, "MOUSE INSTRUCTIONS");
		mlx_string_put(data->mlx, data->win, WIN_WIDTH - 350, 40, WHITE_PIXEL, "Wheel up: Increase height");
		mlx_string_put(data->mlx, data->win, WIN_WIDTH - 350, 60, WHITE_PIXEL, "Wheel down: Decrease height");
		mlx_string_put(data->mlx, data->win, 50, 20, WHITE_PIXEL, "KEYBOARD INSTRUCTIONS");
		mlx_string_put(data->mlx, data->win, 50, 40, WHITE_PIXEL, "Arrows Up, Down, Left and Right: Move view inside window");
		mlx_string_put(data->mlx, data->win, 50, 60, WHITE_PIXEL, "F: Front view");
		mlx_string_put(data->mlx, data->win, 50, 80, WHITE_PIXEL, "T: Top view");
		mlx_string_put(data->mlx, data->win, 50, 100, WHITE_PIXEL, "I: Isometric view");
		mlx_string_put(data->mlx, data->win, 50, 120, WHITE_PIXEL, "B: Bimetric view");
		mlx_string_put(data->mlx, data->win, 50, 140, WHITE_PIXEL, "Esc: Exit");
    }
}
