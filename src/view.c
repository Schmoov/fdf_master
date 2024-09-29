#include "fdf.h"

void	view_init(t_view *view, char *name)
{
	view->img = NULL;
	view->mlx = mlx_init();
	if (!view->mlx)
		return ;
	view->win = mlx_new_window(view->mlx, WIN_WIDTH, WIN_HEIGHT, name);
	if (!view->win)
		return ((void)mlx_destroy_display(view->mlx), free(view->mlx));
	view->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!view->img)
	{
		mlx_destroy_window(view->mlx, view->win);
		return ((void)mlx_destroy_display(view->mlx), free(view->mlx));
	}
}

static void view_clear_img(t_view *view)
{
	mlx_destroy_image(view->mlx, view->img);
	view->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!view->img)
	{
		mlx_destroy_window(view->mlx, view->win);
		return ;
	}
}

void	view_update(t_presenter *p)
{
	static bool	img_is_blank = true;

	if (!img_is_blank)
		view_clear_img(p->view);
	view_draw_img(p);
	img_is_blank = false;
	mlx_clear_window(p->view->mlx, p->view->win);
	mlx_put_image_to_window(p->view->mlx, p->view->win, p->view->img, 0, 0);
}

void	view_destroy(t_view *view)
{
	mlx_destroy_image(view->mlx, view->img);
	mlx_destroy_window(view->mlx, view->win);
	mlx_destroy_display(view->mlx);
	free(view->mlx);
}
