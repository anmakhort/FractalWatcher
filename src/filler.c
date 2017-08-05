#include "../include/graphics.h"
#define _USE_MATH_DEFINES
#include <math.h>

void coloring(sender_t *sender, int w, int h) {
	if (!sender) return;

	int	x, y = h, opp = sender->header.bpp >> 3, dec = 0;

	while (y--) {
		unsigned char *ptr = sender->image.img_drawer_ptr + y*sender->header.sz_line;
		x = w;

		while (x--) {
			double magn = sqrt(sender->calculated[x][y].real*sender->calculated[x][y].real +\
								sender->calculated[x][y].imag*sender->calculated[x][y].imag);

			color_t color = 0UL;

			switch (sender->coloring_idx) {
				case 0:
					color = RGB2YIQ(0, magn/2., (double)sender->calculated[x][y].iters/sender->n_iters);
					break;

				case 1:
					color = PACK_COLOR_RGB(DBL2INT(magn/2.), 0, sender->calculated[x][y].iters%256);
					break;

				case 2:
					color = PACK_COLOR_RGB(75,\
						DBL2INT(((double)sender->calculated[x][y].iters-(log(log(magn))-log(M_LN2))/M_LN2)),\
						DBL2INT((double)sender->calculated[x][y].iters/(double)sender->n_iters));
					break;

				case 3:
					color = PACK_COLOR_RGB(DBL2INT(sin(M_PI*sender->calculated[x][y].real)), \
									sender->calculated[x][y].iters%256, \
									DBL2INT(cos(M_PI*sender->calculated[x][y].imag)));
					break;

				case 4:
					color = PACK_COLOR_RGB(0, 0, sender->calculated[x][y].iters % sender->n_iters);
					break;
					
				default:
					color = PACK_COLOR_RGB(0, sender->calculated[x][y].iters%256, DBL2INT(magn/2.));
					break;
			}

			dec = opp;
			while (dec--) {
				if (sender->endian) *(ptr+x*opp+dec) = ((unsigned char *)(&color))[4-opp+dec];
				else *(ptr+x*opp+dec) = ((unsigned char *)(&color))[dec];
			}
		}
	}
}