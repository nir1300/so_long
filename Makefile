# Define variables
NAME = so_long.a
CC = cc
CFLAGS = -Wall -Werror -Wextra

# Includes
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I libft -I .

# Files
CFILES = validate_map.c
OFILES = $(CFILES:.c=.o)

# Compilation rules
all: $(LIBFT_BONUS) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) bonus

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OFILES) $(LIBFT)
	$(CC) $(CFLAGS) $(OFILES) -L$(LIBFT_DIR) -lft -Lmlx_linux -Imlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	make clean -C $(LIBFT_DIR)
	rm -f $(OFILES)

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
