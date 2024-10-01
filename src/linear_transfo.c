/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_transfo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:47:20 by parden            #+#    #+#             */
/*   Updated: 2024/10/01 20:47:34 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	assign_other_axis(int axis, int *ax1, int *ax2)
{
	if (axis == 0)
	{
		*ax1 = 1;
		*ax2 = 2;
	}
	else if (axis == 1)
	{
		*ax1 = 0;
		*ax2 = 2;
	}
	else
	{
		*ax1 = 0;
		*ax2 = 1;
	}
}

//axis==0 rotate around x 1 y 2 z
t_mat4s	mat_rot(int axis, float angle)
{
	t_mat4s	res;
	int		ax1;
	int		ax2;

	res = mat_id();
	assign_other_axis(axis, &ax1, &ax2);
	res.val[ax1][ax1] = cos(angle);
	res.val[ax2][ax2] = cos(angle);
	res.val[ax1][ax2] = -sin(angle);
	res.val[ax2][ax1] = sin(angle);
	return (res);
}

t_mat4s	mat_scale(float factor)
{
	t_mat4s	res;

	res = mat_id();
	res.val[0][0] = factor;
	res.val[1][1] = factor;
	res.val[2][2] = factor;
	return (res);
}

t_mat4s	mat_scale_axis(int axis, float factor)
{
	t_mat4s	res;

	res = mat_id();
	res.val[axis][axis] = factor;
	return (res);
}

t_mat4s	mat_trans(int axis, float mag)
{
	t_mat4s	res;

	res = mat_id();
	res.val[axis][3] = mag;
	return (res);
}
