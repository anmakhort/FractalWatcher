#ifndef GRAPHICS_H
#define GRAPHICS_H


#define WND_BG_COLOR	0
#define WND_TITLE		"Fractal Watcher"
#define IMAGES_BASE_DIR "./Images/"

#define IMAGE_BUFFER_WIDTH 700
#define IMAGE_BUFFER_HEIGHT 500


typedef unsigned char flag_t;
typedef unsigned int color_t;
typedef unsigned long counter_t;

#define PACK_COLOR_RGB(r,g,b) (color_t)(((color_t)(r)<<0x10)|((color_t)(g)<<0x8)|((color_t)(b)))

/*
|y|   |0.299  0.587   0.114	 |   |r|
|i| = |0.596  -0.274  -0.321 | * |g|
|q|   |0.211  -0.523  0.311  |   |b|
*/
#define RGB2YIQ(r,g,b) PACK_COLOR_RGB(		\
	(color_t)(255.*(.299*r+.587*g+.114*b)),	\
	(color_t)(255.*(.596*r-.274*g-.321*b)),	\
	(color_t)(255.*(.211*r-.523*g+.311*b)))

#define SCREEN_TO_CX_MIN	-1.2
#define SCREEN_TO_CX_MAX	1.2
#define SCREEN_TO_CY_MIN	-1.2
#define SCREEN_TO_CY_MAX	1.2

#define JULIA_SCREEN_TO_CX_MIN	-1.0
#define JULIA_SCREEN_TO_CX_MAX	1.0
#define JULIA_SCREEN_TO_CY_MIN	-1.0
#define JULIA_SCREEN_TO_CY_MAX	1.0

#define MIN_ITERATIONS		50
#define MAX_ITERATIONS		500
#define NORMAL_ITERATIONS	300
#define ITERATIONS_DELTA	5

#define MIN_ZOOM			0.5
#define MAX_ZOOM			25000.0
#define MAX_ANIMATE_ZOOM	100000.0

#define MIN_MOVE_SCALE		0.05
#define MAX_MOVE_SCALE		2.0
#define MOVE_SCALE_DELTA	0.05

#define KEYBOARD_EXIT_KEY	0xff1b
#define KEYBOARD_QUIT_KEY	0x71
#define KEYBOARD_ZOOM_IN	0xffab
#define KEYBOARD_ZOOM_OUT	0xffad
#define KEYBOARD_NORMAL		0xff08
#define KEYBOARD_LEFT_KEY	0xff51
#define KEYBOARD_RIGHT_KEY	0xff53
#define KEYBOARD_UP_KEY		0xff52
#define KEYBOARD_DOWN_KEY	0xff54
#define KEYBOARD_P_KEY		0x70
#define KEYBOARD_B_KEY		0x62
#define KEYBOARD_M_KEY		0x6d
#define KEYBOARD_A_KEY		0x61
#define KEYBOARD_L_KEY		0x6c
#define KEYBOARD_H_KEY		0x68
#define KEYBOARD_N_KEY		0x6e
#define KEYBOARD_C_KEY		0x63
#define KEYBOARD_I_KEY		0x69
#define KEYBOARD_O_KEY		0x6f
#define KEYBOARD_J_KEY		0x6a
#define KEYBOARD_K_KEY		0x6b
#define KEYBOARD_S_KEY		0x73

#define GET_ZOOM_DELTA(zoom) \
	(zoom < 10.) ? 0.5 : ((zoom < 50.) ? 2.5 : (\
		(zoom < 200.) ? 5.0 : (\
			(zoom < 1000.) ? 10.0 : (\
				(zoom < 2000.) ? 25.0 : (\
					(zoom < 5000.) ? 50.0 : 100.0)))))

#define GET_ANIMATE_ZOOM_DELTA(zoom) \
	(zoom < 10.) ? 0.5 : ((zoom < 50.) ? 2.5 : (\
		(zoom < 100.) ? 10.0 : (\
			(zoom < 500.) ? 100.0 : (\
				(zoom < 1000.) ? 200.0 : (\
					(zoom < 5000.) ? 500.0 : (\
						(zoom < 15000.) ? 1000.0 : 5000.0))))))

typedef struct {
	int width;
	int height;
	int bpp;
	int sz_line;
} image_header_t;

typedef struct {
	void *img_buff;
	void *img_drawer_ptr;
} image_t;

typedef struct {
	void *mlx_ptr;
	void *mlx_win;
} wnd_handle_t;


int is_BigEndian() {
	unsigned int a = 0xAA0000FF;
	return (int)(((unsigned char *)&a)[0] == 0xAA);
}

double affine_transf(int x, int w, double toMin, double toMax) {
	double dX = toMax - toMin;
	return (dX*(double)x/(double)w)+toMin;
}

#endif