/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:49 by acastano          #+#    #+#             */
/*   Updated: 2022/05/09 18:30:23 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	bresenham_line_algo(t_data *data);
static void	img_pixel_put(t_data *data, int Rx, int Ry, int colour);

/*
 * draw_line() calculates the starting and ending points of the line to draw,
 * calling transform() if the requested projection isn't parallel TOP.
 * Then checks if said points are inside the window before calling
 * bresenham_line_algo() to draw it
 */
void	draw_line(t_data *data, char direction)
{
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
	else
		data->BC = data->Ry1 - data->Ry0;
	if (data->proj == ISO || data->proj == FRONT || data->proj == BIMETRIC)
		transform(data);//xo yo in screen OR x1y1 in screen
/*	if (((data->Rx0 > 0 && data->Rx0 < WIN_WIDTH) && (data->Ry0 > 0 && data->Ry0 < WIN_HEIGHT)) || ((data->Rx1 > 0 && data->Rx1 < WIN_WIDTH) && (data->Ry1 > 0 && data->Ry1 < WIN_HEIGHT)))
		bresenham_line_algo(data);*/
	if ((!(data->Rx0 <= 0 && data->Rx1 <= 0) || !(data->Rx0 >= WIN_WIDTH && data->Rx1 >= WIN_WIDTH))//		!x0 x1 out left, or !x0 x1 out right AND
		&& (!(data->Ry0 <= 0 && data->Ry1 <= 0) || !(data->Ry0 >= WIN_HEIGHT && data->Ry1 >= WIN_HEIGHT)))//	!y0 y1 out top, or !y0 y1 out bottom
		bresenham_line_algo(data);
}

/*
 * bresenham_line_algo() calculates the pixels that need to be rendered to draw
 * a line from (x0, y0) to (x1, y1), on the window (data->mlx_win). Then calls
 * img_pixel_put() to add them to an image (data->mlx_img).
 * Works in all octants.
 */
static void	bresenham_line_algo(t_data *data)
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
//		if (((data->Rx0 + data->offset + data->offset_x) >= 0 && (data->Rx0 + data->offset + data->offset_x) < WIN_WIDTH) && ((data->Ry0 + data->offset + data->offset_y) >= 0 && (data->Ry0 + data->offset + data->offset_y) < WIN_HEIGHT))
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
}

static void	img_pixel_put(t_data *data, int Rx, int Ry, int colour)
{
	char	*image;

	if (data->px_bits != 32)
		mlx_get_color_value(data->mlx, colour);
	if ((Rx >= 0 && Rx < WIN_WIDTH) && (Ry >= 0 && Ry < WIN_HEIGHT))
	{
		image = data->img_addr + (Rx * (data->px_bits / 8)) + (Ry * data->line_bytes);
		if (image == NULL)
			exit_fdf("img_pixel_put() failed to allocate image pixel.\n");
		*(unsigned int *)image = colour;
	}
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
