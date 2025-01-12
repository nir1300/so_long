/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:57:04 by codespace         #+#    #+#             */
/*   Updated: 2025/01/12 21:33:16 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_freeme(char **arr)
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

int	create_map(int fd, t_map *map)
{
	char	*txt;
	char	*temp;
	char	*new_txt;
	char	**full_txt;

	full_txt = NULL;
	new_txt = NULL;
	txt = ft_strdup("");
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		new_txt = ft_strjoin(txt, temp);
		free(txt);
		free(temp);
		txt = new_txt;
	}
	map->content = ft_split(txt, '\n');
	map->cpy = ft_split(txt, '\n');
	free(txt);
	if (!full_txt)
		return (1);
	return (0);
}

int	validate_map(char **map)
{
	int	a;
	int	b;
	int	length[2];
	int	start_exit;
	int	collect;

	length[0] = 0;
	a = 0;
	start_exit = 0;
	collect = 0;
	while (map[length[0]])
		length[0]++;
	length[1] = ft_strlen(map[0]);
	while (map[a])
	{
		b = 0;
		while (map[a][b])
		{
			if (((a == 0 || a == length[0] - 1 || b == 0 || b == length[1] - 1)
					&& map[a][b] != '1') || (ft_strchr("01CEP",
						map[a][b]) == NULL))
				return (1);
			if (map[a][b] == 'E' || map[a][b] == 'P')
				start_exit++;
			if (map[a][b] == 'C')
				collect++;
			b++;
		}
		if (b != length[1])
			return (1);
		a++;
	}
	if (start_exit != 2 || collect < 1)
		return (1);
	return (collect);
}

void	fill_grid(char **map, int x, int y, int length[], int *count)
{
	if (map[x][y] == 'C')
		(*count)++;
	if (map[x][y] == '1' || map[x][y] == 'F' || map[x][y] == 'E')
		return ;
	if (map[x][y] == '0')
		map[x][y] = 'F';
	if (map[x][y] == 'C')
		map[x][y] = 'c';
	if (x + 1 < length[0])
		fill_grid(map, x + 1, y, length, count);
	if (x - 1 >= 0)
		fill_grid(map, x - 1, y, length, count);
	if (y + 1 < length[1])
		fill_grid(map, x, y + 1, length, count);
	if (y - 1 >= 0)
		fill_grid(map, x, y - 1, length, count);
}

int	flood_fill(char **map)
{
	int	x;
	int	y;
	int	length[2];
	int	count;

	length[0] = 0;
	x = 0;
	count = 0;
	while (map[length[0]])
		length[0]++;
	length[1] = ft_strlen(map[0]);
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'P')
				return (fill_grid(map, x, y, length, &count), count);
			y++;
		}
		x++;
	}
	return (1);
}

int	ft_close(t_mlx_data *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.tree);
	mlx_destroy_image(data->mlx_ptr, data->img.collect);
	mlx_destroy_image(data->mlx_ptr, data->img.exit);
	mlx_destroy_image(data->mlx_ptr, data->img.grass);
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

void	move(t_mlx_data *data, int x_increase, int y_increase)
{
	int	new_x;
	int	new_y;

	new_x = data->x_pos + x_increase;
	new_y = data->y_pos + y_increase;
	if (new_x >= data->map->x_len || new_x <= 0 || new_y >= data->map->y_len
		|| new_y <= 0)
		return ;
	if (data->map->content[new_y][new_x] == '1'
		|| (data->map->content[new_y][new_x] == 'E'
			&& data->collect_total != data->collected))
		return ;
	if (data->map->content[new_y][new_x] == 'C')
	{
		data->map->content[new_y][new_x] = '0';
		data->collected++;
		printf("Collected : %i/%i\n", data->collected, data->collect_total);
	}
	if (data->map->content[new_y][new_x] == 'E')
		ft_close(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.grass, 38
		* data->x_pos, 38 * data->y_pos);
	data->moves++;
	printf("Moves: %i\n", data->moves);
	data->x_pos = new_x;
	data->y_pos = new_y;
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.player, 38
		* data->x_pos, 38 * data->y_pos);
}

int	handle_input(int keysym, t_mlx_data *data)
{
	if (keysym == XK_Escape)
		ft_close(data);
	else if (keysym == 65361)
		move(data, -1, 0);
	else if (keysym == 65363)
		move(data, 1, 0);
	else if (keysym == 65362)
		move(data, 0, -1);
	else if (keysym == 65364)
		move(data, 0, 1);
	return (0);
}

int	button_press(int button, t_mlx_data *data)
{
	if (button == 1)
		ft_close(data);
	return (0);
}

int	draw_background(t_mlx_data *data, int x, int y)
{
	int	x_count;
	int	y_count;

	x_count = 0;
	y_count = 0;
	while (y_count < y)
	{
		x_count = 0;
		while (x_count < x)
		{
			if (data->map->content[y_count][x_count] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img.grass, 38 * x_count, 38 * y_count);
			else if (data->map->content[y_count][x_count] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img.tree, 38 * x_count, 38 * y_count);
			else if (data->map->content[y_count][x_count] == 'P')
			{
				data->x_pos = x_count;
				data->y_pos = y_count;
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img.player, 38 * x_count, 38 * y_count);
			}
			else if (data->map->content[y_count][x_count] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img.exit, 38 * x_count, 38 * y_count);
			else if (data->map->content[y_count][x_count] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
					data->img.collect, 38 * x_count, 38 * y_count);
			x_count++;
		}
		y_count++;
	}
	data->map->x_len = x_count;
	data->map->y_len = y_count;
	return (0);
}

int	load_images(t_mlx_data *data)
{
	int	height;
	int	width;

	data->img.grass = mlx_xpm_file_to_image(data->mlx_ptr, "images/grass.xpm",
			&width, &height);
	data->img.tree = mlx_xpm_file_to_image(data->mlx_ptr, "images/tree.xpm",
			&width, &height);
	data->img.player = mlx_xpm_file_to_image(data->mlx_ptr, "images/player.xpm",
			&width, &height);
	data->img.exit = mlx_xpm_file_to_image(data->mlx_ptr, "images/exit.xpm",
			&width, &height);
	data->img.collect = mlx_xpm_file_to_image(data->mlx_ptr,
			"images/mushroom.xpm", &width, &height);
	if (!data->img.grass || !data->img.tree || !data->img.player
		|| !data->img.exit || !data->img.collect)
		ft_close(data);
	return (0);
}

int	game_loop(t_mlx_data *data, int x, int y)
{
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (1);
	data->win_ptr = mlx_new_window(data->mlx_ptr, x * 38, y * 38, "so_long");
	if (!data->win_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		return (1);
	}
	load_images(data);
	draw_background(data, x, y);
	mlx_key_hook(data->win_ptr, &handle_input, data);
	mlx_hook(data->win_ptr, 17, 0, ft_close, data);
	mlx_loop(data->mlx_ptr);
	return (0);
}

int	main(int argc, char *argv[])
{
	int			fd;
	int			flood;
	int			a;
	t_mlx_data	*data;

	if (argc != 2)
		exit(1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\nMessage"), 1);
	data = malloc(sizeof(*(data)));
	data->map = malloc(sizeof(*(data->map)));
	create_map(fd, data->map);
	data->collect_total = validate_map(data->map->cpy);
	if (data->collect_total == 0)
		return (printf("Error\nInvalid map"), 1);
	flood = flood_fill(data->map->cpy);
	if (data->collect_total != flood)
		return (printf("Error\nNot all collectibles reachable"));
	a = 0;
	data->moves = 0;
	while (data->map->content[a])
		printf("%s\n", data->map->content[a++]);
	data->collected = 0;
	game_loop(data, ft_strlen(data->map->content[0]), a);
}