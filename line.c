/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:49 by acastano          #+#    #+#             */
/*   Updated: 2022/04/29 16:00:02 by acastano         ###   ########.fr       */
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

void	draw_line(t_data *data)
{
/*	data->Rx0 = data->x0 * data->dist;
	data->Ry0 = data->y0 * data->dist;
	data->Rx1 = data->x1 * data->dist;
	data->Ry1 = data->y1 * data->dist;*/
	if (data->projection == ISO)
		transform_iso(data);
	if (data->projection == FRONT)
		transform_front(data);
/*	if (data->y1 == data->y0)
		data->BC = data->Rx1 - data->Rx0;
	else
	data->BC = data->Ry1 - data->Ry0;*/
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
//		mlx_pixel_put(data->mlx, data->win, data->Rx0 + data->offset, data->Ry0 + data->offset, point_height_colour(data);)
		mlx_pixel_put(data->mlx, data->win, data->Rx0 + data->offset + data->offset_x, data->Ry0 + data->offset + data->offset_y, RED_PIXEL);
//		mlx_pixel_put(data->mlx, data->win, data->Rx0, data->Ry0, WHITE_PIXEL);
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

	h0 = data->map[data->y0][data->x0];// + data->h_extra;
	h1 = data->map[data->y1][data->x1];// + data->h_extra;
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
