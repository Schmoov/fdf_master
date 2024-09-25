#include "fdf.h"

void	presenter_update(t_model *model, t_view *view)
{
	model_shader_vertex(model);
	view_update(view, model->vmap, model->cols, model->rows);
}

void	presenter_init(t_presenter *pres, char *path)
{
	model_init(pres->model, path);
	if (!pres->model->color)
		return ((void)(write(2, "Parse error\n", 12)));
	view_init(pres->view, path);
	if (!pres->view->img)
		return ((void)(model_destroy(pres->model), write(2, "Mlx error\n", 10)));
	mlx_key_hook(pres->view->win, key_hook, pres);
	mlx_expose_hook(pres->view->win, expose_hook, pres);
	mlx_loop(pres->view.mlx);
}

void	presenter_destroy(t_model *model, t_view *view)
{
	model_destroy(model);
	view_destroy(view);
}
