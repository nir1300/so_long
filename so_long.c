/* 
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

// clang so_long.c -lX11 -lXext -lmlx
// https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html


// draw different shapes
// include map
// 
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int main(void)
{
    if (argc != 2)
        exit (1);
    if (strnstr(argv[1], ".ber", strlen(argv[1])) == NULL)
        exit (1);

    t_data  img;
    void *mlx;
    void *mlx_win; 
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello");
    int left = 50;
    int top = 50;

    img.img = mlx_new_image(mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
    while (left++ <= 500 && top++ <= 500)
    {
        my_mlx_pixel_put(&img, left, top, 0x00FF0000);
        mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
    }

    mlx_hook(img.win, 2, 1L<<0, close, &vars);
    mlx_loop(mlx);
    // mlx_toop(img.mlx);
}

// use ESC or clicking on windows cross to close program: create event with mlx_loop

// structure:
// build background
// draw map incl collectibles, walls, start and end
// draw player

// 1. step: validate map
    // check only 1 exit and entrance
    // check if chars are valid
    // check there is a possible way to reach the goal without walls abstracting it
 */