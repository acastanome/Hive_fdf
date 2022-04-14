/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:33:14 by acastano          #+#    #+#             */
/*   Updated: 2022/04/14 21:12:33 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int	render(t_data *data)
{
  if (data->win != NULL)//if window not destroyed
    {
      //mlx_string_put(data->mlx, data->win, 50, 50, GREEN_PIXEL, "INSTRUCTIONS\nPress Esc to Exit");//16777215
//      bresenham_line_algo(0, 0, (1 * 10), (1 * 10), data);
	  int	 x = 0;
	  int	 y = 0;
	  int	dist = 20;
      bresenham_line_algo(x, y, ((x + 1) * dist), (y * dist), data);
//      mlx_pixel_put(data->mlx, data->win, (x + data->offset), (y + data->offset), RED_PIXEL);
    }
  return (0);
}

/*
static int	render_points(t_data *data)
{
  int	n_lines = 11;
  int	x = 0;
  int	y = 0;
  //  int	elem = 0;
  if (data->win != NULL)//if window not destroyed
    {
      while (y < n_lines)
	{
	  while (x < 19)
	    {
	      if ((data->lines)[y][x] == 10)
		mlx_pixel_put(data->mlx, data->win, (50 + x), (50 + y), RED_PIXEL);
	      else
		mlx_pixel_put(data->mlx, data->win, (50 + x), (50 + y), WHITE_PIXEL);
	      x++;
	    }
	  x = 0;
	  y++;
	}
    }
  return (0);
}
*/


int	render_map(t_data *data)
{
	if (data->win != NULL)//if window not destroyed
    {
		//mlx_string_put(data->mlx, data->win, 50, 50, GREEN_PIXEL, "INSTRUCTIONS\nPress Esc to Exit");//16777215
//      bresenham_line_algo(0, 0, (1 * 10), (1 * 10), data);
		int	 x = 0;
		int	 y = 0;
		int	dist = 20;

		while (y < data->n_rows)
		{
			x = 0;
			while (x < data->rows_width[y])
			{
				if (data->map[y][x + 1] != '\0')
					bresenham_line_algo((x * dist), (y * dist), ((x + 1) * dist), (y * dist), data);		
				x++;
			}
			y++;
		}
/*		x = 0;
		while (x < data->rows_width[y])
		{
			y = 0;
			while (y < data->n_rows)
			{
				if (data->map[y + 1][x] != '\0')
					bresenham_line_algo((x * dist), (y * dist), (x * dist), ((y + 1) * dist), data);		
				y++;
			}
			x++;
		}*/
	}
	return (0);
}
