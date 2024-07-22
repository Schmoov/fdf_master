#include "fdf.h"

void	hmap_to_screen_vert(t_mat24 mat24, t_hmap *hmap, t_screen_vertex *res)
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
			res->vertex[i * hmap->cols + j] = mat24_vec4_mult(mat24, v);
			j++;
		}
		i++;
	}
}

