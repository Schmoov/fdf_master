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
void view_clear_img(t_view *view)
{
	mlx_destroy_image(view->mlx, view->img);
	view->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!view->img)
	{
		mlx_destroy_window(view->mlx, view->win);
		return ((void)(view->err = E_NEWIMG));
	}
}

void	view_update(t_view *view, t_vec4 *vmap, int cols, int rows)
{
	static bool	img_is_blank = true;

	if (!img_is_blank)
		view_clear_img(view);
	view_draw_img(view, vmap, cols, rows);
	img_is_blank = false;
	mlx_clear_window(view->mlx, view->win);
	mlx_put_image_to_window(view->mlx, view->win, view->img, 0, 0);
	//mlx_put_image_to_window(view->mlx, view->win, view->overlay, 0, 0);
}

void	view_destroy(t_view *view)
{
	mlx_destroy_image(view->mlx, view->img);
	//mlx_destroy_image(view->mlx, view->overlay);
	mlx_destroy_window(view->mlx, view->win);
	mlx_destroy_display(view->mlx);
	free(view->mlx);
}
