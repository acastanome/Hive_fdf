#include "mlx.h"
#include <unistd.h>//write
#include <stdlib.h>//exit

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

int key_action(int keycode, void *param)
{
  //  ft_putchar('X');
  //  ft_putnbr(keycode);
  if (keycode == 65307)//Esc keycode
    exit (0);
  return (0);
}

int	main()
{
  void *mlx;
  void *window;

  mlx = mlx_init();
  window = mlx_new_window(mlx, 500, 500, "Al's first window");
  mlx_pixel_put(mlx, window, 250, 250, 0x9999);
  mlx_key_hook(window, key_action, (void *)0);
  mlx_loop(mlx);
  return (0);
}
