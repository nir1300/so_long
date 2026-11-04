# Define variables
NAME = so_long
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Includes
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I libft -I .

# Files
CFILES = main.c events.c graphics.c helper.c map.c
OFILES = $(CFILES:.c=.o)

# Compilation rules
all: $(LIBFT_BONUS) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) bonus

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -g -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OFILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OFILES) -g -L$(LIBFT_DIR) -lft -Lmlx_linux -Imlx_Linux -lmlx -lXext -lX11 -lm -lz -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OFILES)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re

