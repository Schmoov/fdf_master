/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:47:20 by parden            #+#    #+#             */
/*   Updated: 2024/10/01 20:50:49 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	model_make_iso(t_model *m)
{
	float	angle;

	angle = asin(tan(M_PI / 6));
	m->mat_obj = mat4s_mult(mat_rot(0, angle),
			mat_rot(2, M_PI / 4));
	m->mat_cam = mat4s_mult(mat_trans(1, WIN_HEIGHT / 2.f),
			mat_trans(0, WIN_WIDTH / 2.f));
	m->mat_cam = mat4s_mult(mat_trans(2, -2 * m->hmax),
			m->mat_cam);
}

void	model_make_topdown(t_model *m)
{
	m->mat_obj = mat_id();
	m->mat_cam = mat4s_mult(mat_trans(1, WIN_HEIGHT / 2.f),
			mat_trans(0, WIN_WIDTH / 2.f));
	m->mat_cam = mat4s_mult(mat_trans(2, -2 * m->hmax),
			m->mat_cam);
}

void	model_make_side(t_model *m)
{
	m->mat_obj = mat_rot(0, M_PI / 2);
	m->mat_cam = mat4s_mult(mat_trans(1, WIN_HEIGHT / 2.f),
			mat_trans(0, WIN_WIDTH / 2.f));
	m->mat_cam = mat4s_mult(mat_trans(2, -2 * m->hmax),
			m->mat_cam);
}

void	model_vertex_shader(t_model *m)
{
	int		i;
	int		j;
	t_vec4	v;
	t_mat4s	mat;

	mat = mat4s_mult(m->mat_cam, m->mat_obj);
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
	model_make_iso(model);
	model_vertex_shader(model);
}

void	model_destroy(t_model *model)
{
	free(model->height);
	free(model->color);
	free(model->vertex);
}
