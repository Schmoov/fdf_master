#include "fdf.h"

void	controller_update_view(t_model *model, t_view *view)
{
	mlx_destroy_image(view->mlx, view->img);
	view->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	controller_draw_img(model, view);
	view_draw_win(view);
}
