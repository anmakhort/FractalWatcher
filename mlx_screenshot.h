#ifndef MLX_SCREENSHOT_H
#define MLX_SCREENSHOT_H

#include "../../minilibx/mlx.h"
#include "../../minilibx/mlx_int.h"


#pragma pack (1)
typedef struct tagBITMAPFILEHEADER {
	short   bfType;
	int 	bfSize;
	short   bfReserved1;
	short   bfReserved2;
	int   	bfOffBits;
} BITMAPFILEHEADER;

#pragma pack (1)
typedef struct tagBITMAPINFOHEADER
{
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

void saveXImageToBitmap(XImage *pImage, const char *path) {
	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;
	memset(&bmpFileHeader, 0, sizeof(BITMAPFILEHEADER));
	memset(&bmpInfoHeader, 0, sizeof(BITMAPINFOHEADER));
	bmpFileHeader.bfType = 0x4D42;
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmpFileHeader.bfReserved1 = 0;
	bmpFileHeader.bfReserved2 = 0;
	int biBitCount =32;
	int dwBmpSize = ((pImage->width * biBitCount + 31) / 32) * 4 * pImage->height;
	bmpFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +  dwBmpSize;
	bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfoHeader.biWidth = pImage->width;
	bmpInfoHeader.biHeight = -pImage->height;
	bmpInfoHeader.biPlanes = 1;
	bmpInfoHeader.biBitCount = biBitCount;
	bmpInfoHeader.biSizeImage = 0;
	bmpInfoHeader.biCompression = 0;
	bmpInfoHeader.biXPelsPerMeter = 0;
	bmpInfoHeader.biYPelsPerMeter = 0;
	bmpInfoHeader.biClrUsed = 0;
	bmpInfoHeader.biClrImportant = 0;
	FILE *fp;
	if (!path) {
		static int cnt = 0;
		char filePath[255];
		sprintf(filePath, "bitmap%d.bmp", cnt++);
		fp = fopen(filePath, "wb");
	} else {
		fp = fopen(path, "wb");
	}
	if(fp == NULL) return;
	fwrite(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);
	fwrite(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, fp);
	fwrite(pImage->data, dwBmpSize, 1, fp);
	fclose(fp);
}

void mlx_snap_window(void *mlx_ptr, void *mlx_win, const char *path) {
	t_xvar *tvar = (t_xvar *)mlx_ptr;
	t_win_list *win = (t_win_list *)mlx_win;
	XWindowAttributes winAttr;
	XGetWindowAttributes(tvar->display, win->window, &winAttr);
	XImage *image = XGetImage(tvar->display, win->window, 0, 0, winAttr.width, winAttr.height, XAllPlanes(), ZPixmap);
	if (image != NULL) saveXImageToBitmap(image, path);
}

#endif