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

char	*create_map(int argc, char *argv[], int fd)
{
	char	*txt;
	char	*temp;
	char	*new_txt;
	char	**full_txt;
	int		a;

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
	full_txt = ft_split(txt, '\n');
	free(new_txt);
	a = 0;
	while (full_txt[a])
	{
		printf("%s\n", full_txt[a]);
		a++;
	}
}

int	main(int argc, char *argv[])
{
	int		fd;
	char	*map;
	int		error;

	if (argc != 2)
		exit(1);
	fd = open("map.ber", O_RDONLY);
	if (fd < 0)
		return (0);
	map = create_map(argc, argv, fd);
	//error = validate_map(map);
	// ft_freeme(map, a);
}


