/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:04:45 by parden            #+#    #+#             */
/*   Updated: 2024/10/14 20:54:46 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	color_mid(int c1, int c2, float b)
{
	int	res;

	res = (int)((c1 & 0xff) * (1 - b) + (c2 & 0xff) * b);
	res |= 0xff00 & (int)((c1 & 0xff00) * (1 - b) + (c2 & 0xff00) * b);
	res |= 0xff0000 & (int)((c1 & 0xff0000) * (1 - b) + (c2 & 0xff0000) * b);
	return (res);
}

t_vec4	vec_mid(t_vec4 v1, t_vec4 v2, float b)
{
	t_vec4	res;

	res.e[0] = v1.e[0] * (1 - b) + v2.e[0] * b;
	res.e[1] = v1.e[1] * (1 - b) + v2.e[1] * b;
	res.e[2] = v1.e[2] * (1 - b) + v2.e[2] * b;
	return (res);
}

bool	is_offcam(t_vec4 v)
{
	return ((int)v.e[0] < 0 || (int)v.e[0] > WIN_WIDTH
		|| (int)v.e[1] < 0 || (int)v.e[1] > WIN_HEIGHT
		|| (int)v.e[2] > 0);
}
