#include "fdf.h"

static void	init_mat(t_model *model)
{
	model->mat = mat_id();
}

static void	compute_vmap(t_model *model)
{
	int		i;
	int		j;
	t_vec4	v;

	i = 0;
	while (i < model->rows)
	{
		j = 0;
		while (j < model->cols)
		{
			v.e[0] = j - model->cols / 2.f;
			v.e[1] = i - model->rows / 2.f;
			v.e[2] = model->hmap[i * model->cols + j];
			v.e[3] = 1.f;
			model->vmap[i * model->cols + j] = mat4s_vec4_mult(model->mat, v);
			j++;
		}
		i++;
	}
}

void	init_model(t_model *model, const char *path)
{
	parse_hmap(model, path);
	if (model->err)
		return ;
	init_mat(model);
	compute_vmap(model);
}

void	update_model(t_model *model)
{
	compute_vmap(model);
}

void	destroy_model(t_model *model)
{
	free(model->hmap);
	free(model->vmap);
}
