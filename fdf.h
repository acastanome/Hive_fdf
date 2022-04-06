
#ifndef FDF_H
# define FDF_H

/*
#include <stdlib.h>
#include <stdio.h>

#include <X11/X.h>
#include <X11/keysym.h>
#include "mlx.h"
*/

#include "mlx.h"
#include <X11/keysym.h>//keysym XK_Escape

#include <unistd.h>//write
#include <stdlib.h>//exit

# define MLX_ERROR 1
# define WINDOW_WIDTH 1000
# define WINDOW_HEIGHT 1000
# define WHITE_PIXEL 0xFFFFFF
# define BLACK_PIXEL 0x000000
# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLUE_PIXEL 0x0000FF

typedef struct s_data
{
  void	*mlx;
  void	*win;
  int	**map;
  int	cols;
  int	rows;
  int	offset;
  int	colour;
  int	i;
}	t_data;

int	bresenham_line_algo(int x0, int y0, int x1, int y1, t_data *data);
//int	render(t_data *data);
//int key_action(int keysym, t_data *data);

#endif
