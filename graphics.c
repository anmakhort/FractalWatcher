#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#include <math.h>

#include "concolor.h"
#include "graphics.h"
#include "mlx_screenshot.h"
#include "helpwnd.h"


int endian;

#ifdef _VERBOSE
counter_t cntr = 0;
#endif

static char _images_dir_[64];
static unsigned int n_snap = 0;

flag_t need_update = 0;
flag_t animate = 0;
flag_t mandelbrot = 1;
flag_t save_position = 0;

unsigned n_iters = NORMAL_ITERATIONS;

double julia_X = 0., julia_Y = 0.;
double mouse_X = 0., mouse_Y = 0.;
double offsetX = 0., offsetY = 0.;
double cx_0 = SCREEN_TO_CX_MIN, cx_1 = SCREEN_TO_CX_MAX;
double cy_0 = SCREEN_TO_CY_MIN, cy_1 = SCREEN_TO_CY_MAX;
double move_scale = 0.5;
double zoom = 1.;

image_header_t header;
image_t image;
wnd_handle_t hWnd;

int	fill_image(unsigned char *data, int bpp, int sl, int w, int h);
int my_loop();
int mouse_move(int x, int y);
int	key_released(int key);

void prepare_saving_dir_and_path(char *buff, const char *base_dir) {
	if (!buff) return;

	memcpy(buff, base_dir, strlen(base_dir));

	struct stat st = {0};
	if (stat(buff, &st) == -1) mkdir(buff, 0700);

	time_t t = time(NULL);
	struct tm local = *localtime(&t);
	sprintf(buff, "%s%d-%d-%d_%d:%d:%d/", buff, \
		local.tm_year+1900, local.tm_mon+1, local.tm_mday, \
		local.tm_hour, local.tm_min, local.tm_sec);

	if (stat(buff, &st) == -1) mkdir(buff, 0700);
}


int main() {
	prepare_saving_dir_and_path(_images_dir_, IMAGES_BASE_DIR);
#ifdef _VERBOSE
	printf("[%lu] SAVING DIRECTORY -- %s\n", ++cntr, BOLD(_images_dir_, _FG_GREEN_));
#endif

	endian = is_BigEndian();
#ifdef _VERBOSE
	printf("[%lu] ENDIAN -- %s\n", ++cntr, (!endian ? BOLD("Little", _FG_YELLOW_) : BOLD("Big", _FG_YELLOW_)));
#endif
	if ((hWnd.mlx_ptr = mlx_init()) == NULL) {
#ifdef _VERBOSE
		printf(BOLD("ERROR: ", _FG_RED_) "Can't init the GUI!\n");
#endif
		exit(1);
	}
#ifdef _VERBOSE
	else {
		printf("[%lu] Init -- " BOLD("OK", _FG_GREEN_) "\n", ++cntr);
	}
#endif

    hWnd.mlx_win = mlx_new_window(hWnd.mlx_ptr, IMAGE_BUFFER_WIDTH, IMAGE_BUFFER_HEIGHT, WND_TITLE, WND_BG_COLOR);
    if (!hWnd.mlx_win) {
#ifdef _VERBOSE
    	printf(BOLD("ERROR: ", _FG_RED_) "Can't create a new window!\n");
#endif
    	exit(1);
    }
#ifdef _VERBOSE
    else {
    	printf("[%lu] Create window -- " BOLD("OK", _FG_GREEN_) "\n", ++cntr);
    }
#endif

    header.width = IMAGE_BUFFER_WIDTH;
    header.height = IMAGE_BUFFER_HEIGHT;
    image.img_buff = mlx_new_image(hWnd.mlx_ptr, header.width, header.height);

    if (!image.img_buff) {
#ifdef _VERBOSE
    	printf(BOLD("ERROR: ", _FG_RED_) "Can't allocate image buffer for window!\n");
#endif
    	mlx_destroy_window(hWnd.mlx_ptr, hWnd.mlx_win);
    	exit(1);
    }
#ifdef _VERBOSE
    else {
    	printf("[%lu] Image buffer allocation -- " BOLD("OK", _FG_GREEN_) "\n", ++cntr);
    }
#endif

    image.img_drawer_ptr = mlx_get_data_addr(image.img_buff, &header.bpp, &header.sz_line, &endian);
#ifdef _VERBOSE
    printf("[%lu] Image Drawer -- " BOLD("OK", _FG_GREEN_) "\t" \
    	BOLD("(bpp: %d, sizeline: %d endian: %d type: %d)\n", _FG_MAGENTA_),\
    	++cntr, header.bpp, header.sz_line, endian, ((t_img *)image.img_buff)->type);
#endif

    fill_image(image.img_drawer_ptr, header.bpp, header.sz_line, IMAGE_BUFFER_WIDTH, IMAGE_BUFFER_HEIGHT);
#ifdef _VERBOSE
    printf("[%lu] Fill Image -- " BOLD("OK", _FG_GREEN_) "\t" BOLD("(pixmap : %d)", _FG_MAGENTA_) "\n", ++cntr, \
    	(int)((t_img *)image.img_buff)->pix);
#endif

  	mlx_put_image_to_window(hWnd.mlx_ptr, hWnd.mlx_win, image.img_buff, 0, 0);
#ifdef _VERBOSE
  	printf("[%lu] Put Image -- " BOLD("OK", _FG_GREEN_) "\n", ++cntr);
#endif

    mlx_key_hook(hWnd.mlx_win, key_released, NULL);
    mlx_hook(hWnd.mlx_win, MotionNotify, PointerMotionMask, mouse_move, NULL);
    mlx_loop_hook(hWnd.mlx_ptr, my_loop, NULL);

    need_update = 1;

    mlx_loop(hWnd.mlx_ptr);

	return 0;
}

int mouse_move(int x, int y) {
	if (need_update) return 1;
	mouse_X = affine_transf(x, IMAGE_BUFFER_WIDTH, cx_0, cx_1);
	mouse_Y = affine_transf(y, IMAGE_BUFFER_HEIGHT, cy_0, cy_1);
	if (!mandelbrot) {
		if (!save_position) {
			julia_X = affine_transf(x, IMAGE_BUFFER_WIDTH, JULIA_SCREEN_TO_CX_MIN, JULIA_SCREEN_TO_CX_MAX);
			julia_Y = affine_transf(y, IMAGE_BUFFER_HEIGHT, JULIA_SCREEN_TO_CY_MIN, JULIA_SCREEN_TO_CY_MAX);
		}
		need_update = 1;
	} else need_update = 2;
	return 0;
}

int	key_released(int key) {
	if (key == KEYBOARD_EXIT_KEY || key == KEYBOARD_QUIT_KEY) {
		mlx_destroy_image(hWnd.mlx_ptr, image.img_buff);
#ifdef _VERBOSE
  		printf("[%lu] Destroy Image -- " BOLD("OK", _FG_GREEN_) "\n", ++cntr);
#endif
		mlx_destroy_window(hWnd.mlx_ptr, hWnd.mlx_win);
		exit(0);
	}
	double dX = cx_1-cx_0, dY = cy_1-cy_0;
	switch (key) {
		case KEYBOARD_ZOOM_IN:
			zoom += GET_ZOOM_DELTA(zoom);
			if (zoom > MAX_ZOOM) zoom = MAX_ZOOM;
			need_update = 1;
			break;
		case KEYBOARD_ZOOM_OUT:
			zoom -= GET_ZOOM_DELTA(zoom);
			if (zoom <= MIN_ZOOM) zoom = MIN_ZOOM;
			need_update = 1;
			break;
		case KEYBOARD_NORMAL:
			zoom = 1.;
			need_update = 1;
			break;
		case KEYBOARD_LEFT_KEY:
			offsetX -= dX*move_scale;
			need_update = 1;
			break;
		case KEYBOARD_RIGHT_KEY:
			offsetX += dX*move_scale;
			need_update = 1;
			break;
		case KEYBOARD_UP_KEY:
			offsetY -= dY*move_scale;
			need_update = 1;
			break;
		case KEYBOARD_DOWN_KEY:
			offsetY += dY*move_scale;
			need_update = 1;
			break;
		case KEYBOARD_O_KEY:
			move_scale += MOVE_SCALE_DELTA;
			if (move_scale >= MAX_MOVE_SCALE) \
				move_scale = MAX_MOVE_SCALE;
			need_update = 2;
			break;
		case KEYBOARD_I_KEY:
			move_scale -= MOVE_SCALE_DELTA;
			if (move_scale <= MIN_MOVE_SCALE) \
				move_scale = MIN_MOVE_SCALE;
			need_update = 2;
			break;
		case KEYBOARD_A_KEY:
			animate = !animate;
			need_update = (animate ? 3 : 0);
			break;
		case KEYBOARD_K_KEY:
			n_iters -= ITERATIONS_DELTA;
			if (n_iters <= MIN_ITERATIONS) \
				n_iters = MIN_ITERATIONS;
			need_update = 1;
			break;
		case KEYBOARD_L_KEY:
			n_iters += ITERATIONS_DELTA;
			if (n_iters >= MAX_ITERATIONS) \
				n_iters = MAX_ITERATIONS;
			need_update = 1;
			break;
		case KEYBOARD_N_KEY:
			n_iters = NORMAL_ITERATIONS;
			need_update = 1;
			break;
		case KEYBOARD_C_KEY:
			offsetX = 0.;
			offsetY = 0.;
			need_update = 1;
			break;
		case KEYBOARD_M_KEY:
			if (!mandelbrot) {
				n_iters = NORMAL_ITERATIONS;
				offsetX = 0.;
				offsetY = 0.;
				mandelbrot = 1;
				need_update = 1;
			}
			break;
		case KEYBOARD_J_KEY:
			if (mandelbrot) {
				n_iters = NORMAL_ITERATIONS;
				offsetX = 0.;
				offsetY = 0.;
				mandelbrot = 0;
				need_update = 1;
			}
			break;
		case KEYBOARD_S_KEY:
			save_position = !save_position;
			need_update = 2;
			break;
		case KEYBOARD_B_KEY:
			mlx_snap_window(hWnd.mlx_ptr, hWnd.mlx_win, _images_dir_, \
				(mandelbrot ? "Mandelbrot" : "Julia"), (++n_snap), FORMAT_BMP);
			break;
		case KEYBOARD_P_KEY:
			mlx_snap_window(hWnd.mlx_ptr, hWnd.mlx_win, _images_dir_, \
				(mandelbrot ? "Mandelbrot" : "Julia"), (++n_snap), FORMAT_PNG);
			break;
		case KEYBOARD_H_KEY:
			show_help_window(hWnd.mlx_ptr);
			break;
		default:
			return 1;
	}
	if (need_update == 1) {
		cx_0 = SCREEN_TO_CX_MIN / zoom;
		cx_1 = SCREEN_TO_CX_MAX / zoom;
		cy_0 = SCREEN_TO_CY_MIN / zoom;
		cy_1 = SCREEN_TO_CY_MAX / zoom;
	}
	return 0;
}

int my_loop() {
	if (need_update) {
		if (need_update == 3) {
			if (zoom < MAX_ANIMATE_ZOOM) {
				zoom += GET_ANIMATE_ZOOM_DELTA(zoom);
				cx_0 = SCREEN_TO_CX_MIN / zoom;
				cx_1 = SCREEN_TO_CX_MAX / zoom;
				cy_0 = SCREEN_TO_CY_MIN / zoom;
				cy_1 = SCREEN_TO_CY_MAX / zoom;
			} else {
				animate = 0;
				need_update = 0;
				return 0;
			}
		}
		if (need_update == 1 || need_update == 3) {
			mlx_clear_window(hWnd.mlx_ptr, hWnd.mlx_win);

			fill_image(image.img_drawer_ptr, header.bpp, header.sz_line, header.width, header.height);
#ifdef _VERBOSE
    		printf("[%lu] Fill Image -- " BOLD("OK", _FG_GREEN_) "\t" BOLD("(pixmap : %d)", _FG_MAGENTA_) "\n", \
    			++cntr, (int)((t_img *)image.img_buff)->pix);
#endif
		}
		mlx_put_image_to_window(hWnd.mlx_ptr, hWnd.mlx_win, image.img_buff, 0, 0);
#ifdef _VERBOSE
  		printf("[%lu] Put Image -- " BOLD("OK", _FG_GREEN_) "\n", ++cntr);
#endif

  		char str[128] = {0};
		sprintf(str, "Mouse: (%.10f;%.10f) | magn: %.2fx | offest: [%.2fx (%.8f;%8f)] | iterations: %i", \
			mouse_X, mouse_Y, zoom, move_scale, offsetX, offsetY, n_iters);
		mlx_string_put(hWnd.mlx_ptr, hWnd.mlx_win, 5, 12, 0xff00ff, str);

		if (!mandelbrot) {
			mlx_string_put(hWnd.mlx_ptr, hWnd.mlx_win, 5, 25, 0x00b0af, "Julia");

			memset(str, 0, 128);
			sprintf(str, "z=(%.8f;%.8f)", julia_X, julia_Y);
			mlx_string_put(hWnd.mlx_ptr, hWnd.mlx_win, 45, 25, 0x00b0af, str);

			if (save_position) {
				mlx_string_put(hWnd.mlx_ptr, hWnd.mlx_win, 230, 25, 0xff0000, "Position saved (Undo: press 's')");
			}
		} else {
			mlx_string_put(hWnd.mlx_ptr, hWnd.mlx_win, 5, 25, 0x00b00af, "Mandelbrot");
		}

		need_update = (need_update != 3) ? 0 : 3;
	}
	return 0;
}

int	fill_image(unsigned char *data, int bpp, int sl, int w, int h) {
	int	x = 0, y = h, opp = bpp >> 3, dec = 0;
	const double r = 2.;

	while (y--) {
		unsigned char *ptr = data+y*sl;
		x = w;
		while (x--) {
			double magn = 0., z_x = 0., z_y = 0., \
				c_x = affine_transf(x, w, cx_0, cx_1)+offsetX, \
				c_y = affine_transf(y, h, cy_0, cy_1)+offsetY;

			if (!mandelbrot) {
				z_x = c_x;
				z_y = c_y;
				c_x = julia_X;
				c_y = julia_Y;
			}

			unsigned i = 0;
			while ((i++) < n_iters) {
				double tmp_x = (z_x*z_x)-(z_y*z_y)+c_x, \
					tmp_y = (2.*z_x*z_y)+c_y;
				z_x = tmp_x;
				z_y = tmp_y;
				magn = (z_x*z_x+z_y*z_y);
				if (magn > r*r) break;
			}

			color_t color = RGB2YIQ(0,magn/(r*r),(double)i/n_iters);

			/*if (abs(i-n_iters) <= 5) color = 0xffd700; // interior
			else {	// exterior
				if (abs(magn-r*r) <= 1.e-8) color = ((int)(255.*(z_x*z_x+z_y*z_y)) % 256);
				else color = PACK_COLOR_RGB(r,0xbf,0xff);
			}*/

			dec = opp;
			while (dec--) {
				if (endian) *(ptr+x*opp+dec) = ((unsigned char *)(&color))[4-opp+dec];
				else *(ptr+x*opp+dec) = ((unsigned char *)(&color))[dec];
			}
		}
	}
    return 0;
}