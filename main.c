
#include "fdf.h"

static void ft_putchar(char c)
{
  write(1, &c, 1);
}

static void ft_putnbr(int num)
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

static int key_action(int keysym, t_data *data)
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

static int	render(t_data *data)
{
  if (data->window != NULL)//if window not destroyed
    {
      mlx_pixel_put(data->mlx, data->window, 150, 60, RED_PIXEL);
      //mlx_string_put(data->mlx, data->window, 50, 50, GREEN_PIXEL, "INSTRUCTIONS\nPress Esc to Exit");//16777215
      //bresenham_line_algo(50, 50, 80, 80, data);
      bresenham_line_algo(50, 50, 10, 20, data);
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

