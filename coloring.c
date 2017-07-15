#include "coloring.h"
#include <stdlib.h>
#include <math.h>

color_t coloring0(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i  __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused))) {
	return RGB2YIQ(0, abs(zx*zx+zy*zy)/(r*r), (double)i/n);
}

color_t coloring1(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i  __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused))) {
	return PACK_COLOR_RGB((color_t)(255.*abs(zx*zx+zy*zy)/(r*r))%256, 0, i%256);
}

color_t coloring2(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i  __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused))) {
	return coloring0(zx, zy, i, n, r);
}

color_t coloring3(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i  __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused))) {
	return coloring0(zx, zy, i, n, r);
}

color_t coloring4(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i  __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused))) {
	return coloring0(zx, zy, i, n, r);
}

color_t coloring5(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i  __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused))) {
	return coloring0(zx, zy, i, n, r);
}

color_t coloring6(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i  __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused))) {
	return coloring0(zx, zy, i, n, r);
}

color_t coloring7(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i  __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused))) {
	return coloring0(zx, zy, i, n, r);
}

color_t coloring8(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i  __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused))) {
	return coloring0(zx, zy, i, n, r);
}

color_t coloring9(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i  __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused))) {
	return coloring0(zx, zy, i, n, r);
}