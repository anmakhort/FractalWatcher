#include <stdio.h>
#include <string.h>
#include "../include/endiannes.h"
#include "../include/concolor.h"
#include "../include/graphics.h"
#include "../minilibx/mlx.h"
#include "../minilibx/mlx_int.h"

sender_t *sender;

int main() {
    sender = malloc(sizeof(sender_t));
    memset(sender, 0, sizeof(sender_t));

#ifdef _VERBOSE
	sender->cntr = 0;
#endif
	sender->coloring_idx = 0;
	sender->n_iters = NORMAL_ITERATIONS;
	sender->save_position = 0;
	sender->need_update = NEED_DO_NOP;
	sender->mandelbrot = 1;
	sender->mouse_pt.x = sender->mouse_pt.y = 0.;
    sender->mouse_coord.x = sender->mouse_coord.y = 0;
	sender->move_scale = 0.5;
	sender->zoom = 1.;
	sender->julia_pt.x = sender->julia_pt.y = 0.;
	sender->offset_pt.x = sender->offset_pt.y = 0.;
	sender->c_plane.x_min = SCREEN_TO_CX_MIN;
	sender->c_plane.x_max = SCREEN_TO_CX_MAX;
	sender->c_plane.y_min = SCREEN_TO_CY_MIN;
	sender->c_plane.y_max = SCREEN_TO_CY_MAX;
	sender->endian = is_BigEndian();
#ifdef _VERBOSE
	printf("[%u] ENDIAN -- %s\n", ++sender->cntr, (!sender->endian ? BOLD("Little", _FG_YELLOW_) : BOLD("Big", _FG_YELLOW_)));
#endif

	if ((sender->hWnd.mlx_ptr = mlx_init()) == NULL) {
#ifdef _VERBOSE
		printf(BOLD("ERROR: ", _FG_RED_) "Can't init the GUI!\n");
#endif
        cleanup(sender);
		exit(1);
	}
#ifdef _VERBOSE
	else {
		printf("[%u] Init -- " BOLD("OK", _FG_GREEN_) "\n", ++sender->cntr);
	}
#endif

    sender->hWnd.mlx_win = mlx_new_window(sender->hWnd.mlx_ptr, IMAGE_BUFFER_WIDTH, IMAGE_BUFFER_HEIGHT, WND_TITLE, WND_BG_COLOR);
    if (!sender->hWnd.mlx_win) {
#ifdef _VERBOSE
    	printf(BOLD("ERROR: ", _FG_RED_) "Can't create a new window!\n");
#endif
        cleanup(sender);
    	exit(1);
    }
#ifdef _VERBOSE
    else {
    	printf("[%u] Create window -- " BOLD("OK", _FG_GREEN_) "\n", ++sender->cntr);
    }
#endif

    sender->header.width = IMAGE_BUFFER_WIDTH;
    sender->header.height = IMAGE_BUFFER_HEIGHT;
    sender->image.img_buff = mlx_new_image(sender->hWnd.mlx_ptr, sender->header.width, sender->header.height);

    if (!sender->image.img_buff) {
#ifdef _VERBOSE
    	printf(BOLD("ERROR: ", _FG_RED_) "Can't allocate image buffer for window!\n");
#endif
        cleanup(sender);
    	exit(1);
    }
#ifdef _VERBOSE
    else {
    	printf("[%u] Image buffer allocation -- " BOLD("OK", _FG_GREEN_) "\n", ++sender->cntr);
    }
#endif

    sender->image.img_drawer_ptr = \
        mlx_get_data_addr(sender->image.img_buff, &sender->header.bpp, &sender->header.sz_line, &sender->endian);
#ifdef _VERBOSE
    printf("[%u] Image Drawer -- " BOLD("OK", _FG_GREEN_) "\t" \
    	BOLD("(bpp: %d, sizeline: %d endian: %d type: %d)\n", _FG_MAGENTA_),\
    	++sender->cntr, sender->header.bpp, sender->header.sz_line, sender->endian, ((t_img *)sender->image.img_buff)->type);
#endif

    if (!sender->image.img_drawer_ptr) {
#ifdef _VERBOSE
        printf(BOLD("ERROR: ", _FG_RED_) "Can't access image buffer!\n");
#endif
        cleanup(sender);
        exit(1);
    }

    mlx_key_hook(sender->hWnd.mlx_win, key_released, (void *)sender);
    mlx_hook(sender->hWnd.mlx_win, MotionNotify, PointerMotionMask, mouse_move, (void *)sender);
    mlx_loop_hook(sender->hWnd.mlx_ptr, my_loop, (void *)sender);

    sender->need_update = NEED_FULL_REPAINT;

    mlx_loop(sender->hWnd.mlx_ptr);

	return 0;
}