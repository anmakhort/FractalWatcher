#include "../include/graphics.h"
#include "../include/concolor.h"
#include "../include/mlx_screenshot.h"
#include "../include/helpwnd.h"

static char _images_dir_[64] = {0};
static unsigned int n_snap = 0;

int	key_released(int key, void *param) {
	if (!param) return 1;
	
	sender_t *sender = (sender_t *)param;

	if (key == KEYBOARD_EXIT_KEY || key == KEYBOARD_QUIT_KEY) {
		cleanup(sender);
		exit(0);
	}

	double dX = sender->c_plane.x_max-sender->c_plane.x_min;
	double dY = sender->c_plane.y_max-sender->c_plane.y_min;
	
	switch (key) {
		case KEYBOARD_ZOOM_IN:
			sender->zoom += GET_ZOOM_DELTA(sender->zoom);
			if (sender->zoom > MAX_ZOOM) sender->zoom = MAX_ZOOM;
			sender->need_update |= NEED_FULL_REPAINT;
			break;

		case KEYBOARD_ZOOM_OUT:
			sender->zoom -= GET_ZOOM_DELTA(sender->zoom);
			if (sender->zoom <= MIN_ZOOM) sender->zoom = MIN_ZOOM;
			sender->need_update |= NEED_FULL_REPAINT;
			break;

		case KEYBOARD_NORMAL:
			sender->zoom = 1.;
			sender->need_update = NEED_FULL_REPAINT;
			break;

		case KEYBOARD_LEFT_KEY:
			sender->offset_pt.x -= dX*sender->move_scale;
			sender->need_update |= NEED_FULL_REPAINT;
			break;

		case KEYBOARD_RIGHT_KEY:
			sender->offset_pt.x += dX*sender->move_scale;
			sender->need_update |= NEED_FULL_REPAINT;
			break;

		case KEYBOARD_UP_KEY:
			sender->offset_pt.y -= dY*sender->move_scale;
			sender->need_update |= NEED_FULL_REPAINT;
			break;

		case KEYBOARD_DOWN_KEY:
			sender->offset_pt.y += dY*sender->move_scale;
			sender->need_update |= NEED_FULL_REPAINT;
			break;

		case KEYBOARD_O_KEY:
			sender->move_scale += MOVE_SCALE_DELTA;
			if (sender->move_scale >= MAX_MOVE_SCALE) \
				sender->move_scale = MAX_MOVE_SCALE;
			sender->need_update |= NEED_TEXT_UPDATE;
			break;

		case KEYBOARD_I_KEY:
			sender->move_scale -= MOVE_SCALE_DELTA;
			if (sender->move_scale <= MIN_MOVE_SCALE) \
				sender->move_scale = MIN_MOVE_SCALE;
			sender->need_update |= NEED_TEXT_UPDATE;
			break;

		case KEYBOARD_A_KEY:
			sender->need_update ^= NEED_ZOOM_RENDER;
			break;

		case KEYBOARD_K_KEY:
			sender->n_iters -= ITERATIONS_DELTA;
			if (sender->n_iters <= MIN_ITERATIONS) \
				sender->n_iters = MIN_ITERATIONS;
			sender->need_update |= NEED_FULL_REPAINT;
			break;

		case KEYBOARD_L_KEY:
			sender->n_iters += ITERATIONS_DELTA;
			if (sender->n_iters >= MAX_ITERATIONS) \
				sender->n_iters = MAX_ITERATIONS;
			sender->need_update |= NEED_FULL_REPAINT;
			break;

		case KEYBOARD_N_KEY:
			sender->n_iters = NORMAL_ITERATIONS;
			sender->need_update |= NEED_FULL_REPAINT;
			break;

		case KEYBOARD_C_KEY:
			sender->offset_pt.x = 0.;
			sender->offset_pt.y = 0.;
			sender->need_update |= NEED_FULL_REPAINT;
			break;

		case KEYBOARD_M_KEY:
		case KEYBOARD_J_KEY:
				sender->n_iters = NORMAL_ITERATIONS;
				sender->offset_pt.x = 0.;
				sender->offset_pt.y = 0.;
				sender->mandelbrot = (key == KEYBOARD_M_KEY);
				sender->need_update |= NEED_FULL_REPAINT;
			break;

		case KEYBOARD_S_KEY:
			if (!sender->mandelbrot) {
				sender->save_position = !sender->save_position;
				sender->need_update |= NEED_TEXT_UPDATE;
			}
			return 0;

		case KEYBOARD_B_KEY:
			if (!_images_dir_[0]) prepare_saving_dir_and_path(_images_dir_, IMAGES_BASE_DIR);
			mlx_snap_window(sender->hWnd.mlx_ptr, sender->hWnd.mlx_win, _images_dir_, \
				(sender->mandelbrot ? "sender->mandelbrot" : "Julia"), (++n_snap), FORMAT_BMP);
			break;

		case KEYBOARD_P_KEY:
			if (!_images_dir_[0]) prepare_saving_dir_and_path(_images_dir_, IMAGES_BASE_DIR);
			mlx_snap_window(sender->hWnd.mlx_ptr, sender->hWnd.mlx_win, _images_dir_, \
				(sender->mandelbrot ? "sender->mandelbrot" : "Julia"), (++n_snap), FORMAT_PNG);
			break;

		case KEYBOARD_H_KEY:
			show_help_window(sender->hWnd.mlx_ptr);
			break;

		case KEYBOARD_0_KEY:
			sender->coloring_idx = 0;
			sender->need_update |= (NEED_COLORING | NEED_TEXT_UPDATE);
			break;
		case KEYBOARD_1_KEY:
			sender->coloring_idx = 1;
			sender->need_update |= (NEED_COLORING | NEED_TEXT_UPDATE);
			break;
		case KEYBOARD_2_KEY:
			sender->coloring_idx = 2;
			sender->need_update |= (NEED_COLORING | NEED_TEXT_UPDATE);
			break;
		case KEYBOARD_3_KEY:
			sender->coloring_idx = 3;
			sender->need_update |= (NEED_COLORING | NEED_TEXT_UPDATE);
			break;
		case KEYBOARD_4_KEY:
			sender->coloring_idx = 4;
			sender->need_update |= (NEED_COLORING | NEED_TEXT_UPDATE);
			break;
		case KEYBOARD_5_KEY:
			sender->coloring_idx = 5;
			sender->need_update |= (NEED_COLORING | NEED_TEXT_UPDATE);
			break;
		case KEYBOARD_6_KEY:
			sender->coloring_idx = 6;
			sender->need_update |= (NEED_COLORING | NEED_TEXT_UPDATE);
			break;
		case KEYBOARD_7_KEY:
			sender->coloring_idx = 7;
			sender->need_update |= (NEED_COLORING | NEED_TEXT_UPDATE);
			break;
		case KEYBOARD_8_KEY:
			sender->coloring_idx = 8;
			sender->need_update |= (NEED_COLORING | NEED_TEXT_UPDATE);
			break;
		case KEYBOARD_9_KEY:
			sender->coloring_idx = 9;
			sender->need_update |= (NEED_COLORING | NEED_TEXT_UPDATE);
			break;

		default:
			sender->need_update = NEED_DO_NOP;
			break;
	}
	if (sender->need_update & (NEED_ZOOM_RENDER | NEED_FULL_REPAINT)) {
		sender->c_plane.x_min = SCREEN_TO_CX_MIN / sender->zoom;
		sender->c_plane.x_max = SCREEN_TO_CX_MAX / sender->zoom;
		sender->c_plane.y_min = SCREEN_TO_CY_MIN / sender->zoom;
		sender->c_plane.y_max = SCREEN_TO_CY_MAX / sender->zoom;
	}
	return 0;
}