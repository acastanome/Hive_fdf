/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:49 by acastano          #+#    #+#             */
/*   Updated: 2022/05/05 19:49:52 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>//printf

int	scale_rgb(float scale);
float	calc_colour(t_data *data, float h);
//int	calculate_colour(float colour_percent);
//static int	rgb_toi(float r, float g, float b);
int	point_height_colour(t_data *data);
static int	img_pixel_put(t_data *data, int Rx, int Ry, int colour);

/*
 * draw_line() transforms the starting and ending points of the line to draw into
 * the requested projection, and checks if said points are inside the window
 * before calling bresenham_line_algo() to draw it
 */
void	draw_line(t_data *data, char direction, int x1, int y1)
{
	data->x1 = x1;
	data->y1 = y1;
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
	if (direction == 'h')
		data->BC = data->Rx1 - data->Rx0;
	if (direction == 'v')
		data->BC = data->Ry1 - data->Ry0;
//	if (data->projection == ISO)
//		transform_iso(data);
//	if (data->projection == FRONT)
//		transform_front(data);
	if (data->projection == ISO || data->projection == FRONT || data->projection == BIMETRIC)
		transform(data);
	if ((!(data->Rx0 <= 0 && data->Rx1 <= 0) || !(data->Rx0 >= WIN_WIDTH && data->Rx1 >= WIN_WIDTH))
		&& (!(data->Ry0 <= 0 && data->Ry1 <= 0) || !(data->Ry0 >= WIN_HEIGHT && data->Ry1 >= WIN_HEIGHT)))
		bresenham_line_algo(data);
}

/*
 * bresenham_line_algo() calculates the pixels that need to be rendered to draw
 * a line from (x0, y0) to (x1, y1), on the window defined in data.
 * Works in all octants.
 */
int	bresenham_line_algo(t_data *data)
{
	int	sx;
	int	sy;
	int	error;
	int	e2;

	data->dx = abs(data->Rx1 - data->Rx0);
	if (data->Rx0 < data->Rx1)
		sx = 1;
	else sx = -1;
	data->dy = abs(data->Ry1 - data->Ry0);
	if (data->Ry0 < data->Ry1)
		sy = 1;
	else sy = -1;
	error = data->dx - data->dy;
	while (1)
	{
//		mlx_pixel_put(data->mlx, data->win, data->Rx0 + data->offset + data->offset_x, data->Ry0 + data->offset + data->offset_y, RED_PIXEL);
		img_pixel_put(data, data->Rx0 + data->offset + data->offset_x, data->Ry0 + data->offset + data->offset_y, RED_PIXEL);
		if (data->Rx0 == data->Rx1 && data->Ry0 == data->Ry1)
			break;
		e2 = 2 * error;
		if (e2 > -data->dy)//took >= away
		{
			if (data->Rx0 == data->Rx1)
				break;
			error = error - data->dy;
			data->Rx0 = data->Rx0 + sx;
		}
		if (e2 < data->dx)//took <= away
		{
			if (data->Ry0 == data->Ry1)
				break;
			error = error + data->dx;
			data->Ry0 = data->Ry0 + sy;
		}
	}
	return (0);
}

static int	img_pixel_put(t_data *data, int Rx, int Ry, int colour)
{
	char	*image;

	if (data->px_bits != 32)
		mlx_get_color_value(data->mlx, colour);
//	mlx_pixel_put(data->mlx, data->win, data->Rx0 + data->offset + data->offset_x, data->Ry0 + data->offset + data->offset_y, RED_PIXEL);
	if ((Rx >= 0 && Rx < WIN_WIDTH) && (Ry >= 0 && Ry < WIN_HEIGHT))
	{
		image = data->img_addr + (Rx * (data->px_bits / 8)) + (Ry * data->line_bytes);
		//data->img_addr;//IMG_ADR
		if (image == NULL)
			exit_fdf("img_pixel_put() failed to allocate image pixel.\n");
		*(unsigned int *)image = colour;
	}
	return (0);
}

/*
 * point_height() uses linear equation to calculate the height at any point of
 * a line. Then calls calc_colour() with that height to get the colour the pixels
 * should have.
 */
int	point_height_colour(t_data *data)
{
	float	h;
	float	h0;
	float	h1;

	h0 = data->map[data->y0][data->x0];
	h1 = data->map[data->y1][data->x1];
	if (h0 == h1)
		h = h0;
	else
	{
		if (h0 < h1)
		{
			if (data->y1 == data->y0)
				data->DC = data->Rx0 - data->x0 * data->dist;
//				data->DC = data->Rx0 - (data->x0 * data->dist + data->offset);
			else
				data->DC = data->Ry0 - data->y0 * data->dist;
//				data->DC = data->Ry0 - (data->y0 * data->dist + data->offset);
			h = (h1 * data->DC) / data->BC;
		}
		else
		{
			if (data->y1 == data->y0)
				data->DC = data->x1 * data->dist - data->Rx0;
//				data->DC = (data->x1 * data->dist + data->offset) - data->Rx0;
			else
				data->DC = data->y1 * data->dist - data->Ry0;
//				data->DC = (data->y1 * data->dist + data->offset) - data->Ry0;
			h = (h0 * data->DC) / data->BC;
		}
	}
	return (calc_colour(data, h));
}

float	calc_colour(t_data *data, float h)
{
	float	colour_perc;
	int		colour;

	if (h == 0)
		colour = WHITE_PIXEL;
	else
	{
		colour_perc = (h - data->h_min) / (data->h_max - data->h_min);//0 30 100 0.3 - 30 65 100 - 30 50 230
		colour = scale_rgb(colour_perc);
	}
	return (colour);
}

int	scale_rgb(float percent)
{
	int	rgb_percent;
	int	rgb;

	rgb_percent = percent * 255;
	rgb = ((rgb_percent & 0x0ff) << 16);
	rgb |= ((rgb_percent & 0x0ff) << 8);
	rgb |= (rgb_percent & 0x0ff);
	return rgb;
}

/*
static int	rgb_toi(float r, float g, float b)
{
	int	rgb;

	rgb = (((r * 255) & 0x0ff) << 16);
	rgb |= (((g * 255) & 0x0ff) << 8);
	rgb |= ((b * 255) & 0x0ff);
	return rgb;
}
 */

/*
Works for octant 0, that is lines with slope between 0 and 1.
int	bresenham_line_algo(int x0, int y0, int x1, int y1, t_data *data)
{
  int	dx = x1 - x0;
  int	dy = y1 - y0;
  int	D = 2 * dy - dx;
  int	y = y0;

  while (x0 <= x1)
    {
      mlx_pixel_put(data->mlx, data->win, x0, y, GREEN_PIXEL);
      if (D >= 0)
	{
	  y = y + 1;
	  D = D + 2 * dy - 2 * dx;
	}
      else (D = D + 2 * dy);
      x0++;
    }
  return (0);
}

 */
