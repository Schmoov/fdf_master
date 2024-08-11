#include "fdf.h"
void	controller_init(t_model *model, t_view *view)
{
	mlx_key_hook(st.mlx.win, key_hook, &st);
	mlx_loop(st.mlx.ptr);
}

int	main(int argc, char **argv)
{
	t_model	model;
	t_view	view;

	if (argc > 2)
		return (write(2, "Fdf expects a single file\n", 26));
	if (argc == 1)
		return (write(2, "Reading from stdin not yet implemented\n", 39));
	model_init(&model, argv[1]);
	if (model->err)
		return (write(2, "Parse error\n", 12));
	view_init(&view, argv[1]);
	if (mlx->err)
		return (model_destroy(&model), write(2, "Mlx error\n", 10));
	controller_init(&model, &view);
}
