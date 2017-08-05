#include "../include/graphics.h"
#include "../include/concolor.h"
#include "../minilibx/mlx.h"
#include "../minilibx/mlx_int.h"

void cleanup(sender_t *sender) {
	if (!sender) return;
	if (!sender->hWnd.mlx_ptr) {
		free(sender);
		return;
	}
	if (sender->image.img_buff) {
		mlx_destroy_image(sender->hWnd.mlx_ptr, sender->image.img_buff);
#ifdef _VERBOSE
  		printf("[%u] Destroy Image -- " BOLD("OK", _FG_GREEN_) "\n", ++sender->cntr);
#endif
	}
	if (sender->hWnd.mlx_win) {
		mlx_destroy_window(sender->hWnd.mlx_ptr, sender->hWnd.mlx_win);
#ifdef _VERBOSE
  		printf("[%u] Destroy Window -- " BOLD("OK", _FG_GREEN_) "\n", ++sender->cntr);
#endif
	}
	free(sender);
}