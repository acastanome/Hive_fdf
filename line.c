/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:49 by acastano          #+#    #+#             */
/*   Updated: 2022/04/14 20:38:04 by acastano         ###   ########.fr       */
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
int	point_height(t_data *data)
{
  int	h;
  int	h0;
  int	h1;
  int	colour;

  h0 = data->map[data->y0][data->x0];
  h1 = data->map[data->y1][data->x1];
  h = ((h1 - h0) / data->dist) * ((*(data->p)) - data->p0) + h0;
  //ft_putnbr(h);
  //write(1, " ", 1);
  if (h == 0)
    colour = WHITE_PIXEL;
  else if (h > 5 && h < 10)
    colour = RED_PIXEL;
  else
    colour = GREEN_PIXEL;
  return (colour);
}

void	draw_line(int x0, int y0, int x1, int y1, t_data *data)
{
  //  data->offset = 50;
  //  data->dist = 20;
  x0 = (x0 * data->dist) + data->offset;
  y0 = (y0 * data->dist) + data->offset;
  x1 = (x1 * data->dist) + data->offset;
  y1 = (y1 * data->dist) + data->offset;
  bresenham_line_algo(x0, y0, x1, y1, data);
}

/*
 * bresenham_line_algo() draws a line to the window defined in data.
 * Works in all octants.
 */
int	bresenham_line_algo(int x0, int y0, int x1, int y1, t_data *data)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	error;
	int	e2;

	if (data->p0 == x0)
	  data->p = &x0;
	else
	  data->p = &y0;
	dx = abs(x1 - x0);
	if (x0 < x1)
		sx = 1;
	else sx = -1;
	dy = -abs(y1 - y0);
	if (y0 < y1)
		sy = 1;
	else sy = -1;
	error = dx + dy;

	while (1)
	{
	  mlx_pixel_put(data->mlx, data->win, x0, y0, point_height(data));
	  //mlx_pixel_put(data->mlx, data->win, (x0 + data->offset), (y0 + data->offset), WHITE_PIXEL);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * error;
		if (e2 >= dy)
		{
			if (x0 == x1)
				break;
			error = error + dy;
			x0 = x0 + sx;
		}
		if (e2 <= dx)
		{
			if (y0 == y1)
				break;
			error = error + dx;
			y0 = y0 + sy;
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
