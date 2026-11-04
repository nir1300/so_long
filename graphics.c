/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:23:15 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/01/20 15:47:44 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_background(t_mlx_data *data)
{
	if (data->map->content[data->y_count][data->x_count] == '0')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.grass,
			38 * data->x_count, 38 * data->y_count);
	else if (data->map->content[data->y_count][data->x_count] == '1')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.tree, 38
			* data->x_count, 38 * data->y_count);
	else if (data->map->content[data->y_count][data->x_count] == 'P')
	{
		data->x_pos = data->x_count;
		data->y_pos = data->y_count;
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.player,
			38 * data->x_count, 38 * data->y_count);
	}
	else if (data->map->content[data->y_count][data->x_count] == 'E')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.exit, 38
			* data->x_count, 38 * data->y_count);
	else if (data->map->content[data->y_count][data->x_count] == 'C')
		mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.shroom,
			38 * data->x_count, 38 * data->y_count);
}

int	loop_background(t_mlx_data *data)
{
	while (data->y_count < data->y_len)
	{
		data->x_count = 0;
		while (data->x_count < data->x_len)
		{
			draw_background(data);
			data->x_count++;
		}
		data->y_count++;
	}
	return (0);
}

int	load_images(t_mlx_data *data)
{
	int	height;
	int	width;

	data->img.grass = mlx_xpm_file_to_image(data->mlx_ptr, "textures/grass.xpm",
			&width, &height);
	data->img.tree = mlx_xpm_file_to_image(data->mlx_ptr, "textures/tree.xpm",
			&width, &height);
	data->img.player = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/player.xpm", &width, &height);
	data->img.exit = mlx_xpm_file_to_image(data->mlx_ptr, "textures/exit.xpm",
			&width, &height);
	data->img.shroom = mlx_xpm_file_to_image(data->mlx_ptr,
			"textures/mushroom.xpm", &width, &height);
	if (!data->img.grass || !data->img.tree || !data->img.player
		|| !data->img.exit || !data->img.shroom)
		ft_close(data);
	return (0);
}
