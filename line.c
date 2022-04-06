
#include "fdf.h"
#include <math.h>

/*
 * bresenham_line_algo() draws a line to the window defined in data. Works in all octants.
 */
int	bresenham_line_algo(int x0, int y0, int x1, int y1, t_data *data)
{
  int	dx;
  int	sx;
  int	dy;
  int	sy;
  int	error;
  int	e2;

  dx = abs(x1 - x0);
  if (x0 < x1)
    sx = 1;
  else sx = -1;
  dy = -abs(y1 - y0);
  if (y0 < y1)
    sy = 1;
  else sy = -1;
  error = dx + dy;

  while (1)
    {
      mlx_pixel_put(data->mlx, data->win, x0, y0, WHITE_PIXEL);
      if (x0 == x1 && y0 == y1)
	break;
      e2 = 2 * error;
      if (e2 >= dy)
	{
	  if (x0 == x1)
	    break;
	  error = error + dy;
	  x0 = x0 + sx;
	}
      if (e2 <= dx)
	{
	  if (y0 == y1)
	    break;
	  error = error + dx;
	  y0 = y0 + sy;
	}
    }
  return (0);
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
