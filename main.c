/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:56:40 by acastano          #+#    #+#             */
/*   Updated: 2022/04/07 19:25:47 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "../../libftproject/libftfinal/libft.h"
#include <stdio.h>//printf

static int key_action(int keysym, t_data *data)
{
	//if (keysym == XK_Escape)//65307)Esc keycode
  if (keysym == 53)//65307)Esc keycode
    {
      mlx_destroy_window(data->mlx, data->win);
      data->win = NULL;
	  free(data->mlx);
	  exit (1);
    }
  return (0);
}

static int	render(t_data *data)
{
  if (data->win != NULL)//if window not destroyed
    {
      mlx_pixel_put(data->mlx, data->win, 150, 60, RED_PIXEL);
      //mlx_string_put(data->mlx, data->win, 50, 50, GREEN_PIXEL, "INSTRUCTIONS\nPress Esc to Exit");//16777215
      bresenham_line_algo(50, 50, 10, 20, data);
    }
  return (0);
}

/*
static int	render_points(t_data *data)
{
  int	n_lines = 11;
  int	x = 0;
  int	y = 0;
  //  int	elem = 0;
  if (data->win != NULL)//if window not destroyed
    {
      while (y < n_lines)
	{
	  while (x < 19)
	    {
	      if ((data->lines)[y][x] == 10)
		mlx_pixel_put(data->mlx, data->win, (50 + x), (50 + y), RED_PIXEL);
	      else
		mlx_pixel_put(data->mlx, data->win, (50 + x), (50 + y), WHITE_PIXEL);
	      x++;
	    }
	  x = 0;
	  y++;
	}
    }
  return (0);
}
*/

//int	main(int argc, char **argv)
int	main(void)
{
//  int	i = 0;
//  int	n_lines = 11;
  t_data	data;

//  (data.lines)[11][19] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 10, 10, 0, 0, 10, 10, 0, 0, 0, 10, 10, 10, 10, 10, 0, 0, 0}, {0, 0, 10, 10, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0}, {0, 0, 10, 10, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0}, {0, 0, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 10, 10, 10, 10, 0, 0, 0}, {0, 0, 0, 10, 10, 10, 10, 10, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 10, 10, 10, 10, 10, 10, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
  /*
  (data.lines)[0] = "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
  (data.lines)[1] = "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
  (data.lines)[2] = "0 0 10 10 0 0 10 10 0 0 0 10 10 10 10 10 0 0 0";
  (data.lines)[3] = "0 0 10 10 0 0 10 10 0 0 0 0 0 0 0 10 10 0 0";
  (data.lines)[4] = "0 0 10 10 0 0 10 10 0 0 0 0 0 0 0 10 10 0 0";
  (data.lines)[5] = "0 0 10 10 10 10 10 10 0 0 0 0 10 10 10 10 0 0 0";
  (data.lines)[6] = "0 0 0 10 10 10 10 10 0 0 0 10 10 0 0 0 0 0 0";
  (data.lines)[7] = "0 0 0 0 0 0 10 10 0 0 0 10 10 0 0 0 0 0 0";
  (data.lines)[8] = "0 0 0 0 0 0 10 10 0 0 0 10 10 10 10 10 10 0 0";
  (data.lines)[9] = "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
  (data.lines)[10] = "0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0";
  while (i < n_lines)
    {
      printf("%s\n", (data.lines)[i]);
      i++;
      }*/
  //if (argc != 2)
  //{
  //ft_putstr("usage: ./fdf <filename>");
  //exit (1);
  //}
  //fd = open(argv[1], O_RDONLY);
  //if (fd == -1)
  //return (MLX_ERROR);
  //ret = 1;
  //i = 1;
  //while (ret == 1)
  //{
  //ret = get_next_line(fd, &line);
  //if (line != NULL)
  //ft_putstr(line);
  //if (ret == 1)
  //printf("\n");
  //free(line);
  //}
  //close(fd);
  data.mlx = mlx_init();
  if (data.mlx == NULL)
    return (MLX_ERROR);
  data.win = mlx_new_window(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Al's first window");
  if (data.win == NULL)
    {
      free(data.win);
      return (MLX_ERROR);
    }

  //mlx_loop_hook(data.mlx, &render_points, &data);
  mlx_loop_hook(data.mlx, &render, &data);
  mlx_key_hook(data.win, key_action, &data);

  mlx_loop(data.mlx);

//  mlx_destroy_display(data.mlx);//when no window left, this happens
//  free(data.mlx);
  return (0);
}

