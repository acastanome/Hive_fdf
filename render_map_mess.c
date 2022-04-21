/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:33:14 by acastano          #+#    #+#             */
/*   Updated: 2022/04/21 14:27:43 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	render_text(t_data *data)
{
  if (data->win != NULL)//if window not destroyed
    {
      mlx_string_put(data->mlx, data->win, 50, 20, WHITE_PIXEL, "INSTRUCTIONS");//16777215
      mlx_string_put(data->mlx, data->win, 50, 40, WHITE_PIXEL, "Press Esc to Exit");//16777215
    }
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
	data->offset = 100;
	data->dist = 50;
	if (data->win != NULL)//if window not destroyed
    {
		//mlx_string_put(data->mlx, data->win, 50, 50, GREEN_PIXEL, "INSTRUCTIONS\nPress Esc to Exit");//16777215
		//      bresenham_line_algo(0, 0, (1 * 10), (1 * 10), data);

		data->y0 = 0;
		while (data->y0 < data->n_rows)
		{
			data->x0 = 0;
			while (data->x0 < data->rows_width[data->y0])
			{
				if ((data->x0 + 1) < data->rows_width[data->y0])
				{
					data->x1 = data->x0 + 1;
					data->y1 = data->y0;
//					data->p0 = (data->x0 * data->dist) + data->offset;
//					data->p1 = (data->x1 * data->dist) + data->offset;
					draw_line(data);
				}
				if (((data->y0 + 1) < data->n_rows) && (data->x0 < data->rows_width[data->y0 + 1]))
				{
					data->x1 = data->x0;
					data->y1 = data->y0 + 1;
//					data->p0 = (data->y0 * data->dist) + data->offset;
//					data->p1 = (data->y1 * data->dist) + data->offset;
					draw_line(data);
				}
				data->x0++;
			}
			data->y0++;
		}
    }
	render_text(data);
	return (0);
}
