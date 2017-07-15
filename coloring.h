#ifndef COLORING_H
#define COLORING_H

typedef unsigned int color_t;

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

typedef color_t (*coloring_func_t)(double zx __attribute__((unused)), double zy __attribute__((unused)), \
	unsigned i __attribute__((unused)), \
	const unsigned n_max_iters __attribute__((unused)), \
	const double r __attribute__((unused)));

color_t coloring0(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i  __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused)));

color_t coloring1(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused)));

color_t coloring2(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused)));

color_t coloring3(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused)));

color_t coloring4(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused)));

color_t coloring5(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused)));

color_t coloring6(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused)));

color_t coloring7(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused)));

color_t coloring8(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused)));

color_t coloring9(double zx __attribute__((unused)), \
	double zy __attribute__((unused)), unsigned i __attribute__((unused)), \
	const unsigned n __attribute__((unused)), const double r __attribute__((unused)));

#endif