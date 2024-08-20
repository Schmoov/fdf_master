#include "fdf.h"

static void	model_init_mat(t_model *model)
{
	float	angle;

	angle = asin(tan(M_PI / 6));
	model->mat_obj = mat_id();
	model->mat_obj = mat4s_mult(mat_rot(2, M_PI / 4), model->mat_obj);
	model->mat_obj = mat4s_mult(mat_rot(0, angle), model->mat_obj);
	model->mat_cam = mat_trans(1, WIN_HEIGHT / 2);
	model->mat_cam = mat4s_mult(mat_trans(0, WIN_WIDTH / 2), model->mat_cam);
	//model->mat_proj = mat_proj_parallel();
	model->mat_proj = mat_id();
}

void	model_update_vmap(t_model *model)
{
	int		i;
	int		j;
	t_vec4	v;
	t_mat4s	mat;

	mat = mat4s_mult(model->mat_cam, model->mat_obj);
	mat = mat4s_mult(model->mat_proj, mat);
	i = 0;
	while (i < model->rows)
	{
		j = 0;
		while (j < model->cols)
		{
			v.e[0] = j - model->cols / 2.f + .5f;
			v.e[1] = i - model->rows / 2.f + .5f;
			v.e[2] = model->hmap[i * model->cols + j];
			v.e[3] = 1.f;
			model->vmap[i * model->cols + j] = mat4s_vec4_mult(mat, v);
			j++;
		}
		i++;
	}
}

void	model_init(t_model *model, char *path)
{
	model->err = E_SUCCESS;
	model_alloc_and_parse(model, path);
	if (model->err)
		return ;
	model_init_mat(model);
	model_update_vmap(model);
}

void	model_destroy(t_model *model)
{
	free(model->hmap);
	free(model->vmap);
}
