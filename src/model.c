#include "fdf.h"
#include <stdio.h>


t_mat4s persp_m()
{
	t_mat4s	res = mat_nul();

	res.val[0][0] = 1;
	res.val[1][1] = 1;
	res.val[2][2] = 1;
	res.val[3][2] = -1;
	return (res);
}

static void	model_init_mat(t_model *model)
{
	float	angle;
	float	ratio;

	model->mat_obj = mat_trans(0, (1.f - model->cols)/2.f);
	model->mat_obj = mat4s_mult(mat_trans(1, (1.f - model->rows)/2.f), model->mat_obj);
	ratio = (WIN_WIDTH - 1.f) / (model->cols - 1.f);
	ratio = fmin((WIN_HEIGHT - 1.f) / (model->rows - 1.f), ratio);
	model->mat_obj = mat4s_mult(mat_scale(ratio / 2.f), model->mat_obj);
//	model->mat_obj = mat4s_mult(mat_trans(2, -(model->hmax - model->hmin)/2.f), model->mat_obj);
	angle = asin(tan(M_PI / 6));
	model->mat_obj = mat4s_mult(mat_rot(2, M_PI / 4), model->mat_obj);
	model->mat_obj = mat4s_mult(mat_rot(0, angle), model->mat_obj);

	model->mat_cam = mat_id();
	model->mat_cam = mat4s_mult(mat_trans(0, WIN_WIDTH/2.f), model->mat_cam);
	model->mat_cam = mat4s_mult(mat_trans(1, WIN_HEIGHT/2.f), model->mat_cam);
	model->mat_cam = mat4s_mult(mat_trans(2, ratio*(-model->hmax - 10.f)), model->mat_cam);
	//model->mat_obj = mat4s_mult(mat_trans(0, WIN_WIDTH/2.f), model->mat_obj);
//	model->mat_obj = mat4s_mult(mat_trans(1, WIN_HEIGHT/2.f), model->mat_obj);

	model->mat_cam = mat4s_mult(mat_trans(0, -WIN_WIDTH/2.f), model->mat_cam);
	model->mat_cam = mat4s_mult(mat_trans(1, -WIN_HEIGHT/2.f), model->mat_cam);
	model->mat_cam = mat4s_mult(persp_m(), model->mat_cam);
	model->mat_cam = mat4s_mult(mat_trans(0, WIN_WIDTH/2.f), model->mat_cam);
	model->mat_cam = mat4s_mult(mat_trans(1, WIN_HEIGHT/2.f), model->mat_cam);
	model->mat_proj = mat_id();
}

/*
static void	model_init_mat(t_model *model)
{
	float	angle;

	angle = asin(tan(M_PI / 6));
	model->mat_obj = mat4s_mult(mat_rot(2, M_PI / 4), model->mat_obj);
	model->mat_obj = mat4s_mult(mat_rot(0, angle), model->mat_obj);
	model->mat_obj = mat_id();
	model->mat_obj = mat_trans(0, -model->cols/2.f);
	model->mat_obj = mat_trans(0, -model->rows/2.f);
	model->mat_cam = mat_trans(1, WIN_HEIGHT / 2);
	model->mat_cam = mat4s_mult(mat_trans(0, WIN_WIDTH / 2), model->mat_cam);
	model->mat_cam = mat4s_mult(mat_trans(2, -1000.f), model->mat_cam);
	//model->mat_proj = mat_proj_parallel();
	model->mat_cam = mat_trans(2, -1000.f);
	model->mat_proj = mat_nul();
	model->mat_proj.val[0][0] = 1.f / tan(M_PI/4);
	model->mat_proj.val[1][1] = 1.f / tan(M_PI/4);
	model->mat_proj.val[2][2] = -10.f/9.f;
	model->mat_proj.val[2][3] = -1.f;
	model->mat_proj.val[3][2] = 10.f/9.f;
	model->mat_proj = mat_id();
}
*/
void	model_homogenize_vmap(t_model *model)
{
	int		i;
	int		j;
	t_vec4	*v;

	i = 0;
	while (i < model->rows)
	{
		j = 0;
		while (j < model->cols)
		{
			v = &(model->vmap[i * model->cols + j]);
			v->e[0] /= v->e[3];
			v->e[1] /= v->e[3];
			//v->e[2] /= v->e[3];
			v->e[3] = 1.f;
			j++;
		}
		i++;
	}
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
			v.e[0] = j;
			v.e[1] = i;
			v.e[2] = model->hmap[i * model->cols + j];
			v.e[3] = 1.f;
			model->vmap[i * model->cols + j] = mat4s_vec4_mult(mat, v);
			j++;
		}
		i++;
	}
	model_homogenize_vmap(model);
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
