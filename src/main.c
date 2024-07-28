#include "fdf.h"

void	init_view(t_view *view, const char *path)
{
	view->mlx = mlx_init();
	view->win = mlx_new_window(view->mlx, WIN_WIDTH, WIN_HEIGHT, path);
	view->img = mlx_new_image(view->mlx, WIN_WIDTH, WIN_HEIGHT);
	view->overlay = mlx_xpm_file_to_image(view->mlx, "xpm/overlay.xpm", WIN_WIDTH, WIN_HEIGHT);
}

int	main(int argc, char **argv)
{
	t_model	model;
	t_view	view;

	if (argc > 2)
		return (write(2, "Fdf expects a single file\n", 26));
	if (argc == 1)
		return (write(2, "Reading from stdin not yet implemented\n", 39));
	init_model(&model, argv[1]);
	if (model->err)
		return (write(2, "Parse error\n", 12));
	init_view(&view, argv[1]);
	mlx_key_hook(st.mlx.win, key_hook, &st);
	mlx_loop(st.mlx.ptr);
}
