#include "fdf.h"

void	img_pixel_put(t_state st, int x, int y, int color)
{
	int		*line;
	int		bits_per_pixel;
	int		size_line;
	int		endian;

	line = (int *)mlx_get_data_addr(st.img, &bits_per_pixel, &size_line, &endian);
	//ft_printf("bbp %d, sizL %d, end %d\n", bits_per_pixel, size_line, endian);
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		line[y * size_line / sizeof(int) + x] = mlx_get_color_value(st.mlx.ptr, color);
}

void	draw_segment(t_state st, t_vec4 v1, t_vec4 v2)
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
			return (draw_segment(st, v2, v1));
		while (i <= dx)
		{
			img_pixel_put(st, v1.e[0] + i, v1.e[1] + (i * dy / dx), COLOR_WHITE);
			i++;
		}
	}
	else
	{
		if (dy < 0)
			return (draw_segment(st, v2, v1));
		while (i <= dy)
		{
			img_pixel_put(st, v1.e[0] + (i * dx / dy), v1.e[1] + i, COLOR_WHITE);
			i++;
		}
	}
	return ;
}

/*
void	draw_moire(t_mlx mlx, float nb_radius)
{
	t_vec4	c = {{WIN_WIDTH/2.f, WIN_HEIGHT/2.f, 0, 1}};
	float	r = fmin(WIN_WIDTH, WIN_HEIGHT)/2;
	for (int theta = 0; theta < nb_radius; theta++)
	{
		float angle = theta * 2.f * M_PI / nb_radius;
		t_vec4 p = {c.e[0]+r*cos(angle), c.e[1]+r*sin(angle), c.e[2], c.e[3]};
		draw_segment(mlx, c, p);
	}
}
*/

t_vmap	init_vmap(t_hmap hmap)
{
	t_vmap	res;

	res.rows = hmap.rows;
	res.cols = hmap.cols;
	res.val = malloc(res.rows * res.cols * sizeof(*(res.val)));
	return (res);
}

void	update_vmap(t_state st)
{
	int		i;
	int		j;
	int		rows;
	int		cols;
	t_vec4	v;

	i = 0;
	rows = st.hmap.rows;
	cols = st.hmap.cols;
	while (i < rows)
	{
		j = 0;
		while (j < cols)
		{
			v = (t_vec4){j - cols / 2.f, i - rows / 2.f, st.hmap.height[i * cols + j], 1};
			st.vmap.val[i * cols + j] = mat4s_vec4_mult(st.mat, v);
			j++;
		}
		i++;
	}
}

void	draw_fdf(t_state st)
{
	int		i;
	int		j;
	t_vmap	v;

	update_vmap(st);
	i = 0;
	v = st.vmap;
	while (i < v.rows)
	{
		j = 0;
		while (j < v.cols)
		{
			if (i)
				draw_segment(st, v.val[(i-1)*v.cols+j], v.val[i*v.cols+j]);
			if (j)
				draw_segment(st, v.val[i*v.cols+j-1], v.val[i*v.cols+j]);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(st.mlx.ptr, st.mlx.win, st.img, 0, 0);
}
