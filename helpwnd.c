#include "helpwnd.h"

#include "./minilibx/mlx.h"
#include "./minilibx/mlx_int.h"


static void *__mlx_helpwnd_win__;

int __key_released(int key, void *mlx_ptr) {
	key = key;
	if (mlx_ptr && __mlx_helpwnd_win__) {
		mlx_destroy_window(mlx_ptr, __mlx_helpwnd_win__);
		__mlx_helpwnd_win__ = NULL;
	}
	return 0;
}

void __put_text(void *mlx_ptr, int x, int y, int color, char *str) {
	if (!__mlx_helpwnd_win__) return;
	mlx_string_put(mlx_ptr, __mlx_helpwnd_win__, x, y, color, str);
}

void show_help_window(void *mlx_ptr) {
	if (__mlx_helpwnd_win__) return;

	__mlx_helpwnd_win__ = mlx_new_window(mlx_ptr, HELPWND_WIDTH, HELPWND_HEIGHT, HELPWND_TITLE, HELPWND_BG_COLOR);
	
	__put_text(mlx_ptr, HELPWND_WIDTH/2-35, 20, HELPWND_HELP_TITLE_COLOR, "USAGE");

	__put_text(mlx_ptr, 120, 45, HELPWND_DESCRIPTION_COLOR1, "Navigation");
	__put_text(mlx_ptr, 202, 45, HELPWND_COMMANDS_COLOR, "<- ^ ->");
	__put_text(mlx_ptr, 250, 45, 0, "keyboard arrows");
	
	__put_text(mlx_ptr, 67, 65, HELPWND_DESCRIPTION_COLOR2, "Centering a fractal");
	__put_text(mlx_ptr, 200, 65, HELPWND_COMMANDS_COLOR, "'c'");
	__put_text(mlx_ptr, 220, 65, 0, "key");

	__put_text(mlx_ptr, 72, 85, HELPWND_DESCRIPTION_COLOR3, "Set an offset step");
	__put_text(mlx_ptr, 200, 85, HELPWND_COMMANDS_COLOR, "'k'");
	__put_text(mlx_ptr, 220, 85, 0, "or");
	__put_text(mlx_ptr, 235, 85, HELPWND_COMMANDS_COLOR, "'l'");
	__put_text(mlx_ptr, 255, 85, 0, "keys");

	__put_text(mlx_ptr, 42, 105, HELPWND_DESCRIPTION_COLOR4, "Set an iterations count");
	__put_text(mlx_ptr, 200, 105, HELPWND_COMMANDS_COLOR, "'i'");
	__put_text(mlx_ptr, 220, 105, 0, "or");
	__put_text(mlx_ptr, 235, 105, HELPWND_COMMANDS_COLOR, "'o'");
	__put_text(mlx_ptr, 255, 105, 0, "with");
	__put_text(mlx_ptr, 285, 105, HELPWND_COMMANDS_COLOR, "'n'");
	__put_text(mlx_ptr, 305, 105, 0, "to 300");

	__put_text(mlx_ptr, 96, 125, HELPWND_DESCRIPTION_COLOR5, "Zoom-in (-out)");
	__put_text(mlx_ptr, 200, 125, HELPWND_COMMANDS_COLOR, "'-'");
	__put_text(mlx_ptr, 220, 125, 0, "or");
	__put_text(mlx_ptr, 235, 125, HELPWND_COMMANDS_COLOR, "'+'");
	__put_text(mlx_ptr, 255, 125, 0, "numpad keys");

	__put_text(mlx_ptr, 48, 145, HELPWND_DESCRIPTION_COLOR6, "Animate (auto-zoom-in)");
	__put_text(mlx_ptr, 200, 145, HELPWND_COMMANDS_COLOR, "'a'");
	__put_text(mlx_ptr, 220, 145, 0, "key");

	__put_text(mlx_ptr, 36, 165, HELPWND_DESCRIPTION_COLOR7, "Change a current fractal");
	__put_text(mlx_ptr, 200, 165, HELPWND_COMMANDS_COLOR, "'j'");
	__put_text(mlx_ptr, 220, 165, 0, "(for Julia)");
	__put_text(mlx_ptr, 290, 165, HELPWND_COMMANDS_COLOR, "'m'");
	__put_text(mlx_ptr, 310, 165, 0, "(for Mandelbrot)");

	__put_text(mlx_ptr, 65, 185, HELPWND_DESCRIPTION_COLOR8, "Select");
	__put_text(mlx_ptr, 109, 185, 0xf000fc, "z");
	__put_text(mlx_ptr, 124, 185, HELPWND_DESCRIPTION_COLOR8, "for Julia");
	__put_text(mlx_ptr, 202, 185, HELPWND_COMMANDS_COLOR, "move cursor");

	__put_text(mlx_ptr, 11, 205, HELPWND_DESCRIPTION_COLOR9, "Save cursor position (Julia)");
	__put_text(mlx_ptr, 200, 205, HELPWND_COMMANDS_COLOR, "'s'");
	__put_text(mlx_ptr, 220, 205, 0, "key");

	__put_text(mlx_ptr, 51, 225, HELPWND_DESCRIPTION_COLOR10, "Save fractal as image");
	__put_text(mlx_ptr, 200, 225, HELPWND_COMMANDS_COLOR, "'b'");
	__put_text(mlx_ptr, 220, 225, 0, "(for BMP)");
	__put_text(mlx_ptr, 280, 225, HELPWND_COMMANDS_COLOR, "'p'");
	__put_text(mlx_ptr, 300, 225, 0, "(for PNG)");

	__put_text(mlx_ptr, 153, 245, HELPWND_DESCRIPTION_COLOR11, "Help");
	__put_text(mlx_ptr, 200, 245, HELPWND_COMMANDS_COLOR, "'h'");
	__put_text(mlx_ptr, 220, 245, 0, "key");

	__put_text(mlx_ptr, 153, 265, HELPWND_DESCRIPTION_COLOR12, "Quit");
	__put_text(mlx_ptr, 202, 265, HELPWND_COMMANDS_COLOR, "ESC");
	__put_text(mlx_ptr, 225, 265, 0, "or");
	__put_text(mlx_ptr, 242, 265, HELPWND_COMMANDS_COLOR, "'q'");
	
	mlx_key_hook(__mlx_helpwnd_win__, __key_released, mlx_ptr);
}