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

#define MLX_ERROR 1
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 300
#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0x00FF00
#define BLUE_PIXEL 0x0000FF

typedef struct s_data
{
void	*mlx;
void	*window;
}	t_data;

void ft_putchar(char c)
{
  write(1, &c, 1);
}

void ft_putnbr(int num)
{
  if (num < 0)
    {
      write(1, "-", 1);
      num = -num;
    }
  while (num > 9)//3250
    {
      ft_putnbr(num / 10);
      num = num % 10;
    }
  ft_putchar('0' + num);
}

int key_action(int keysym, t_data *data)
{
  //  ft_putchar('X');
  //  ft_putnbr(keycode);
  if (keysym == XK_Escape)//65307)Esc keycode
    {
      mlx_destroy_window(data->mlx, data->window);
      data->window = NULL;
      //exit (0);
    }
  return (0);
}

int	render(t_data *data)
{
  if (data->window != NULL)//if window not destroyed
    {
      mlx_pixel_put(data->mlx, data->window, (WINDOW_WIDTH / 2), (WINDOW_HEIGHT / 2), GREEN_PIXEL);
      mlx_string_put(data->mlx, data->window, 50, 50, GREEN_PIXEL, "INSTRUCTIONS\nPress Esc to Exit");//16777215
    }
  return (0);
}

int	main()
{
  t_data	data;

  data.mlx = mlx_init();
  if (data.mlx == NULL)
    return (MLX_ERROR);
  data.window = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Al's first window");
  if (data.window == NULL)
    {
      free(data.window);
      return (MLX_ERROR);
    }

  mlx_loop_hook(data.mlx, &render, &data);
  mlx_key_hook(data.window, key_action, &data);

  mlx_loop(data.mlx);

  mlx_destroy_display(data.mlx);//when no window left, this happens
  free(data.mlx);
  return (0);
}

