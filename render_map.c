/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:33:14 by acastano          #+#    #+#             */
/*   Updated: 2022/05/05 19:57:13 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	render_text(t_data *data);
//static void	draw_horizontal_line(t_data *data);
//static void	draw_vertical_line(t_data *data);

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

int	render_map(t_data *data)
{
	if (data->win != NULL)
    {
		data->y0 = 0;
		while (data->y0 < data->n_rows)
		{
			data->x0 = 0;
			while (data->x0 < data->rows_width[data->y0])
			{
				if ((data->x0 + 1) < data->rows_width[data->y0])
					draw_line(data, 'h', (data->x0 + 1), data->y0);
//					draw_horizontal_line(data);
				if (((data->y0 + 1) < data->n_rows) && (data->x0 < data->rows_width[data->y0 + 1]))
					draw_line(data, 'v', data->x0, (data->y0 + 1));
//					draw_vertical_line(data);
				data->x0++;
			}
			data->y0++;
		}
	}
//	render_text(data);
	return (0);
}

/*static void	draw_horizontal_line(t_data *data)
{
	data->x1 = data->x0 + 1;
	data->y1 = data->y0;
	data->Rx0 = data->x0 * data->dist;
	data->Ry0 = data->y0 * data->dist;
	data->Rx1 = data->x1 * data->dist;
	data->Ry1 = data->y1 * data->dist;

	data->z0 = data->map[data->y0][data->x0];
	if (data->z0 != 0)
		data->z0 = (data->z0 * data->h_extra) * data->dist;
	data->z1 = data->map[data->y1][data->x1];
	if (data->z1 != 0)
		data->z1 = (data->z1 * data->h_extra) * data->dist;

	data->BC = data->Rx1 - data->Rx0;
	draw_line(data);
}

static void	draw_vertical_line(t_data *data)
{
	data->x1 = data->x0;
	data->y1 = data->y0 + 1;
	data->Rx0 = data->x0 * data->dist;
	data->Ry0 = data->y0 * data->dist;
	data->Rx1 = data->x1 * data->dist;
	data->Ry1 = data->y1 * data->dist;

	data->z0 = data->map[data->y0][data->x0];
	if (data->z0 != 0)
		data->z0 = (data->z0 * data->h_extra) * data->dist;
	data->z1 = data->map[data->y1][data->x1];
	if (data->z1 != 0)
		data->z1 = (data->z1 * data->h_extra) * data->dist;

	data->BC = data->Ry1 - data->Ry0;
	draw_line(data);
	}*/

void	transform(t_data *data)
{
	int	tempRx0;
	int	tempRy0;
	int	tempRx1;
	int	tempRy1;

	if (data->projection == ISO)
	{
		tempRx0 = (data->Rx0 - data->Ry0) * COS_30;
		tempRy0 = -data->z0 + (data->Rx0 + data->Ry0) * SIN_30;
		tempRx1 = (data->Rx1 - data->Ry1) * COS_30;
		tempRy1 = -data->z1 + (data->Rx1 + data->Ry1) * SIN_30;
	}
	else if (data->projection == FRONT)
	{
		tempRx0 = data->Rx0;
		tempRy0 = -(data->z0);
		tempRx1 = data->Rx1;
		tempRy1 = -(data->z1);
	}
	else// if (data->projection == BIMETRIC)
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

/*void	transform_iso(t_data *data)
{
	int	tempRx0;
	int	tempRy0;
	int	tempRx1;
	int	tempRy1;

	tempRx0 = (data->Rx0 - data->Ry0) * COS_30;
	tempRy0 = -data->z0 + (data->Rx0 + data->Ry0) * SIN_30;
	tempRx1 = (data->Rx1 - data->Ry1) * COS_30;
	tempRy1 = -data->z1 + (data->Rx1 + data->Ry1) * SIN_30;

	data->Rx0 = tempRx0;
	data->Ry0 = tempRy0;
	data->Rx1 = tempRx1;
	data->Ry1 = tempRy1;
}

void	transform_front(t_data *data)
{
	int	tempRx0;
	int	tempRy0;
	int	tempRx1;
	int	tempRy1;

	tempRx0 = data->Rx0;
	tempRy0 = -(data->z0);
	tempRx1 = data->Rx1;
	tempRy1 = -(data->z1);

	data->Rx0 = tempRx0;
	data->Ry0 = tempRy0;
	data->Rx1 = tempRx1;
	data->Ry1 = tempRy1;
	}*/

/*
 * 30 degrees = 0.523598776 rad
 * ptr->x = (x - y) * cos(30)
 * ptr->y = -z + (x + y) * sin(30)
 */

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
