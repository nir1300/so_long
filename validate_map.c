/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:57:04 by codespace         #+#    #+#             */
/*   Updated: 2024/12/09 18:18:10 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	ft_freeme(char **arr, int a)
{
	while (a >= 0)
	{
		free(arr[a]);
		a--;
	}
	free(arr);
}

char	*sl_ft_remainder(char *dest)
{
	char	*rem;
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (dest[i])
		i++;
	if (dest[i] == '\0')
		return (ft_free(dest, NULL, 0));
	i++;
	rem = malloc(ft_strlen(dest) - i + 1);
	if (!rem)
		return (ft_free(dest, NULL, 0));
	while (dest[i])
		rem[n++] = dest[i++];
	rem[n] = '\0';
	ft_free(dest, NULL, 0);
	return (rem);
}

char	*sl_create_line(char *dest)
{
	int		i;
	char	*temp;

	i = 0;
	while (dest[i])
		i++;
	temp = malloc(i + 2);
	if (!temp)
		return (ft_free(dest, NULL, 0));
	i = 0;
	while (dest[i])
	{
		temp[i] = dest[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*sl_read_lines(int fd, char *dest, char *buf)
{
	int	check;

	check = 1;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (ft_free(dest, NULL, 0));
	while (1)
	{
		check = read(fd, buf, BUFFER_SIZE);
		if (check < 0)
			return (ft_free(dest, buf, 0));
		buf[check] = '\0';
		if (check == 0)
		{
			if (*dest == '\0' || !dest)
				return (ft_free(dest, buf, 0));
			break ;
		}
		dest = ft_free(dest, buf, 1);
		if (ft_strchr(buf, '\0') || (check < BUFFER_SIZE && *dest))
			break ;
	}
	free(buf);
	return (dest);
}

char	*sl_get_next_line(int fd)
{
	static char	*dest;
	char		*ret_line;
	char		*buf;

	buf = NULL;
	if (fd < 0)
		return (NULL);
	if (!dest)
	{
		dest = ft_strdup("");
		if (!dest)
			return (NULL);
	}
	dest = sl_read_lines(fd, dest, buf);
	if (!dest)
		return (NULL);
	ret_line = sl_create_line(dest);
	if (!ret_line)
		return (ft_free(dest, NULL, 0));
	dest = sl_ft_remainder(dest);
	return (ret_line);
}

char	**create_map(int fd)
{
	char	*txt;
	char	*temp;
	char	*new_txt;
	char	**full_txt;

	new_txt = NULL;
	txt = ft_strdup("");
	while (1)
	{
		temp = sl_get_next_line(fd);
		if (!temp)
			break ;
		new_txt = ft_strjoin(txt, temp);
		free(txt);
		free(temp);
		txt = new_txt;
	}
	if (txt[0] == 0)
		return (free(txt), NULL);
	full_txt = ft_split(txt, '\n');
	free(new_txt);
	return (full_txt);
}

int	validate_map(char **map)
{
	int	a;
	int	b;
	int	length[2];
	int	start_exit;
	int	collect;

	a = 0;
	length[0] = 0;
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
	return (collect + start_exit);
}

void	fill_grid(char **map, int x, int y, int length[], int *count)
{
	if (map[x][y] == 'C' || map[x][y] == 'E')
		(*count)++;
	if (map[x][y] == '1' || map[x][y] == 'F' || map[x][y] == 'E')
		return ;
	map[x][y] = 'F';
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
	int length[2];
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

int	main(int argc, char *argv[])
{
	int		fd;
	char	**map;
	int		collect_nb;
	int		flood;
	int		a;

	if (argc != 2)
		exit(1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (perror("Error\nMessage"), 1);
	map = create_map(fd);
	if (!map)
		exit(1);
	collect_nb = validate_map(map);
	if (collect_nb == 1)
		return (printf("Error\nInvalid map"), 1);
	flood = flood_fill(map);
	printf("%i\n", collect_nb);
	if (collect_nb != flood)
		return (printf("Error\nNot all collectibles reachable"));
	a = 0;
	while (map[a])
		printf("%s\n", map[a++]);
	ft_freeme(map, a);
}
