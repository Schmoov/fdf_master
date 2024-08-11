#include "fdf.h"

// bpp -> bits per pixel
static void	img_pixel_put(void *img, int x, int y, int color)
{
	int		*line;
	int		bpp;
	int		size;
	int		endian;

	line = (int *)mlx_get_data_addr(img, &bpp, &size, &endian);
	//ft_printf("bbp %d, sizL %d, end %d\n", bpp, size, endian);
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		line[y * size / sizeof(int) + x] = color;
}

static void	draw_line_n(void *img, t_vec4 v1, t_vec4 v2)
{
	int dx;
	int dy;
	int	i;

	dx = v2.e[0] - v1.e[0];
	dy = v2.e[1] - v1.e[1];
	if (!dx && !dy)
		return ;
	i = 0;
	if (ft_iabs(dx) >= ft_iabs(dy))
	{
		if (dx < 0)
			return (draw_line_n(img, v2, v1));
		while (i <= dx)
		{
			img_pixel_put(img, v1.e[0] + i, v1.e[1] + (i * dy / dx), COLOR_WHITE);
			i++;
		}
	}
	else
	{
		if (dy < 0)
			return (draw_line_n(img, v2, v1));
		while (i <= dy)
		{
			img_pixel_put(img, v1.e[0] + (i * dx / dy), v1.e[1] + i, COLOR_WHITE);
			i++;
		}
	}
	return ;
}

void	draw_fdf(t_model *model, void *img)
{
	int		i;
	int		j;
	int		idx;
	t_vec4	*vmap;

	vmap = model->vmap;
	i = 0;
	while (i < model->rows)
	{
		j = 0;
		while (j < model->cols)
		{
			idx = i * model->cols + j;
			if (i)
				draw_line_n(img, vmap[idx - model->cols], vmap[idx]);
			if (j)
				draw_line_n(img, vmap[idx - 1], vmap[idx]);
			j++;
		}
		i++;
	}
}
