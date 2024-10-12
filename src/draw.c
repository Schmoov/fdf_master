/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:44:56 by parden            #+#    #+#             */
/*   Updated: 2024/10/12 20:21:00 by parden           ###   ########.fr       */
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
