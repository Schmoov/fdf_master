#include "fdf.h"

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
