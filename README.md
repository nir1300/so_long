# so_long

A small 2D tile-based game written in C with **MiniLibX**. You guide a character through a forest map, collect every mushroom, and then walk to the exit. Maps are plain text `.ber` files that the program parses and validates before opening a window.

Written for the 42 curriculum.

## Gameplay

- Move with **W A S D** or the **arrow keys**.
- Walls (trees) block movement.
- Collect every mushroom (`C`) on the map; the exit (`E`) stays closed until you have them all.
- Walking onto the exit after collecting everything ends the game.
- The move counter is printed to the terminal after every step (`Moves: N`).
- **ESC** or the window's close button quits cleanly.

## Build and run

Requires the Linux version of MiniLibX, expected in a `mlx_linux/` directory next to the sources (the Makefile links with `-lmlx -lXext -lX11 -lm -lz`).

```bash
make
./so_long map.ber
```

Map files are loaded from the `maps/` folder: the argument is the file name only, and the program opens `maps/<name>`. Textures are loaded from `textures/` (`grass.xpm`, `tree.xpm`, `player.xpm`, `exit.xpm`, `mushroom.xpm`).

Other targets: `make clean`, `make fclean`, `make re`. The bundled `libft` is built through its own Makefile.

## Map format

| Char | Meaning |
|------|---------|
| `0` | free space (grass) |
| `1` | wall (tree) |
| `C` | collectible (mushroom) |
| `E` | exit |
| `P` | player start |

```
1111111111111
10010000000C1
1000011111001
1P0011E000001
1111111111111
```

## Map validation

The map is checked before any window is created. Every failure prints `Error` followed by a specific message and exits cleanly with all memory freed.

1. The argument must be a `.ber` file and must open successfully.
2. The file is read line by line with `get_next_line`, joined into one string, rejected if it contains empty lines, and split into rows with `ft_split`.
3. The map must be rectangular, no larger than **50 x 24 tiles**, and made only of `0 1 C E P`.
4. The outer border must consist entirely of walls.
5. It must contain at least one collectible.
6. A **flood fill** starting from the player's position checks reachability on a copy of the grid: every collectible must be reached, and the exit must be reachable too. The exit tile stops the fill so it cannot be walked through to reach other tiles.

Keeping two copies of the grid (`content` for the game, `cpy` for the flood fill) means validation never changes the map that is later drawn.

## How it works

- **Rendering.** Each tile is 38 x 38 pixels, so the window size is the map size times 38. All sprites are loaded once as MiniLibX images, and the whole map is drawn once at startup. After that only two tiles change per move: the tile being left is redrawn as grass and the player is drawn on the new tile, so there is no full-screen redraw.
- **Collecting.** Stepping onto a `C` tile turns it into `0` in the map and increments the collected counter. The move is rejected if the target is a wall, or the exit while items remain.
- **Events.** `mlx_key_hook` handles keyboard input and `mlx_hook` with event 17 handles the window's close button. Both go through the same cleanup routine that destroys the images, window and display and frees the map data.

## Project structure

| File | Contents |
|------|----------|
| `main.c` | argument checks, initialization, window creation and the MiniLibX loop |
| `map.c` | map reading, validation and flood fill |
| `events.c` | key handling, movement and collection logic |
| `graphics.c` | texture loading and tile drawing |
| `helper.c` | cleanup and utility functions |
| `so_long.h` | structures and prototypes |
| `maps/`, `textures/` | map files and XPM sprites |
| `libft/` | bundled `libft` (including `ft_printf` / `get_next_line`) |
