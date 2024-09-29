#include "fdf.h"

// bpp -> bits per pixel
static void	img_pixel_put(void *img, int x, int y, int z, int color)
{
	int		*line;
	int		bpp;
	int		size;
	int		endian;

	if (z >= 0)
		return ;
	line = (int *)mlx_get_data_addr(img, &bpp, &size, &endian);
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		line[y * size / sizeof(int) + x] = color;
}

static void	draw_line_n(void *img, t_vec4 v1, t_vec4 v2, int color1, int color2)
{
	float dx;
	float dy;
	float dz;
	int	i;

	dx = v2.e[0] - v1.e[0];
	dy = v2.e[1] - v1.e[1];
	dz = v2.e[2] - v1.e[2];
	if (!dx && !dy)
		return ;
	i = 0;
	if (ft_iabs(dx) >= ft_iabs(dy))
	{
		if (dx < 0)
			return (draw_line_n(img, v2, v1,color2,color1));
		while (i <= dx)
		{
			img_pixel_put(img, v1.e[0] + i, v1.e[1] + (i * dy / dx), v1.e[2] + (i * dz / dx),
				 (color1*(dx-i) + color2*i)/dx);
			i++;
		}
	}
	else
	{
		if (dy < 0)
			return (draw_line_n(img, v2, v1,color2,color1));
		while (i <= dy)
		{
			img_pixel_put(img, v1.e[0] + (i * dx / dy), v1.e[1] + i, v1.e[2] + (i * dz / dy),
				 (color1*(dy-i) + color2*i)/dy);
			i++;
		}
	}
	return ;
}

void	view_draw_img(t_presenter *p)
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
				draw_line_n(p->view->img, p->model->vertex[idx - cols], p->model->vertex[idx]
				, p->model->color[idx-cols], p->model->color[idx]);
			if (j)
				draw_line_n(p->view->img, p->model->vertex[idx - 1], p->model->vertex[idx]
				, p->model->color[idx-1], p->model->color[idx]);
			j++;
		}
		i++;
	}
}
