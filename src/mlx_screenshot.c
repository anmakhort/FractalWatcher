#include "../include/mlx_screenshot.h"

XImage *mlx_get_window_XImage(void *mlx_ptr, void *mlx_win) {
	t_xvar *tvar = (t_xvar *)mlx_ptr;
	t_win_list *win = (t_win_list *)mlx_win;
	XWindowAttributes winAttr;
	XGetWindowAttributes(tvar->display, win->window, &winAttr);
	return XGetImage(tvar->display, win->window, 0, 0, winAttr.width, winAttr.height, XAllPlanes(), ZPixmap);
}

void saveXImageToBMP(XImage *pImage, const char *path) {
	BITMAPFILEHEADER bmpFileHeader;
	BITMAPINFOHEADER bmpInfoHeader;
	memset(&bmpFileHeader, 0, sizeof(BITMAPFILEHEADER));
	memset(&bmpInfoHeader, 0, sizeof(BITMAPINFOHEADER));
	bmpFileHeader.bfType = 0x4D42;
	bmpFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	bmpFileHeader.bfReserved1 = 0;
	bmpFileHeader.bfReserved2 = 0;
	const int biBitCount = 32;
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
	FILE *fp = fopen(path, "wb");
	if(fp == NULL) return;
	fwrite(&bmpFileHeader, sizeof(bmpFileHeader), 1, fp);
	fwrite(&bmpInfoHeader, sizeof(bmpInfoHeader), 1, fp);
	fwrite(pImage->data, dwBmpSize, 1, fp);
	fclose(fp);
}

void saveXImageToPNG(XImage *pImage, const char *path) {
	FILE *fp = fopen(path, "wb");
    if (!fp) return;
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png_ptr) {
    	fprintf(stderr, "Can't create file: %s\n", path);
    	fclose(fp);
    	return;
    }
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
    	fprintf(stderr, "Can't create PNG Info Structure\n");
    	png_destroy_write_struct(&png_ptr, NULL);
    	fclose(fp);
    	return;
    }
    if (setjmp(png_jmpbuf(png_ptr))) {
    	fprintf(stderr, "Can't set JMP\n");
    	png_destroy_write_struct(&png_ptr, &info_ptr);
    	fclose(fp);
    	return;
    }
    png_init_io(png_ptr, fp);
    const int bit_depth = 8;
    png_set_IHDR(png_ptr, info_ptr, pImage->width, pImage->height, \
    	bit_depth, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE, \
    	PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_text _text[4];
    _text[0].compression = _text[1].compression = \
    	_text[2].compression = _text[3].compression = \
    		PNG_TEXT_COMPRESSION_zTXt;
    _text[0].key = "Title";
    _text[0].text = "Fractal Image";
    _text[1].key = "Author";
    _text[1].text = "Anatolii Makhort";
    _text[2].key = "Software";
    _text[2].text = "Fractal Watcher";
    _text[3].key = "Source";
    _text[3].text = "Fractal Watcher & libpng";
    png_set_text(png_ptr, info_ptr, _text, 4);

    png_write_info(png_ptr, info_ptr);

    png_bytep png_row = (png_bytep)malloc(3*pImage->width*sizeof(png_byte));

    unsigned long red_mask = (pImage->red_mask ? pImage->red_mask : 0xff0000);
    unsigned long green_mask = (pImage->red_mask ? pImage->green_mask : 0xff00);
    unsigned long blue_mask = (pImage->blue_mask ? pImage->blue_mask : 0xff);

    for (int y = 0; y < pImage->height; y++) {
    	for (int x = 0; x < pImage->width; x++) {
    		unsigned long pixel = XGetPixel(pImage, x, y);
    		unsigned char blue = pixel & blue_mask;
    		unsigned char green = (pixel & green_mask) >> 8;
    		unsigned char red = (pixel & red_mask) >> 16;
    		png_byte *ptr = &(png_row[x*3]);
    		ptr[0] = red;
    		ptr[1] = green;
    		ptr[2] = blue;
    	}
    	png_write_row(png_ptr, png_row);
    }
    
    png_write_end(png_ptr, NULL);

    fclose(fp);
    png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
    png_destroy_write_struct (&png_ptr, NULL);
    free(png_row);
}

void mlx_snap_window(void *mlx_ptr, void *mlx_win, const char *directory, const char *fract_name, unsigned int snap_number, image_format_t format) {
	XImage *image = mlx_get_window_XImage(mlx_ptr, mlx_win);
	if (image) {
		char path[256];
		sprintf(path, "%s/%s_%d", directory, fract_name, snap_number);
		switch (format) {
			case FORMAT_BMP:
				sprintf(path, "%s.bmp", path);
				saveXImageToBMP(image, path);
				break;
			case FORMAT_PNG:
				sprintf(path, "%s.png", path);
				saveXImageToPNG(image, path);
				break;
			default:
				fprintf(stderr, "Incorrect file format specified: %i\n", format);
				break;
		}
		XDestroyImage(image);
	}
}