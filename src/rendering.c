#include "fdf.h"

void	draw_segment(t_mlx mlx, t_vec4 v1, t_vec4 v2)
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
			return (draw_segment(mlx, v2, v1));
		while (i <= dx)
		{
			mlx_pixel_put(mlx.ptr, mlx.win, v1.e[0] + i, v1.e[1] + (i * dy / dx), COLOR_WHITE);
			i++;
		}
	}
	else
	{
		if (dy < 0)
			return (draw_segment(mlx, v2, v1));
		while (i <= dy)
		{
			mlx_pixel_put(mlx.ptr, mlx.win, v1.e[0] + (i * dx / dy), v1.e[1] + i, COLOR_WHITE);
			i++;
		}
	}
	return ;
}

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
	t_vec4	v;

	i = 0;
	while (i < st.hmap.rows)
	{
		j = 0;
		while (j < st.hmap.cols)
		{
			v = (t_vec4){j, i, st.hmap.height[i * st.hmap.cols + j], 1};
			st.vmap.val[i * st.hmap.cols + j] = mat4s_vec4_mult(st.mat, v);
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
				draw_segment(st.mlx, v.val[(i-1)*v.cols+j], v.val[i*v.cols+j]);
			if (j)
				draw_segment(st.mlx, v.val[i*v.cols+j-1], v.val[i*v.cols+j]);
			j++;
		}
		i++;
	}
}
