/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:23 by acastano          #+#    #+#             */
/*   Updated: 2022/04/21 15:47:44 by acastano         ###   ########.fr       */
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

# define MLX_ERROR 1
# define WIN_WIDTH 2000
# define WIN_HEIGHT 1000
# define WHITE_PIXEL 0xFFFFFF
# define BLACK_PIXEL 0x000000
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLUE_PIXEL 0x0000FF

typedef struct s_data
{
	int		fd;
	void	*mlx;
	void	*win;
	int		**map;
	int		n_rows;
	int		*rows_width;
  int	x0;
  int	y0;
  int	x1;
  int	y1;
  int	Rx0;
  int	Ry0;
  int	Rx1;
  int	Ry1;
//bresenham_line_algo()
	int	dx;
	int	dy;
//  int	*p;
//  int	p0;
//  int	p1;
	int		offset;
  	int		dist;
	int		colour;
	int		i;
}			t_data;

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
int	render_map(t_data *data);

#endif
