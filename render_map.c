/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:33:14 by acastano          #+#    #+#             */
/*   Updated: 2022/04/22 17:07:29 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	render_text(t_data *data)
{
	if (data->win != NULL)
    {
		mlx_string_put(data->mlx, data->win, 50, 20, WHITE_PIXEL, "INSTRUCTIONS");
		mlx_string_put(data->mlx, data->win, 50, 40, WHITE_PIXEL, "Press Esc to Exit");
    }
}

int	render_map(t_data *data)
{
	data->offset = 100;
	data->dist = 50;
	if (data->win != NULL)
    {
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
					draw_line(data);
				}
				if (((data->y0 + 1) < data->n_rows) && (data->x0 < data->rows_width[data->y0 + 1]))
				{
					data->x1 = data->x0;
					data->y1 = data->y0 + 1;
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
