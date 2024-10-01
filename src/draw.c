#include "fdf.h"

// bpp -> bits per pixel
static void	img_pixel_put(void *img, int x, int y, int color)
{
	int		*line;
	int		bpp;
	int		size;
	int		endian;

	line = (int *)mlx_get_data_addr(img, &bpp, &size, &endian);
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		line[y * size / sizeof(int) + x] = color;
}

static int	color_mid(int c1, int c2, float b)
{
	int res;

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

static void	draw_line_dl(t_presenter *p, int i1, int i2, float dl)
{
	int		i;
	t_vec4	v;
	int		color;

	i = 0;
	while (i < roundf(dl))
	{
		v = vec_mid(p->model->vertex[i1], p->model->vertex[i2], i / dl);
		color = color_mid(p->model->color[i1], p->model->color[i2], i / dl);
		img_pixel_put(p->view->img, v.e[0], v.e[1], color);
		i++;
	}
}

static void	draw_line(t_presenter *p, int i1, int i2)
{
	float	dx;
	float	dy;
	
	dx = p->model->vertex[i2].e[0] -  p->model->vertex[i1].e[0];
	dy = p->model->vertex[i2].e[1] -  p->model->vertex[i1].e[1];
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
				draw_line(p, idx - cols, idx);
			if (j)
				draw_line(p, idx - 1, idx);
			j++;
		}
		i++;
	}
}
