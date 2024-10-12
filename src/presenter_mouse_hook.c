/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presenter_mouse_hook.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:47:20 by parden            #+#    #+#             */
/*   Updated: 2024/10/12 21:22:35 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	model_make_iso(t_model *m)
{
	float	angle;
	float	scale;

	scale = WIN_WIDTH / (m->cols * 2.f);
	angle = asin(tan(M_PI / 6));
	m->mat_obj = mat4s_mult(mat_rot(2, M_PI / 4), mat_scale(scale));
	m->mat_obj = mat4s_mult(mat_rot(0, angle), m->mat_obj);
	m->mat_cam = mat4s_mult(mat_trans(1, WIN_HEIGHT / 2.f),
			mat_trans(0, WIN_WIDTH / 2.f));
	m->mat_cam = mat4s_mult(mat_trans(2, -2 * m->hmax * scale),
			m->mat_cam);
}

void	model_make_topdown(t_model *m)
{
	float	scale;

	scale = WIN_WIDTH / (m->cols * 2.f);
	m->mat_obj = mat_scale(scale);
	m->mat_cam = mat4s_mult(mat_trans(1, WIN_HEIGHT / 2.f),
			mat_trans(0, WIN_WIDTH / 2.f));
	m->mat_cam = mat4s_mult(mat_trans(2, -2 * m->hmax * scale),
			m->mat_cam);
}

void	model_make_side(t_model *m)
{
	float	scale;

	scale = WIN_WIDTH / (m->cols * 2.f);
	m->mat_obj = mat4s_mult(mat_rot(0, M_PI / 2), mat_scale(scale));
	m->mat_cam = mat4s_mult(mat_trans(1, WIN_HEIGHT / 2.f),
			mat_trans(0, WIN_WIDTH / 2.f));
	m->mat_cam = mat4s_mult(mat_trans(2, -2 * m->hmax * scale),
			m->mat_cam);
}

int	close_with_cross(void *param)
{
	presenter_destroy(param);
	exit(0);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	t_model	*model;
	t_view	*view;

	(void) x;
	(void) y;
	model = ((t_presenter *)param)->model;
	view = ((t_presenter *)param)->view;
	if (button == 1)
		model_make_side(model);
	if (button == 2)
		model_make_iso(model);
	if (button == 3)
		model_make_topdown(model);
	presenter_update(param);
	return (0);
}
