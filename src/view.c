#include "fdf.h"

void	init_view(t_view *view, const char *path)
{
	view->mlx = mlx_init();
	if (!view->mlx)
		return (view->err = E_MLXPTR);
	view->win = mlx_new_window(view->mlx, WIN_WIDTH, WIN_HEIGHT, path);
	if (!view->win)
		return (view->err = E_MLXWIN);
	view->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!view->img)
	{
		mlx_destroy_window(view->mlx, view->win);
		return (view->err = E_NEWIMG);
	}
	view->overlay = mlx_xpm_file_to_image(view->mlx,
			"xpm/overlay.xpm", WIN_WIDTH, WIN_HEIGHT);
	if (!view->overlay)
	{
		mlx_destroy_image(view->mlx, view->img);
		mlx_destroy_window(view->mlx, view->win);
		return (view->err = E_OVERLAY);
	}
}

void	destroy_view(t_view *view)
{
	mlx_destroy_image(view->mlx, view->img);
	mlx_destroy_image(view->mlx, view->overlay);
	mlx_destroy_window(view->mlx, view->win);
}
