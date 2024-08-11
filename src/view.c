#include "fdf.h"

void	view_init(t_view *view, char *path)
{
//	int	osef;

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

void	view_destroy(t_view *view)
{
	mlx_destroy_image(view->mlx, view->img);
	mlx_destroy_image(view->mlx, view->overlay);
	mlx_destroy_window(view->mlx, view->win);
}
