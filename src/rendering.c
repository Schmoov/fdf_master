#include "fdf.h"

void	draw_segment(t_vec4 v1, t_vec4 v2, t_mlx *mlx)
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
			return (draw_segment(v2, v1, mlx));
		while (i <= dx)
		{
			mlx_pixel_put(mlx->ptr, mlx->win, v1.e[0] + i, v1.e[1] + (i * dy / dx), COLOR_WHITE);
			i++;
		}
	}
	else
	{
		if (dy < 0)
			return (draw_segment(v2, v1, mlx));
		while (i <= dy)
		{
			mlx_pixel_put(mlx->ptr, mlx->win, v1.e[0] + (i * dx / dy), v1.e[1] + i, COLOR_WHITE);
			i++;
		}
	}
	return ;
}

void	hmap_to_4dvxmap(t_mat4s mat, t_hmap *hmap, t_4dvxmap *res)
{
	int		i;
	int		j;
	t_vec4	v;

	i = 0;
	while (i < hmap->rows)
	{
		j = 0;
		while (j < hmap->cols)
		{
			v = (t_vec4){j, i, hmap->height[i * hmap->cols + j], 1};
			res->vertex[i * hmap->cols + j] = mat4s_vec4_mult(mat, v);
			j++;
		}
		i++;
	}
}

