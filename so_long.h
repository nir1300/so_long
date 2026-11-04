/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrumpfhu <nrumpfhu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 17:59:14 by nrumpfhu          #+#    #+#             */
/*   Updated: 2025/01/31 14:43:55 by nrumpfhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include <X11/keysym.h>
# include <bsd/string.h>
# include <errno.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_map
{
	char	**content;
	char	**cpy;
	char	*txt;
	char	*temp;
	char	*new_txt;
}			t_map;

typedef struct s_img
{
	void	*grass;
	void	*tree;
	void	*shroom;
	void	*player;
	void	*exit;
}			t_img;

typedef struct s_mlx_data
{
	void	*mlx_ptr;
	char	*path;
	int		fd;
	int		a;
	int		b;
	int		x_pos;
	int		y_pos;
	int		x_len;
	int		y_len;
	int		x_count;
	int		y_count;
	int		se_count;
	void	*win_ptr;
	int		collect;
	int		collected;
	int		exit_reached;
	int		moves;
	t_map	*map;
	t_img	img;
}			t_mlx_data;

// main
int			game_loop(t_mlx_data *data);
void		initalize(t_mlx_data *data);
void		error(char *msg);
void		check_exit(t_mlx_data *data);

// helper
void		ft_freeme(char **arr);
int			ft_close(t_mlx_data *data);
void		free_struct(t_mlx_data *data, char *msg);

// graphics
void		draw_background(t_mlx_data *data);
int			loop_background(t_mlx_data *data);
int			load_images(t_mlx_data *data);

// map
int			create_map(int fd, t_map *map);
void		validate_map(char **map, t_mlx_data *data);
void		fill_grid(t_mlx_data *data, int x, int y, int *count);
int			flood_fill(t_mlx_data *data);
int			empty_lines(t_map *map);

// events
void		move(t_mlx_data *data, int new_x, int new_y);
int			handle_input(int keysym, t_mlx_data *data);
int			button_press(int button, t_mlx_data *data);

#endif
