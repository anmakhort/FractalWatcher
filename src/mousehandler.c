#include "../include/graphics.h"
#include "../include/transform.h"

int mouse_move(int x, int y, void *param) {
	if (!param) return -1;
	
	sender_t *sender = (sender_t *)param;
	if (sender->need_update) return 1;

	sender->mouse_coord.x = x;
	sender->mouse_coord.y = y;
	
	sender->mouse_pt.x = affine_transf(x, IMAGE_BUFFER_WIDTH, sender->c_plane.x_min, sender->c_plane.x_max);
	sender->mouse_pt.y = affine_transf(y, IMAGE_BUFFER_HEIGHT, sender->c_plane.y_min, sender->c_plane.y_max);
	if (!sender->mandelbrot) {
		if (!sender->save_position) {
			sender->julia_pt.x = affine_transf(x, IMAGE_BUFFER_WIDTH, JULIA_SCREEN_TO_CX_MIN, JULIA_SCREEN_TO_CX_MAX);
			sender->julia_pt.y = affine_transf(y, IMAGE_BUFFER_HEIGHT, JULIA_SCREEN_TO_CY_MIN, JULIA_SCREEN_TO_CY_MAX);
			sender->need_update = NEED_FULL_REPAINT;
		} else sender->need_update = NEED_TEXT_UPDATE;
	} else sender->need_update = NEED_TEXT_UPDATE;
	
	return 0;
}