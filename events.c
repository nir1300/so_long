/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 16:24:29 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/01/20 17:40:28 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move(t_mlx_data *data, int new_x, int new_y)
{
	if (new_x >= data->x_len || new_x <= 0 || new_y >= data->y_len
		|| new_y <= 0)
		return ;
	if (data->map->content[new_y][new_x] == '1'
		|| (data->map->content[new_y][new_x] == 'E'
			&& data->collect != data->collected))
		return ;
	if (data->map->content[new_y][new_x] == 'C')
	{
		data->map->content[new_y][new_x] = '0';
		data->collected++;
	}
	if (data->map->content[new_y][new_x] == 'E')
		ft_close(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.grass, 38
		* data->x_pos, 38 * data->y_pos);
	data->moves++;
	ft_printf("Moves: %i\n", data->moves);
	data->x_pos = new_x;
	data->y_pos = new_y;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.player, 38
		* data->x_pos, 38 * data->y_pos);
}

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		ft_close(data);
	else if (keysym == 65361 || keysym == 97)
		move(data, data->x_pos - 1, data->y_pos);
	else if (keysym == 65363 || keysym == 100)
		move(data, data->x_pos + 1, data->y_pos);
	else if (keysym == 65362 || keysym == 119)
		move(data, data->x_pos, data->y_pos - 1);
	else if (keysym == 65364 || keysym == 115)
		move(data, data->x_pos, data->y_pos + 1);
	return (0);
}

int	button_press(int button, t_mlx_data *data)
{
	if (button == 1)
		ft_close(data);
	return (0);
}
