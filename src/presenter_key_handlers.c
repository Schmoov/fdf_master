/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presenter_key_handlers.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:47:20 by parden            #+#    #+#             */
/*   Updated: 2024/10/01 20:51:30 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include "fdf.h"

void	handle_scaling_key(int keycode, t_mat4s *mat)
{
	if (keycode == KEY_PLUS)
		*mat = mat4s_mult(*mat, mat_scale(1.5f));
	else if (keycode == KEY_MINUS)
		*mat = mat4s_mult(*mat, mat_scale(2.f / 3));
	else if (keycode == KEY_MULT)
		*mat = mat4s_mult(*mat, mat_scale_axis(2, 1.5f));
	else if (keycode == KEY_DIV)
		*mat = mat4s_mult(*mat, mat_scale_axis(2, 2.f / 3));
}

void	handle_rotation_key(int keycode, t_mat4s *mat)
{
	int		axis;
	float	angle;

	if (keycode == 'i' || keycode == 'k')
		axis = 0;
	else if (keycode == 'j' || keycode == 'l')
		axis = 1;
	else
		axis = 2;
	if (keycode == 'i' || keycode == 'j' || keycode == 'u')
		angle = M_PI / 12;
	else
		angle = -M_PI / 12;
	*mat = mat4s_mult(mat_rot(axis, angle), *mat);
}

void	handle_translation_key(int keycode, t_mat4s *mat)
{
	int		axis;
	float	mag;

	if (keycode == 'a' || keycode == 'd')
		axis = 0;
	else if (keycode == 'w' || keycode == 's')
		axis = 1;
	else
		axis = 2;
	if (keycode == 'd' || keycode == 's' || keycode == 'e')
		mag = 30.f;
	else
		mag = -30.f;
	*mat = mat4s_mult(mat_trans(axis, mag), *mat);
}
