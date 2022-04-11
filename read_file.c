/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:41:59 by acastano          #+#    #+#             */
/*   Updated: 2022/04/08 14:48:39 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>//open
#include <stdio.h>//printf

int	read_file(char *file)//, t_data *data)
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
		{
			(data->n_rows)++;
			ft_putstr(line);
		}
		if (ret == 1)
			printf("\n");
		free(line);
	}
	close(fd);
	init_map(data);//&?
	init_rows(file, data);//&?
	return (0);
}

int	init_rows(char *file, t_data *data)
{
	int		fd;
	int		ret;
	char	*line;
	int		i = 0;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("Error: Failed to open file.");
		return (MLX_ERROR);
	}
	ret = 1;
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		while (line)
		{//line: 0 0 0 10 10 ...
			if ((*line != " ") && (*line != '/0'))
			while (*line == " ")
				line++;
			if ((*line != " ") && (*line != '/0'))
				(data->rows_width)[i]++;
			line++;
		}
		(data->map)[i] = (int *)ft_memalloc(sizeof(int) * ((data->rows_width)[i] + 1));
		int j = 0;
		while (j < ((data->rows_width)[i]))
		{
			(data->map)[i] = ft_strsplit(line, " ");// no because chars not ints. have to -48
			j++;
		}
		i++;
		free(line);
	}

	close(fd);
	return (line_elem);
}

int	init_map(t_data *data)
{
	data->map = (int **)ft_memalloc(sizeof(int *) * ((data->n_rows) + 1));
	if (!(data->map))
	{
		ft_putstr("Error: Failed to allocate int **map.");
		return (MLX_ERROR);
	}
/*
	int	i = 0;
	while (i < data->n_rows)
	{
		map[i] = (int *)ft_memalloc(sizeof(int) * ((data->rows_width)[i] + 1));
		i++;
	}
*/
	return (0);
}
