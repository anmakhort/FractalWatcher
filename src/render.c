#include "../include/graphics.h"
#include "../include/transform.h"
#include <stdio.h>

void render(sender_t *sender, int w, int h) {
	if (!sender) return;
	
	int	x = 0, y = h;
	const double r = 2.;

	while (y--) {
		x = w;
		while (x--) {
			double magn = 0., z_x = 0., z_y = 0., \
				c_x = affine_transf(x, w, sender->c_plane.x_min, sender->c_plane.x_max)+sender->offset_pt.x, \
				c_y = affine_transf(y, h, sender->c_plane.y_min, sender->c_plane.y_max)+sender->offset_pt.y;

			if (!sender->mandelbrot) {
				z_x = c_x;
				z_y = c_y;
				c_x = sender->julia_pt.x;
				c_y = sender->julia_pt.y;
			}

			unsigned i = 0;
			while ((++i) < sender->n_iters) {
				double tmp_x = (z_x*z_x)-(z_y*z_y)+c_x, \
					tmp_y = (2.*z_x*z_y)+c_y;
				z_x = tmp_x;
				z_y = tmp_y;
				magn = (z_x*z_x+z_y*z_y);
				if (magn > r*r) break;
			}

			sender->calculated[x][y].real = z_x;
			sender->calculated[x][y].imag = z_y;
			sender->calculated[x][y].iters = i;
		}
	}
}