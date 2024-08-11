#include "fdf.h"

int	expose_hook(void *param)
{
	t_model	*model;
	t_view	*view;

	model = &(((t_controller *) param)->model);
	view = &(((t_controller *) param)->view);
	controller_draw_img(model, view);
	controller_update_view(model, view);
	return (0);
}

void	controller_init(t_controller *ctrl)
{
	mlx_key_hook(ctrl->view.win, key_hook, ctrl);
	mlx_expose_hook(ctrl->view.win, expose_hook, ctrl);
	mlx_loop(ctrl->view.mlx);
}

int	main(int argc, char **argv)
{
	t_controller	ctrl;

	if (argc > 2)
		return (write(2, "Fdf expects a single file\n", 26));
	if (argc == 1)
		return (write(2, "Reading from stdin not yet implemented\n", 39));
	model_init(&(ctrl.model), argv[1]);
	if (ctrl.model.err)
		return (write(2, "Parse error\n", 12));
	view_init(&(ctrl.view), argv[1]);
	if (ctrl.view.err)
		return (model_destroy(&(ctrl.model)), write(2, "Mlx error\n", 10));
	controller_init(&ctrl);
}
