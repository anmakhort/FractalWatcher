#include "../include/transform.h"

double affine_transf(int x, int w, double toMin, double toMax) {
	double dX = toMax - toMin;
	return (dX*(double)x/(double)w)+toMin;
}