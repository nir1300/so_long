/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:20:44 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/01/31 14:47:55 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	create_map(int fd, t_map *map)
{
	while (1)
	{
		map->temp = get_next_line(fd);
		if (!map->temp)
		{
			if (read(fd, map->txt, 1) < 0)
				return (free(map->txt), 1);
			break ;
		}
		map->new_txt = ft_strjoin(map->txt, map->temp);
		free(map->txt);
		free(map->temp);
		if (!map->new_txt)
			return (free(map->txt), 1);
		map->txt = map->new_txt;
	}
	close(fd);
	if (empty_lines(map) == 1)
		return (1);
	map->content = ft_split(map->txt, '\n');
	map->cpy = ft_split(map->txt, '\n');
	free(map->new_txt);
	if (!map->content || !map->cpy || !map->content[0])
		return (1);
	return (0);
}

void	validate_map(char **map, t_mlx_data *data)
{
	while (map[data->y_len])
		data->y_len++;
	data->x_len = ft_strlen(map[0]);
	if (data->x_len > 50 || data->y_len > 24)
		free_struct(data, "Error\nMap too large");
	while (map[data->a])
	{
		data->b = 0;
		while (map[data->a][++data->b])
		{
			if (((data->a == 0 || data->a == data->y_len - 1 || data->b == 0 \
			|| data->b == data->x_len - 1) && map[data->a][data->b] != '1') \
			|| (ft_strchr("01CEP", map[data->a][data->b]) == NULL))
				free_struct(data, "Error\nMap characters invalid");
			if (map[data->a][data->b] == 'E' || map[data->a][data->b] == 'P')
				data->se_count++;
			if (map[data->a][data->b] == 'C')
				data->collect++;
		}
		if (data->b != data->x_len)
			free_struct(data, "Error\nMap not rectangular");
		data->a++;
	}
	if (data->se_count != 2 || data->collect < 1)
		free_struct(data, "Error\nEntry, exit or collectible number invalid");
}

void	fill_grid(t_mlx_data *data, int x, int y, int *count)
{
	if (data->map->cpy[y][x] == '1' || data->map->cpy[y][x] == 'F')
		return ;
	if (data->map->cpy[y][x] == 'C')
		(*count)++;
	if (data->map->cpy[y][x] == 'E')
	{
		data->map->cpy[y][x] = 'F';
		return ;
	}
	data->map->cpy[y][x] = 'F';
	if (x + 1 < data->x_len)
		fill_grid(data, x + 1, y, count);
	if (x - 1 >= 0)
		fill_grid(data, x - 1, y, count);
	if (y + 1 < data->y_len)
		fill_grid(data, x, y + 1, count);
	if (y - 1 >= 0)
		fill_grid(data, x, y - 1, count);
}

void	check_exit(t_mlx_data *data)
{
	int	y;

	y = 0;
	while (data->map->cpy[y])
	{
		if (ft_strchr(data->map->cpy[y], 'E') != NULL)
			free_struct(data, "Error\nExit not reachable");
		y++;
	}
}

int	flood_fill(t_mlx_data *data)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (data->map->cpy[y])
	{
		x = 0;
		while (data->map->cpy[y][x])
		{
			if (data->map->cpy[y][x] == 'P')
			{
				fill_grid(data, x, y, &count);
				if (count != data->collect)
					free_struct(data,
						"Error\nCollectibles not reachable");
			}
			x++;
		}
		y++;
	}
	check_exit(data);
	return (1);
}
