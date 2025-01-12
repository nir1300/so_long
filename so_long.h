#ifndef SOLONG_H
# define SOLONG_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdarg.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <bsd/string.h>
# include <errno.h>
# include "libft/libft.h"
# include <X11/keysym.h>

typedef struct s_map {
    char **content;
    char **cpy;
    char *line;
    int x_len;
    int y_len;
}               t_map;

typedef struct s_img {
    void *grass;
    void *tree;
    void *collect;
    void *player;
    void *exit;
}               t_img;


typedef struct s_mlx_data
{
    void *mlx_ptr;
    int x_pos;
    int y_pos;
    void *win_ptr;
    int collect_total;
    int collected;
    int moves;
    t_map *map;
    t_img img;
}           t_mlx_data;

// so_long



#endif
