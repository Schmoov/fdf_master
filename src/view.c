#include "fdf.h"

void	view_init(t_view *view, char *path)
{
//	int	osef;
	view->err = E_SUCCESS;
	view->mlx = mlx_init();
	if (!view->mlx)
		return ((void)(view->err = E_MLXPTR));
	view->win = mlx_new_window(view->mlx, WIN_WIDTH, WIN_HEIGHT, path);
	if (!view->win)
		return ((void)(view->err = E_MLXWIN));
	view->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!view->img)
	{
		mlx_destroy_window(view->mlx, view->win);
		return ((void)(view->err = E_NEWIMG));
	}
/*
	view->overlay = mlx_xpm_file_to_image(view->mlx, "xpm/overlay.xpm", &osef, &osef);
	if (!view->overlay)
	{
		mlx_destroy_image(view->mlx, view->img);
		mlx_destroy_window(view->mlx, view->win);
		return ((void)(view->err = E_OVERLAY));
	}
*/
}

void	view_draw_win(t_view *view)
{
	mlx_clear_window(view->mlx, view->win);
	mlx_put_image_to_window(view->mlx, view->win, view->img, 0, 0);
	//mlx_put_image_to_window(view->mlx, view->win, view->overlay, 0, 0);
}

void	view_destroy(t_view *view)
{
	mlx_destroy_image(view->mlx, view->img);
	mlx_destroy_image(view->mlx, view->overlay);
	mlx_destroy_window(view->mlx, view->win);
}

void	controller_update_view(t_model *model, t_view *view)
{
	mlx_destroy_image(ctrl->view.mlx, ctrl->view.img);
	view.img = mlx_new_image(view.mlx, WIN_WIDTH, WIN_HEIGHT);
	controller_draw_img(model, view);
	view_draw_win(view);
}
