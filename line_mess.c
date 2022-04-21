/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:49 by acastano          #+#    #+#             */
/*   Updated: 2022/04/21 18:38:05 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/*int	rgb_toi(float r, float g, float b)
{
  int	rgb;

  rgb = (r * 255) << 16;
  rgb |= ((g * 255) << 8);
  rgb |= (b * 255);
  return rgb;
}*/

/*
 * point_height() uses linear equation to calculate the height at any point of
 * a line. Then uses this height to calculate the colour the pixels should have.
 */
int	point_height_colour(t_data *data)
{
	int	h;
	int	h0;
	int	h1;
	int	m;
	int	colour;

	h0 = data->map[data->y0][data->x0];
	h1 = data->map[data->y1][data->x1];
	if (data->dy == 0)
		h = ((h1 - h0) / (data->Rx1 - data-Rx0)) * (data->Rx0 - data->Rx0) + h1;
//	else
	m = (h1 - h0) / (data->Rx1 - data-Rx0);
//	h = ((h1 - h0) / (data->dist * (data->x1 - data->x0))) * (*data->p - data->p0) + h0;
	//ft_putnbr(h);
	//write(1, " ", 1);
	if (h == 0)
		colour = WHITE_PIXEL;
	else
	{
		if (h < 6)
			colour = RED_PIXEL;
		else
			colour = GREEN_PIXEL;
	}
	return (colour);
}

void	draw_line(t_data *data)
{
	data->Rx0 = (data->x0 * data->dist) + data->offset;
	data->Ry0 = (data->y0 * data->dist) + data->offset;
	data->Rx1 = (data->x1 * data->dist) + data->offset;
	data->Ry1 = (data->y1 * data->dist) + data->offset;
	bresenham_line_algo(data);
}

/*
 * bresenham_line_algo() calculates the pixels that need to be rendered to draw
 * a line from (x0, y0) to (x1, y1), on the window defined in data.
 * Works in all octants.
 */
int	bresenham_line_algo(t_data *data)
{
	//int	dx;
	int	sx;
	//int	dy;
	int	sy;
	int	error;
	int	e2;

/*	if (data->p0 == x0)
		data->p = &x0;
	else
	  data->p = &y0;*/
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
