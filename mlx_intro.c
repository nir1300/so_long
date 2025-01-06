#include "so_long.h"

// 1: establish connection

/* int main(void)
{
    void *mlx_ptr;
    mlx_ptr = mlx_init();
    if (!mlx_ptr)
        return (1);
    // connect to x-window server, mallocs -> free later with mlx_destroy_display
    // creates and return a structure
    mlx_destroy_display(mlx_ptr);
    free (mlx_ptr);
} */

// 2: create windows

/* int main(void)
{
    void *mlx_ptr;
    void *window1;
    void *window2;
    int height = 400;
    int width = 400;

    mlx_ptr = mlx_init();
    if (!mlx_ptr)
        return (1);
    // create new window, can have multiple windows in program
    window1 = mlx_new_window(mlx_ptr, height, width, "Window 1");
    if (!window1)
    {
        mlx_destroy_display(mlx_ptr);
        free (mlx_ptr);
        return (1);
    }
    window2 = mlx_new_window(mlx_ptr, height, width, "Window 2");
    if (!window2)
    {
        mlx_destroy_display(mlx_ptr);
        free (mlx_ptr);
        return (1);
    }
    mlx_loop(mlx_ptr);
} */

// 3: events - mlx_key_hook, mlx_hook, mlx_loop_hook


/* typedef struct s_mlx_data
{
    void *mlx_ptr;
    void *win_ptr;
}           t_mlx_data;

int handle_input(int keysym, t_mlx_data *data)
{
    // XK_Escape defined in library X11/keysym.h
    // difference between keycode and keysym
    // keycode -> in mac you get keycodes, hardware specific, tied to keyboard, differs between QWERTY and QWERTZ eg
    // keysym: more abstract, more portable
    if (keysym == XK_Escape)
    {
        printf("The %d key (ESC) has been pressed\n\n", keysym);
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        mlx_destroy_display(data->mlx_ptr);
        free (data->mlx_ptr);
        exit(1);
    }
    // find keysym with this print -> saved in keysym.txt
    printf("The %d key has been pressed\n\n", keysym);
    return (0);
}

int main(void)
{
    t_mlx_data  data;
    int height = 400;
    int width = 400;
    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
        return (1);
    // create new window, can have multiple windows in program
    data.win_ptr = mlx_new_window(data.mlx_ptr, height, width, "Window 1");
    if (!data.win_ptr)
    {
        mlx_destroy_display(data.mlx_ptr);
        free (data.mlx_ptr);
        return (1);
    }
    // event: press a key
    // hooks: something happens after pressing a key, reacts to an event
    // handler function: tells the system how to react to the event    
    mlx_key_hook(data.win_ptr, handle_input, &data);
    mlx_loop(data.mlx_ptr);
} */

// 3: events - mlx_key_hook, mlx_hook, mlx_loop_hook
#include <X11/keysym.h>

typedef struct s_mlx_data
{
    void *mlx_ptr;
    void *win_ptr;
}           t_mlx_data;

int button_press(int button, int x, int y, t_mlx_data *data)
{
    // x and y are coordinates: where in the window was clicked?
    if (button == 1)
        printf("Left mouse button has been pressed at (%d, %d)\n\n", x, y);
    else if (button == 3)
        printf("Right mouse button has been pressed at (%d, %d)\n\n", x, y);
    return (0);
}

int main(void)
{
    t_mlx_data  data;
    int height = 400;
    int width = 400;
    data.mlx_ptr = mlx_init();
    if (!data.mlx_ptr)
        return (1);
    // create new window, can have multiple windows in program
    data.win_ptr = mlx_new_window(data.mlx_ptr, height, width, "Window 1");
    if (!data.win_ptr)
    {
        mlx_destroy_display(data.mlx_ptr);
        free (data.mlx_ptr);
        return (1);
    }
    // event: press a key
    // hooks: something happens after pressing a key, reacts to an event
    // for hooks you need the event (button press), and the event mask (tells the X11 system it should notify you when this event occurs)
    // handler function: tells the system how to react to the event    
    mlx_hook(data.win_ptr, 4, 1L<<2, button_press, &data);
    // this is also valid: mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, button_press, &data);
    mlx_loop(data.mlx_ptr);
}

// mlx_loop_hook is continuosly rendering when there is no event processed
// use this to react to key presses

// what to use for background? just insert image?

//stopped listening youtube tutorial at 25 min


// which functions to use for what
// 1. initalize: mlx_init()
// 2. create a window: mlx_new_window()
// 3. react to key press: mlx_key_hook()
// 4. react to mouse click: mlx_mouse_hook()
// 5. redrawing content (backgroud, map, player?): mlx_expose_hook()
// 6. keep app running and listen for events: mlx_loop()
// 7. clear window before redrawing: mlx_clear_window()
