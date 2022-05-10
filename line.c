/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:49 by acastano          #+#    #+#             */
/*   Updated: 2022/05/10 12:01:20 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line(t_data *data, char direction);
static void	bresenham_line_algo_setup(t_data *data);
static void	bresenham_line_algo(t_data *data);
void	transform(t_data *data);
static int	line_through_win(t_data *data);
static void	img_pixel_put(t_data *data, int Rx, int Ry, int colour);

/*
 * draw_line() calculates the starting and ending points of the line to draw,
 * calling transform() if the requested projection isn't (parallel) TOP.
 * Then checks if the line goes through/ is inside the window before calling
 * bresenham_line_algo() to draw it
 */
void	draw_line(t_data *data, char direction)
{
	data->Rx0 = data->x0 * data->dist;
	data->Ry0 = data->y0 * data->dist;
	data->Rx1 = data->x1 * data->dist;
	data->Ry1 = data->y1 * data->dist;
	data->z0 = data->map[data->y0][data->x0];
	if ((data->z0 != 0) && direction)//TO DO:useless dir
		data->z0 = (data->z0 * data->h_extra) * data->dist;
	data->z1 = data->map[data->y1][data->x1];
	if (data->z1 != 0)
		data->z1 = (data->z1 * data->h_extra) * data->dist;
/*	if (direction == 'h')
		data->BC = data->Rx1 - data->Rx0;
	else
		data->BC = data->Ry1 - data->Ry0;*/
	if (data->proj == ISO || data->proj == FRONT || data->proj == BIMETRIC)
		transform(data);
	if (line_through_win(data) == 1)
		bresenham_line_algo_setup(data);
}

/*
 * transform() modifies the starting and ending points of the line to draw from
 * TOP to the requested projection: Front, Iso, Bimetric
 */
void	transform(t_data *data)
{
	if (data->proj == FRONT)
	{
		data->tempRx0 = data->Rx0;
		data->tempRy0 = -(data->z0);
		data->tempRx1 = data->Rx1;
		data->tempRy1 = -(data->z1);
	}
	else
	{
		data->tempRx0 = (data->Rx0 - data->Ry0) * COS_30;
		data->tempRy0 = -data->z0 + (data->Rx0 + data->Ry0) * SIN_30;
		data->tempRx1 = (data->Rx1 - data->Ry1) * COS_30;
		data->tempRy1 = -data->z1 + (data->Rx1 + data->Ry1) * SIN_30;
		if (data->proj == BIMETRIC)
		{
			data->tempRx0 = (data->Rx0 - data->Ry0) * COS_60;
			data->tempRx1 = (data->Rx1 - data->Ry1) * COS_60;
		}
	}
	data->Rx0 = data->tempRx0;
	data->Ry0 = data->tempRy0;
	data->Rx1 = data->tempRx1;
	data->Ry1 = data->tempRy1;
}

int	line_through_win(t_data *data)
{
	data->Rx0 = data->Rx0 + data->offset_x + data->offset;
	data->Ry0 = data->Ry0 + data->offset_y + data->offset;
	data->Rx1 = data->Rx1 + data->offset_x + data->offset;
	data->Ry1 = data->Ry1 + data->offset_y + data->offset;

	if (((data->Rx0 <= 0) && (data->Rx1 <= 0))
		|| ((data->Rx0 >= WIN_WIDTH) && (data->Rx1 >= WIN_WIDTH))
		|| ((data->Ry0 <= 0) && (data->Ry1 <= 0))
		|| ((data->Ry0 >= WIN_HEIGHT) && (data->Ry1 >= WIN_HEIGHT)))
		return (0);
	return (1);
}

/*
 * bresenham_line_algo_setup() calculates the values the bresenham line algo
 * needs to before calling bresenham_line_algo() to calculate the line's pixels
 */
static void	bresenham_line_algo_setup(t_data *data)
{
	data->dx = abs(data->Rx1 - data->Rx0);
	if (data->Rx0 < data->Rx1)
		data->sx = 1;
	else data->sx = -1;
	data->dy = abs(data->Ry1 - data->Ry0);
	if (data->Ry0 < data->Ry1)
		data->sy = 1;
	else data->sy = -1;
	data->error = data->dx - data->dy;
	bresenham_line_algo(data);
}

/* ************************************************************************** */
/*
 * bresenham_line_algo() calculates the pixels that need to be rendered to draw
 * a line from (x0, y0) to (x1, y1), on the window (data->mlx_win). Then calls
 * img_pixel_put() to add them to an image (data->mlx_img).
 * Works in all octants.
 */
static void	bresenham_line_algo(t_data *data)
{
	while (1)
	{
		if ((data->Rx0 >= 0 && data->Rx0 < WIN_WIDTH)
			&& (data->Ry0 >= 0 && data->Ry0 < WIN_HEIGHT))
			img_pixel_put(data, data->Rx0, data->Ry0, RED_PIXEL);
		if (data->Rx0 == data->Rx1 && data->Ry0 == data->Ry1)
			break;
		data->e2 = 2 * data->error;
		if (data->e2 > -data->dy)//took >= away
		{
			if (data->Rx0 == data->Rx1)
				break;
			data->error = data->error - data->dy;
			data->Rx0 = data->Rx0 + data->sx;
		}
		if (data->e2 < data->dx)//took <= away
		{
			if (data->Ry0 == data->Ry1)
				break;
			data->error = data->error + data->dx;
			data->Ry0 = data->Ry0 + data->sy;
		}
	}
}

/*
 * img_pixel_put() adds the pixel (Rx, Ry), in the specified colour, to the
 * image saved in data.
 * Note: It is up to the user to check that the pixel fits in the image.
 */
static void	img_pixel_put(t_data *data, int Rx, int Ry, int colour)
{
	char	*image;

	if (data->px_bits != 32)
		mlx_get_color_value(data->mlx, colour);
	image = data->img_addr + (Rx * (data->px_bits / 8)) + (Ry * data->line_bytes);
	if (image == NULL)
		exit_fdf("img_pixel_put() failed to allocate image pixel.\n");
	*(unsigned int *)image = colour;
}
