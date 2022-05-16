/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:33:14 by acastano          #+#    #+#             */
/*   Updated: 2022/05/16 20:28:33 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	render_map(t_data *data);
static void	render_text(t_data *data);

/*
 * render() clears the window before calling render_map() to create the image to
 * render, mlx_put_image_to_window() to display it, and render_text() to add the
 * (instruction) text on top. Finally, it destroys the image before returning.
 */
int	render(t_data *data)
{
	mlx_clear_window(data->mlx, data->win);
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (data->img == NULL)
		exit_fdf("mlx_new_image() failed.\n");
	data->img_addr = mlx_get_data_addr(data->img, &data->px_bits,
			&data->line_bytes, &data->endian);
	if (data->img_addr == NULL)
		exit_fdf("mlx_get_data_addr() failed.\n");
	render_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	render_text(data);
	mlx_destroy_image(data->mlx, data->img);
	return (0);
}

/*
 * render_map() will call draw_line() to add the necessary pixels to the image
 * for each line between the maps points.
 */
static void	render_map(t_data *data)
{
	if (data->win == NULL)
		return ;
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
			if (((data->y0 + 1) < data->n_rows)
				&& (data->x0 < data->rows_width[data->y0 + 1]))
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

/*
 * render_text() displays the instructions in the window saved in data->win.
 */
static void	render_text(t_data *data)
{
	if (data->win != NULL)
	{
		mlx_string_put(data->mlx, data->win, 125, 50, WHITE, "INSTRUCTIONS");
		mlx_string_put(data->mlx, data->win, 25, 90, WHITE, "Mouse");
		mlx_string_put(data->mlx, data->win, 50, 115, WHITE,
			"Wheel: Modify height");
		mlx_string_put(data->mlx, data->win, 50, 135, WHITE,
			"L / R buttons: Change colours");
		mlx_string_put(data->mlx, data->win, 25, 175, WHITE, "Keyboard");
		mlx_string_put(data->mlx, data->win, 50, 200, WHITE,
			"Arrows: Position inside window");
		mlx_string_put(data->mlx, data->win, 50, 220, WHITE,
			"+ - : Change zoom");
		mlx_string_put(data->mlx, data->win, 50, 240, WHITE, "R: Reset view");
		mlx_string_put(data->mlx, data->win, 50, 270, WHITE, "Perspectives:");
		mlx_string_put(data->mlx, data->win, 75, 290, WHITE, "F: Front");
		mlx_string_put(data->mlx, data->win, 75, 310, WHITE, "T: Top");
		mlx_string_put(data->mlx, data->win, 75, 330, WHITE, "I: Isometric");
		mlx_string_put(data->mlx, data->win, 75, 350, WHITE, "B: Bimetric");
		mlx_string_put(data->mlx, data->win, 50, 380, WHITE, "Esc: Exit");
		mlx_string_put(data->mlx, data->win, 25, WIN_HEIGHT - 50, WHITE,
			"Bresenham line algorithm");
	}
}

/*
 * img_pixel_put() adds the pixel (rx, ry), in the specified colour, to the
 * image saved in data.
 * Note: It is up to the user to check that the pixel fits in the image.
 */
void	img_pixel_put(t_data *data, int rx, int ry, int colour)
{
	char	*image;

	if (data->px_bits != 32)
		mlx_get_color_value(data->mlx, colour);
	image = data->img_addr + (rx * (data->px_bits / 8))
		+ (ry * data->line_bytes);
	if (image == NULL)
		exit_fdf("img_pixel_put() failed to allocate image pixel.\n");
	*(unsigned int *)image = colour;
}

/*
 * colour() sets the colour for the whole line, depending is the line at 0
 * height or not.
 */
int	colour(t_data *data)
{
	if ((data->z0 == data->z1) && (data->z0 == 0))
	{
		if (data->colour == WHITE)
			return (0x00ffff);
		return (WHITE);
	}
	else
		return (data->colour);
}
