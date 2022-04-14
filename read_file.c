/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:41:59 by acastano          #+#    #+#             */
/*   Updated: 2022/04/14 17:44:48 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>//open
#include <stdio.h>//printf

static int	init_map(t_data *data)
{
	data->map = (int **)ft_memalloc(sizeof(int *) * ((data->n_rows) + 1));
	if (!(data->map))
		errors("Error: Failed to allocate int **map.\n");
	data->rows_width = (int *)ft_memalloc(sizeof(int) * data->n_rows);
	if (!(data->rows_width))
		errors("Error: Failed to allocate int *rows_width.\n");
	return (0);
}

static int	init_rows(char *file, t_data *data)
{
	int		ret;
	char	*line;
	char	**temp;
	int		j;

	data->fd = open(file, O_RDONLY);
	if (data->fd < 0)
		errors("Error: Failed to open file.\n");
	ret = 1;
	data->i = 0;
	while (ret == 1)
	{
		ret = get_next_line(data->fd, &line);
		if (line)
		{
			data->rows_width[data->i] = ft_word_count(line, ' ');
			(data->map)[data->i] = (int *)ft_memalloc(sizeof(int) * ((data->rows_width)[data->i] + 1));
			if (!(data->map[data->i]))
				errors("Error: Failed to allocate data->map[data->i].\n");
			temp = ft_strsplit(line, ' ');
			j = 0;
			while (j < data->rows_width[data->i])
			{
				data->map[data->i][j] = ft_atoi(temp[j]);
				j++;
			}
			ft_memdelarray((void ***)&temp);
		}
		data->i++;
		ft_memdel((void *)&line);
	}
	close(data->fd);
	return (0);
}

int	read_file(char *file, t_data *data)
{
	int		ret;
	char	*line;

	data->fd = open(file, O_RDONLY);
	if (data->fd < 0)
		errors("Error: Failed to open file.");
	ret = 1;
	(data->n_rows) = 0;
	while (ret == 1)
	{
		ret = get_next_line(data->fd, &line);
		if (line != NULL)
			(data->n_rows)++;
		ft_memdel((void *)&line);
	}
	close(data->fd);
	init_map(data);
	init_rows(file, data);
	return (0);
}
