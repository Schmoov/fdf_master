/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:44:56 by parden            #+#    #+#             */
/*   Updated: 2024/10/01 20:47:34 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// bpp -> bits per pixel
static void	img_pixel_put(void *img, t_vec4 v, int color)
{
	int		*line;
	int		bpp;
	int		size;
	int		endian;

	line = (int *)mlx_get_data_addr(img, &bpp, &size, &endian);
	line[(int)v.e[1] * size / sizeof(int) + (int)v.e[0]] = color;
}

static int	color_mid(int c1, int c2, float b)
{
	int	res;

	res = (int)((c1 & 0xff) * (1 - b) + (c2 & 0xff) * b);
	res |= (int)((c1 & 0xff00) * (1 - b) + (c2 & 0xff00) * b);
	res |= (int)((c1 & 0xff0000) * (1 - b) + (c2 & 0xff0000) * b);
	return (res);
}

static t_vec4	vec_mid(t_vec4 v1, t_vec4 v2, float b)
{
	t_vec4	res;

	res.e[0] = v1.e[0] * (1 - b) + v2.e[0] * b;
	res.e[1] = v1.e[1] * (1 - b) + v2.e[1] * b;
	res.e[2] = v1.e[2] * (1 - b) + v2.e[2] * b;
	return (res);
}

static bool	is_offcam(t_vec4 v)
{
	return ((int)v.e[0] < 0 || (int)v.e[0] > WIN_WIDTH
		|| (int)v.e[1] < 0 || (int)v.e[1] > WIN_HEIGHT
		|| (int)v.e[2] > 0);
}

static void	draw_line_dl(t_presenter *p, int i1, int i2, float dl)
{
	int		i;
	t_vec4	v;
	int		color;

	if (is_offcam(p->model->vertex[i1]) || is_offcam(p->model->vertex[i2]))
		return ;
	i = 0;
	while (i < roundf(dl))
	{
		v = vec_mid(p->model->vertex[i1], p->model->vertex[i2], i / dl);
		color = color_mid(p->model->color[i1], p->model->color[i2], i / dl);
		img_pixel_put(p->view->img, v, color);
		i++;
	}
}

static void	draw_line(t_presenter *p, int i1, int i2)
{
	float	dx;
	float	dy;

	dx = p->model->vertex[i2].e[0] - p->model->vertex[i1].e[0];
	dy = p->model->vertex[i2].e[1] - p->model->vertex[i1].e[1];
	if (fabs(dx) >= fabs(dy))
	{
		if (dx >= 0)
			draw_line_dl(p, i1, i2, dx);
		else
			draw_line_dl(p, i2, i1, -dx);
	}
	else
	{
		if (dy >= 0)
			draw_line_dl(p, i1, i2, dy);
		else
			draw_line_dl(p, i2, i1, -dy);
	}
}

void	draw_img(t_presenter *p)
{
	int		i;
	int		j;
	int		idx;
	int		cols;

	cols = p->model->cols;
	i = 0;
	while (i < p->model->rows)
	{
		j = 0;
		while (j < cols)
		{
			idx = i * cols + j;
			if (i)
				draw_line(p, idx, idx - cols);
			if (j)
				draw_line(p, idx, idx - 1);
			j++;
		}
		i++;
	}
}
