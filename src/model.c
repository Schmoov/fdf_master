/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   model.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:47:20 by parden            #+#    #+#             */
/*   Updated: 2024/10/12 21:22:33 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	model_init(t_model *model, int fd)
{
	parse_fdf(model, fd);
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
