/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_algebra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:47:20 by parden            #+#    #+#             */
/*   Updated: 2024/10/01 20:47:34 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mat4s	mat_nul(void)
{
	t_mat4s	res;

	ft_memset(res.val, 0, sizeof(res.val));
	return (res);
}

t_mat4s	mat_id(void)
{
	t_mat4s	res;

	ft_memset(res.val, 0, sizeof(res.val));
	res.val[0][0] = 1;
	res.val[1][1] = 1;
	res.val[2][2] = 1;
	res.val[3][3] = 1;
	return (res);
}

t_mat4s	mat4s_mult(t_mat4s left, t_mat4s right)
{
	t_mat4s	res;
	int		i;
	int		j;
	int		k;

	res = mat_nul();
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				res.val[i][j] += left.val[i][k] * right.val[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (res);
}

t_vec4	mat4s_vec4_mult(t_mat4s mat, t_vec4 v)
{
	t_vec4	res;
	int		i;
	int		j;

	res = (t_vec4){0.f, 0.f, 0.f, 0.f};
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res.e[i] += mat.val[i][j] * v.e[j];
			j++;
		}
		i++;
	}
	return (res);
}
