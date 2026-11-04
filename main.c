/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:57:04 by codespace         #+#    #+#             */
/*   Updated: 2025/01/27 01:14:33 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	game_loop(t_mlx_data *data)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->x_len * 38, data->y_len
			* 38, "so_long");
	if (!data->win_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		free_struct(data, "Error\nCan't display window");
	}
	load_images(data);
	loop_background(data);
	mlx_key_hook(data->win_ptr, &handle_input, data);
	mlx_hook(data->win_ptr, 17, 0, ft_close, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}

void	initalize(t_mlx_data *data)
{
	data->y_len = 0;
	data->moves = 0;
	data->collected = 0;
	data->collect = 0;
	data->x_count = 0;
	data->y_count = 0;
	data->a = 0;
	data->se_count = 0;
	data->map->content = NULL;
	data->map->cpy = NULL;
	data->map->new_txt = NULL;
	data->map->txt = ft_strdup("");
	if (!data->map->txt)
		free_struct(data, "Error\nMemory allocation error");
	data->fd = open(data->path, O_RDONLY);
	free(data->path);
	if (data->fd < 0)
	{
		free(data->map->txt);
		free_struct(data, "Error\nCan't open file");
	}
}

void	error(char *msg)
{
	errno = EINVAL;
	perror(msg);
	exit(1);
}

int	main(int argc, char *argv[])
{
	t_mlx_data	*data;

	if (argc != 2 || ft_strnstr(argv[1], ".ber", ft_strlen(argv[1])) == NULL
		|| ft_strcmp(argv[1], ".ber") == 0)
		error("Error\nInvalid input");
	data = malloc(sizeof(*(data)));
	if (!data)
		error("Error\nMemory allocation failed");
	data->path = ft_strjoin("maps/", argv[1]);
	data->map = malloc(sizeof(*(data->map)));
	if (!data->map)
		free_struct(data, "Error\nMemory allocation failed");
	initalize(data);
	if (create_map(data->fd, data->map) == 1)
	{
		free(data->map->txt);
		free_struct(data, "Error\nMap creation failed");
	}
	validate_map(data->map->cpy, data);
	flood_fill(data);
	game_loop(data);
}
