/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:23 by acastano          #+#    #+#             */
/*   Updated: 2022/05/02 14:51:14 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
#include <stdlib.h>
#include <stdio.h>

#include <X11/X.h>
#include <X11/keysym.h>
#include "mlx.h"
*/

#include "libft/libft.h"
#include "mlx.h"
//#include <keys.h>
//#include <X11/keysym.h>//keysym XK_Escape

#include <unistd.h>//write
#include <stdlib.h>//exit
#include <stdio.h>//printf

# define MLX_ERROR 1
# define WIN_WIDTH 1500
# define WIN_HEIGHT 1000
# define TOP 1
# define FRONT 2
# define ISO 3

# define WHITE_PIXEL 0xFFFFFF
# define BLACK_PIXEL 0x000000
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLUE_PIXEL 0x0000FF

# define SIN_30 0.5
# define COS_30 0.8660254

typedef struct s_data
{
// helper variables
	int		colour;
	int		i;
// context
	int		fd;
	void	*mlx;
	void	*win;
  	int		dist;
	int		offset;
	int		offset_x;
	int		offset_y;
	int		x_extra;
	int		y_extra;
	float		h_extra;
// map
	int		**map;
	int		n_rows;
	int		*rows_width;
	float		h_max;
	float		h_min;
//view
	int		projection;
	int		x0;
	int		y0;
	int		z0;
	int		x1;
	int		y1;
	int		z1;
	int		Rx0;
	int		Ry0;
	int		Rx1;
	int		Ry1;
//bresenham
	int		BC;
	int		DC;
	int		dx;
	int		dy;
}			t_data;

//main.c
void	initialize_data(t_data *data);

//line.c
void	draw_line(t_data *data);
int	bresenham_line_algo(t_data *data);
//int	render(t_data *data);
//int key_action(int keysym, t_data *data);

//read_file.c
int	read_file(char *file, t_data *data);

//errors.c
void	errors(char *s);

//render_map.c
void	transform_iso(t_data *data);
void	transform_front(t_data *data);
int	render_map(t_data *data);

#endif
