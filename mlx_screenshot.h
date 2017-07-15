#ifndef MLX_SCREENSHOT_H
#define MLX_SCREENSHOT_H

#include <png.h>
#include "./minilibx/mlx.h"
#include "./minilibx/mlx_int.h"


#pragma pack (1)
typedef struct tagBITMAPFILEHEADER {
	short   bfType;
	int 	bfSize;
	short   bfReserved1;
	short   bfReserved2;
	int   	bfOffBits;
} BITMAPFILEHEADER;

#pragma pack (1)
typedef struct tagBITMAPINFOHEADER {
	int  	biSize;
	int   	biWidth;
	int   	biHeight;
	short   biPlanes;
	short   biBitCount;
	int  	biCompression;
	int  	biSizeImage;
	int   	biXPelsPerMeter;
	int   	biYPelsPerMeter;
	int  	biClrUsed;
	int  	biClrImportant;
} BITMAPINFOHEADER;


typedef enum { FORMAT_BMP = -1, FORMAT_PNG = 1 } image_format_t;

XImage *mlx_get_window_XImage(void *mlx_ptr, void *mlx_win);
void saveXImageToBMP(XImage *pImage, const char *path);
void saveXImageToPNG(XImage *pImage, const char *path);
void mlx_snap_window(void *mlx_ptr, void *mlx_win, const char *directory, const char *fract_name, unsigned int snap_number, image_format_t format);

#endif