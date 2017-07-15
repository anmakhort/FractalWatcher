#include "helpwnd.h"

#include "../../minilibx/mlx.h"
#include "../../minilibx/mlx_int.h"


static void *__mlx_helpwnd_win__;
static void *__image__;


int __key_released(int key, void *mlx_ptr) {
	key = key;
	if (mlx_ptr && __mlx_helpwnd_win__) {
		//mlx_destroy_image(mlx_ptr, __image__);
		//__image__ = NULL;
		mlx_destroy_window(mlx_ptr, __mlx_helpwnd_win__);
		__mlx_helpwnd_win__ = NULL;
	}
	return 0;
}

void __put_xmp_bg_image(void *mlx_ptr, char *path) {
	if (__image__) return;
	int szx = 0, szy = 0;
	__image__ = mlx_xpm_file_to_image(mlx_ptr, path, &szx, &szy);
	if (__image__)
		mlx_put_image_to_window(mlx_ptr, __mlx_helpwnd_win__, __image__, 0, 0);
}

void __put_text(void *mlx_ptr, int x, int y, int color, char *str) {
	if (!__mlx_helpwnd_win__) return;
	mlx_string_put(mlx_ptr, __mlx_helpwnd_win__, x, y, color, str);
}

void show_help_window(void *mlx_ptr) {
	if (__mlx_helpwnd_win__) return;
	__mlx_helpwnd_win__ = mlx_new_window(mlx_ptr, HELPWND_WIDTH, HELPWND_HEIGHT, HELPWND_TITLE);
	//__put_xmp_bg_image(mlx_ptr, "helpbg.xmp");
	__put_text(mlx_ptr, HELPWND_WIDTH/2-35, 20, HELPWND_HELP_COLOR, "USAGE:");
	__put_text(mlx_ptr, 25, 50, HELPWND_BASE_COLOR, "Some text will be here soon...");
	mlx_key_hook(__mlx_helpwnd_win__, __key_released, mlx_ptr);
}