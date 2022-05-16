/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:49 by acastano          #+#    #+#             */
/*   Updated: 2022/05/16 20:39:28 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	transform(t_data *data);
static int	line_through_win(t_data *data);
static void	bresenham_line_algo_setup(t_data *data);
static void	bresenham_line_algo(t_data *data, t_bres *bres);

/*
 * draw_line() calculates the starting and ending points of the line to draw,
 * calling transform() if the requested projection isn't (parallel) TOP.
 * Then checks if the line goes through/ is inside the window before calling
 * bresenham_line_algo() to draw it
 */
void	draw_line(t_data *data)
{
	data->rx0 = data->x0 * data->dist;
	data->ry0 = data->y0 * data->dist;
	data->rx1 = data->x1 * data->dist;
	data->ry1 = data->y1 * data->dist;
	data->z0 = data->map[data->y0][data->x0];
	if (data->z0 != 0)
		data->z0 = (data->z0 * data->h_extra) * data->dist;
	data->z1 = data->map[data->y1][data->x1];
	if (data->z1 != 0)
		data->z1 = (data->z1 * data->h_extra) * data->dist;
	if (data->proj != TOP)
		transform(data);
	if (line_through_win(data) == 1)
		bresenham_line_algo_setup(data);
}

/*
 * transform() modifies the starting and ending points of the line to draw from
 * TOP to the requested projection: Front, Iso, Bimetric
 */
static void	transform(t_data *data)
{
	if (data->proj == FRONT)
	{
		data->temp_rx0 = data->rx0;
		data->temp_ry0 = -(data->z0);
		data->temp_rx1 = data->rx1;
		data->temp_ry1 = -(data->z1);
	}
	else
	{
		data->temp_rx0 = (data->rx0 - data->ry0) * COS_30;
		data->temp_ry0 = -data->z0 + (data->rx0 + data->ry0) * SIN_30;
		data->temp_rx1 = (data->rx1 - data->ry1) * COS_30;
		data->temp_ry1 = -data->z1 + (data->rx1 + data->ry1) * SIN_30;
		if (data->proj == BIMETRIC)
		{
			data->temp_rx0 = (data->rx0 - data->ry0) * COS_60;
			data->temp_rx1 = (data->rx1 - data->ry1) * COS_60;
		}
	}
	data->rx0 = data->temp_rx0;
	data->ry0 = data->temp_ry0;
	data->rx1 = data->temp_rx1;
	data->ry1 = data->temp_ry1;
}

/*
 * line_through_win() checks if a line crosses (or is in) the window, by
 * checking if the starting and ending points are at the same side of the
 * window.
 * Return values: 1 if it crosses, 0 if it doesn't
 */
static int	line_through_win(t_data *data)
{
	data->rx0 = data->rx0 + data->offset_x;
	data->ry0 = data->ry0 + data->offset_y;
	data->rx1 = data->rx1 + data->offset_x;
	data->ry1 = data->ry1 + data->offset_y;
	if (((data->rx0 <= 0) && (data->rx1 <= 0))
		|| ((data->rx0 >= WIN_WIDTH) && (data->rx1 >= WIN_WIDTH))
		|| ((data->ry0 <= 0) && (data->ry1 <= 0))
		|| ((data->ry0 >= WIN_HEIGHT) && (data->ry1 >= WIN_HEIGHT)))
		return (0);
	return (1);
}

/*
 * bresenham_line_algo_setup() calculates the values the bresenham line algo
 * needs to before calling bresenham_line_algo() to calculate the line's pixels
 */
static void	bresenham_line_algo_setup(t_data *data)
{
	t_bres	bres;

	bres.dx = abs(data->rx1 - data->rx0);
	if (data->rx0 < data->rx1)
		bres.sx = 1;
	else
		bres.sx = -1;
	bres.dy = abs(data->ry1 - data->ry0);
	if (data->ry0 < data->ry1)
		bres.sy = 1;
	else
		bres.sy = -1;
	bres.error = bres.dx - bres.dy;
	bresenham_line_algo(data, &bres);
}

/*
 * bresenham_line_algo() calculates the pixels that need to be rendered to draw
 * a line from (x0, y0) to (x1, y1), on the window (data->mlx_win). Then calls
 * img_pixel_put() to add them to an image (data->mlx_img).
 * Works in all octants.
 */
static void	bresenham_line_algo(t_data *data, t_bres *bres)
{
	while (1)
	{
		if ((data->rx0 >= 0 && data->rx0 < WIN_WIDTH)
			&& (data->ry0 >= 0 && data->ry0 < WIN_HEIGHT))
			img_pixel_put(data, data->rx0, data->ry0, colour(data));
		if (data->rx0 == data->rx1 && data->ry0 == data->ry1)
			break ;
		bres->e2 = 2 * bres->error;
		if (bres->e2 >= -bres->dy)
		{
			if (data->rx0 == data->rx1)
				break ;
			bres->error = bres->error - bres->dy;
			data->rx0 = data->rx0 + bres->sx;
		}
		if (bres->e2 <= bres->dx)
		{
			if (data->ry0 == data->ry1)
				break ;
			bres->error = bres->error + bres->dx;
			data->ry0 = data->ry0 + bres->sy;
		}
	}
}
