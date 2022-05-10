/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:23 by acastano          #+#    #+#             */
/*   Updated: 2022/05/10 20:49:30 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "mlx.h"

# include <math.h>
# include <fcntl.h>//open
# include <unistd.h>//write
# include <stdlib.h>//exit
# include <stdio.h>//printf

/*	RESOLUTION		*/
# define MLX_ERROR 1
# define WIN_WIDTH 2200
# define WIN_HEIGHT 1100

/*	PROJECTIONS		*/
/* Isometric: angles between axis are the same
 * Bimetric: 2 angles between axis are the same, one is different
 */
# define TOP 1
# define FRONT 2
# define ISO 3
# define BIMETRIC 4
# define SIN_30 0.5
# define COS_30 0.8660254
# define COS_60 0.5

/*	COLOURS			*/
# define WHITE 0xFFFFFF
# define BLACK 0x000000
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF

/*	KEYBOARD		*/
# define ON_DESTROY_X11 17
# define KEY_ESC_MAC 53
# define KEY_ESC_LINUX 65307
# define KEY_T 17
# define KEY_F 3
# define KEY_I 34
# define KEY_B 11
# define KEY_R 15
# define KEY_ARROW_LEFT 123
# define KEY_ARROW_RIGHT 124
# define KEY_ARROW_DOWN 125
# define KEY_ARROW_TOP 126
# define KEY_PLUS 69
# define KEY_MINUS 78

/*	DATA			*/
typedef struct s_data
{
	int		fd;
	void	*mlx;
	void	*win;
	void	*img;
	char	*img_addr;
	int		px_bits;
	int		line_bytes;
	int		endian;
	int		dist;
	int		offset_x;
	int		offset_y;
	float	h_extra;
	int		**map;
	int		n_rows;
	int		rows_width_max;
	int		*rows_width;
	float	h_max;
	float	h_min;
	int		x0;
	int		y0;
	int		z0;
	int		x1;
	int		y1;
	int		z1;
	int		proj;
	int		rx0;
	int		ry0;
	int		rx1;
	int		ry1;
//	int		colour;
//	int		x_extra;
//	int		y_extra;
	int		i;
	int		temp_rx0;
	int		temp_ry0;
	int		temp_rx1;
	int		temp_ry1;
}			t_data;

typedef struct s_bres
{
//	int		BC;
//	int		DC;
	int		dx;
	int		sx;
	int		dy;
	int		sy;
	int		error;
	int		e2;
}			t_bres;

/*	main.c			*/
void	initialize_data(t_data *data);

/*	read_file.c		*/
int		read_file(char *file, t_data *data);

/*	render.c	*/
int		render(t_data *data);
void	img_pixel_put(t_data *data, int rx, int ry, int colour);

/*	line.c			*/
void	draw_line(t_data *data, char direction);

/*	exit_fdf.c		*/
int		exit_fdf(char *s);

#endif
