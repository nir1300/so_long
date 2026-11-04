/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:21:24 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/01/31 14:31:10 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	empty_lines(t_map *map)
{
	int	a;

	a = 0;
	if (map->txt[a])
	{
		while (map->txt[a + 1])
		{
			if (map->txt[a] == '\n' && map->txt[a + 1] == '\n')
				return (1);
			a++;
		}
	}
	return (0);
}

void	ft_freeme(char **arr)
{
	int	a;

	a = 0;
	while (arr[a])
		a++;
	while (a >= 0)
	{
		free(arr[a]);
		a--;
	}
	free(arr);
}

int	ft_close(t_mlx_data *data)
{
	if (data->img.tree)
		mlx_destroy_image(data->mlx_ptr, data->img.tree);
	if (data->img.shroom)
		mlx_destroy_image(data->mlx_ptr, data->img.shroom);
	if (data->img.exit)
		mlx_destroy_image(data->mlx_ptr, data->img.exit);
	if (data->img.grass)
		mlx_destroy_image(data->mlx_ptr, data->img.grass);
	if (data->img.player)
		mlx_destroy_image(data->mlx_ptr, data->img.player);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	ft_freeme(data->map->content);
	ft_freeme(data->map->cpy);
	free(data->map);
	free(data);
	exit(1);
}

void	free_struct(t_mlx_data *data, char *msg)
{
	if (data->map)
	{
		if (data->map->content)
			ft_freeme(data->map->content);
		if (data->map->cpy)
			ft_freeme(data->map->cpy);
		free(data->map);
	}
	if (data)
		free(data);
	error(msg);
}
