#include "fdf.h"
#include <stdio.h>

static void	model_default_mat(t_model *m)
{
	m->mat_obj = mat_id();
	m->mat_proj = mat_id();
	m->mat_cam = mat_id();
	m->mat_screen = mat_trans(0, WIN_WIDTH / 2.f);
	m->mat_screen = mat_trans(1, WIN_HEIGHT / 2.f);
	m->mat_screen = mat_trans(2, 2*m->hmax);
}

static void	model_default_iso(t_model *m)
{
	float angle;

	angle = asin(tan(M_PI / 6));
	model_default_mat(m);
	m->mat_obj = mat4s_mult(mat_rot(2, M_PI / 4), m->mat_obj);
	m->mat_obj = mat4s_mult(mat_rot(0, angle), m->mat_obj);
}

void	model_vertex_shader(t_model *m)
{
	int		i;
	int		j;
	t_vec4	v;
	t_mat4s	mat;

	mat = mat4s_mult(m->mat_proj, m->mat_obj);
	mat = mat4s_mult(m->mat_cam, mat);
	mat = mat4s_mult(m->mat_screen, mat);
	i = 0;
	while (i < m->rows)
	{
		j = 0;
		while (j < m->cols)
		{
			v.e[0] = j - m->cols / 2.f;
			v.e[1] = i - m->rows / 2.f;
			v.e[2] = m->height[i * m->cols + j];
			v.e[3] = 1.f;
			m->vertex[i * m->cols + j] = mat4s_vec4_mult(mat, v);
			j++;
		}
		i++;
	}
}

void	model_init(t_model *model, char *path)
{
	parse_fdf(model, path);
	if (!model->color)
		return ;
	model_default_iso(model);
	model_vertex_shader(model);
}

void	model_destroy(t_model *model)
{
	free(model->height);
	free(model->color);
	free(model->vertex);
}
