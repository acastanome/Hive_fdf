/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acastano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 12:41:59 by acastano          #+#    #+#             */
/*   Updated: 2022/05/10 20:16:09 by acastano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_map(char *file, t_data *data);
static void	init_row(char *line, t_data *data);

int	read_file(char *file, t_data *data)
{
	int		ret;
	char	*line;

	data->fd = open(file, O_RDONLY);
	if (data->fd < 0)
		exit_fdf("Error: Failed to open file.");
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
	data->rows_width_max = 0;
	init_map(file, data);
	return (0);
}

static void	init_map(char *file, t_data *data)
{
	int		ret;
	char	*line;

	data->map = (int **)ft_memalloc(sizeof(int *) * (data->n_rows));
	if (!(data->map))
		exit_fdf("Error: Failed to allocate int **map.\n");
	data->rows_width = (int *)ft_memalloc(sizeof(int) * data->n_rows);
	if (!(data->rows_width))
		exit_fdf("Error: Failed to allocate int *rows_width.\n");
	data->fd = open(file, O_RDONLY);
	if (data->fd < 0)
		exit_fdf("Error: Failed to open file.\n");
	ret = 1;
	data->i = 0;
	while (ret == 1)
	{
		ret = get_next_line(data->fd, &line);
		if (line)
			init_row(line, data);
		data->i++;
		ft_memdel((void *)&line);
	}
	close(data->fd);
}

static void	init_row(char *line, t_data *data)
{
	char	**temp;
	int		j;

	data->rows_width[data->i] = ft_word_count(line, ' ');
	if (data->rows_width[data->i] > data->rows_width_max)
		data->rows_width_max = data->rows_width[data->i];
	(data->map)[data->i] = (int *)ft_memalloc(sizeof(int)
			* ((data->rows_width)[data->i]));
	if (!(data->map[data->i]))
		exit_fdf("Error: Failed to allocate data->map[data->i].\n");
	temp = ft_strsplit(line, ' ');
	j = 0;
	data->h_min = data->map[0][0];
	data->h_max = data->map[0][0];
	while (j < data->rows_width[data->i])
	{
		data->map[data->i][j] = ft_atoi(temp[j]);
		if (data->map[data->i][j] < data->h_min)
			data->h_min = data->map[data->i][j];
		if (data->map[data->i][j] > data->h_max)
			data->h_max = data->map[data->i][j];
		j++;
	}
	ft_memdelarray((void *)&temp);
}
