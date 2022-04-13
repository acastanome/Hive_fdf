
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:41:59 by acastano          #+#    #+#             */
/*   Updated: 2022/04/13 23:12:53 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>//open
#include <stdio.h>//printf

static int	init_map(t_data *data)
{
	data->map = (int **)ft_memalloc(sizeof(int *) * ((data->n_rows) + 1));
	if (!(data->map))
	{
		ft_putstr("Error: Failed to allocate int **map.\n");
		return (MLX_ERROR);
	}
	data->rows_width = (int *)ft_memalloc(sizeof(int) * data->n_rows);
	if (!(data->rows_width))
	{
		ft_putstr("Error: Failed to allocate int *rows_width.\n");
		//ft_strdelarray((char ***)&(data->map)) this is done before returning from read_file()
		return (MLX_ERROR);
	}
	return (0);
}

static int	init_rows(char *file, t_data *data)
{
	int		fd;
	int		ret;
	char	*line;
	int		i;
	char	**temp;
	int		j;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("Error: Failed to open file.\n");
		return (MLX_ERROR);
	}
	ret = 1;
	i = 0;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (line)
		{
			data->rows_width[i] = ft_word_count(line, ' ');
			(data->map)[i] = (int *)ft_memalloc(sizeof(int) * ((data->rows_width)[i] + 1));
			if (!(data->map[i]))
			{
				ft_putstr("Error: Failed to allocate data->map[");
				ft_putnbr(i);
				ft_putstr("].\n");
				//ft_strdelarray((char ***)&(data->map)) this is done before returning from read_file()
				return (MLX_ERROR);
			}
			temp = ft_strsplit(line, ' ');
			j = 0;
			while (j < data->rows_width[i])
			{
				data->map[i][j] = ft_atoi(temp[j]);
				printf("%d\t", data->map[i][j]);
				j++;
			}
			printf("\n");
			ft_memdelarray((void ***)&temp);
		}
		i++;
		ft_memdel((void*)&line);
	}
	close(fd);
	return (0);
}

int	read_file(char *file, t_data *data)
{
	int		fd;
	int		ret;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("Error: Failed to open file.");
		return (MLX_ERROR);
	}
	ret = 1;
	(data->n_rows) = 0;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (line != NULL)
			(data->n_rows)++;
		ft_memdel((void*)&line);
	}
	close(fd);
	init_map(data);
	init_rows(file, data);
	ft_memdelarray((void ***)&(data->map));
	return (0);
}
