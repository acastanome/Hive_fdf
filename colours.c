/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:52:12 by acastano          #+#    #+#             */
/*   Updated: 2022/05/09 16:01:07 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	scale_rgb(float scale);
float	calc_colour(t_data *data, float h);
//int	calculate_colour(float colour_percent);
//static int	rgb_toi(float r, float g, float b);
int	point_height_colour(t_data *data);

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
