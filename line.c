/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:49 by acastano          #+#    #+#             */
/*   Updated: 2022/04/25 16:34:19 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdio.h>//printf

static int	scale_rgb(float scale);
static float	calc_colour(t_data *data, float h);
//int	calculate_colour(float colour_percent);
//static int	rgb_toi(float r, float g, float b);
static int	point_height_colour(t_data *data);

void	draw_line(t_data *data)
{
	data->Rx0 = (data->x0 * data->dist) + data->offset;
	data->Ry0 = (data->y0 * data->dist) + data->offset;
	data->Rx1 = (data->x1 * data->dist) + data->offset;
	data->Ry1 = (data->y1 * data->dist) + data->offset;

	if (data->y1 == data->y0)
		data->BC = data->Rx1 - data->Rx0;
	else
		data->BC = data->Ry1 - data->Ry0;
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
	data->dy = -abs(data->Ry1 - data->Ry0);
	if (data->Ry0 < data->Ry1)
		sy = 1;
	else sy = -1;
	error = data->dx + data->dy;
	while (1)
	{
		mlx_pixel_put(data->mlx, data->win, data->Rx0, data->Ry0, point_height_colour(data));
		if (data->Rx0 == data->Rx1 && data->Ry0 == data->Ry1)
			break;
		e2 = 2 * error;
		if (e2 >= data->dy)
		{
			if (data->Rx0 == data->Rx1)
				break;
			error = error + data->dy;
			data->Rx0 = data->Rx0 + sx;
		}
		if (e2 <= data->dx)
		{
			if (data->Ry0 == data->Ry1)
				break;
			error = error + data->dx;
			data->Ry0 = data->Ry0 + sy;
		}
	}
	return (0);
}

/*
 * point_height() uses linear equation to calculate the height at any point of
 * a line. Then calls calc_colour() with that height to get the colour the pixels
 * should have.
 */
static int	point_height_colour(t_data *data)
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
				data->DC = data->Rx0 - (data->x0 * data->dist + data->offset);
			else
				data->DC = data->Ry0 - (data->y0 * data->dist + data->offset);
			h = (h1 * data->DC) / data->BC;
		}
		else
		{
			if (data->y1 == data->y0)
				data->DC = (data->x1 * data->dist + data->offset) - data->Rx0;
			else
				data->DC = (data->y1 * data->dist + data->offset) - data->Ry0;
			h = (h0 * data->DC) / data->BC;
		}
	}
	return (calc_colour(data, h));
}

static float	calc_colour(t_data *data, float h)
{
	float	colour_perc;
	int		colour;

	if (h == 0)
		colour = BLACK_PIXEL;
	else
	{
		colour_perc = (h - data->min_h) / (data->max_h - data->min_h);//0 30 100 0.3 - 30 65 100 - 30 50 230
		//colour = colour_perc * GREEN_PIXEL;
//		colour = colour_perc * WHITE_PIXEL;
		colour = scale_rgb(colour_perc);
	}
	return (colour);
}

static int	scale_rgb(float percent)
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
