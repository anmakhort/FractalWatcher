#include <stdio.h>
#include <string.h>
#include "../include/graphics.h"
#include "../include/concolor.h"
#include "../minilibx/mlx.h"
#include "../minilibx/mlx_int.h"

int my_loop(void *param) {
	if (!param) return -1;
	sender_t *sender = (sender_t *)param;

	if (sender->need_update == NEED_DO_NOP) return 0;

	if (sender->need_update & NEED_ZOOM_RENDER) {
		if (sender->zoom < MAX_ANIMATE_ZOOM) {
			sender->zoom += GET_ANIMATE_ZOOM_DELTA(sender->zoom);
			sender->c_plane.x_min = SCREEN_TO_CX_MIN / sender->zoom;
			sender->c_plane.x_max = SCREEN_TO_CX_MAX / sender->zoom;
			sender->c_plane.y_min = SCREEN_TO_CY_MIN / sender->zoom;
			sender->c_plane.y_max = SCREEN_TO_CY_MAX / sender->zoom;
			sender->need_update |= NEED_FULL_REPAINT;
		} else {
			sender->need_update &= (~NEED_ZOOM_RENDER) | (~NEED_FULL_REPAINT);
			return 0;
		}
	}

	if (sender->need_update & NEED_FULL_REPAINT) {
		render(sender, IMAGE_BUFFER_WIDTH, IMAGE_BUFFER_HEIGHT);
		sender->need_update &= ~NEED_FULL_REPAINT;
		sender->need_update |= (NEED_COLORING | NEED_TEXT_UPDATE);
	}

	if (sender->need_update & NEED_COLORING) {
		mlx_clear_window(sender->hWnd.mlx_ptr, sender->hWnd.mlx_win);
		coloring(sender, IMAGE_BUFFER_WIDTH, IMAGE_BUFFER_HEIGHT);
		sender->need_update &= ~NEED_COLORING;
	}

	//mlx_clear_window(sender->hWnd.mlx_ptr, sender->hWnd.mlx_win);
	mlx_put_image_to_window(sender->hWnd.mlx_ptr, sender->hWnd.mlx_win, sender->image.img_buff, 0, 0);
#ifdef _VERBOSE
  	printf("[%u] Put Image -- " BOLD("OK", _FG_GREEN_) "\n", ++sender->cntr);
#endif

	if (sender->need_update & NEED_TEXT_UPDATE) {
		char str[128] = {0};
		sprintf(str, "Mouse: (%.10f;%.10f) | magn: %.2fx | offest: [%.2fx (%.8f;%8f)] | iterations: %i/%i", \
					sender->mouse_pt.x, sender->mouse_pt.y, sender->zoom, sender->move_scale, \
					sender->offset_pt.x, sender->offset_pt.y, \
					sender->calculated[sender->mouse_coord.x][sender->mouse_coord.y].iters, sender->n_iters);
		
		mlx_string_put(sender->hWnd.mlx_ptr, sender->hWnd.mlx_win, 5, 12, 0xff00ff, str);

		if (!sender->mandelbrot) {
			mlx_string_put(sender->hWnd.mlx_ptr, sender->hWnd.mlx_win, 5, 25, 0x00b0af, "Julia");

			memset(str, 0, 128);
			sprintf(str, "z=(%.8f;%.8f)", sender->julia_pt.x, sender->julia_pt.y);
			mlx_string_put(sender->hWnd.mlx_ptr, sender->hWnd.mlx_win, 45, 25, 0x00b0af, str);

			if (sender->save_position)
				mlx_string_put(sender->hWnd.mlx_ptr, sender->hWnd.mlx_win, 230, 25, 0x0f5f5f, "Position saved (Undo: press 's')");
		} else
			mlx_string_put(sender->hWnd.mlx_ptr, sender->hWnd.mlx_win, 5, 25, 0x00b00af, "Mandelbrot");

		sender->need_update &= ~NEED_TEXT_UPDATE;
	}

	return 0;
}