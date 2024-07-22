#include "fdf.h"

t_mat4s	mat_nul(void)
{
	t_mat4s	res;

	ft_memset(res.val, 0, sizeof(res.val));
	return (res);
}

t_mat4s	mat_id(void)
{
	t_mat4s	res;

	ft_memset(res.val, 0, sizeof(res.val));
	res.val[0][0] = 1;
	res.val[1][1] = 1;
	res.val[2][2] = 1;
	res.val[3][3] = 1;
	return (res);
}

t_mat4s	mat4s_mult(t_mat4s left, t_mat4s right)
{
	t_mat4s	res;
	int		i;
	int		j;
	int		k;

	res = mat_nul();
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			k = 0;
			while (k < 4)
			{
				res.val[i][j] += left.val[i][k] * right.val[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (res);
}

t_vec2	mat24_vec4_mult(t_mat24 mat, t_vec4 v)
{
	t_vec2	res;
	int		i;
	int		j;

	res = (t_vec2){0, 0};
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 4)
		{
			res.e[i] += mat.val[i][j] * v.e[j];
			j++;
		}
		i++;
	}
	return (res);
}


void	assign_other_axis(int axis, int *ax1, int *ax2)
{
	if (axis == 0)
	{
		*ax1 = 1;
		*ax2 = 2;
	}
	else if (axis == 1)
	{
		*ax1 = 0;
		*ax2 = 2;
	}
	else
	{
		*ax1 = 0;
		*ax2 = 1;
	}
}

//axis==0 rotate around x 1 y 2 z
t_mat4s	mat_rot(int axis, double angle)
{
	t_mat4s	res;
	int		ax1;
	int		ax2;

	res = mat_id();
	assign_other_axis(axis, &ax1, &ax2);
	res.val[ax1][ax1] = cos(angle);
	res.val[ax2][ax2] = cos(angle);
	res.val[ax1][ax2] = -sin(angle);
	res.val[ax2][ax1] = sin(angle);
	return (res);
}


hmap_to_screen_vert(t_mat24 mat24, t_hmap *hmap, t_screen_vertex *res)
{
	int		i;
	int		j;
	t_vec4	v;

	i = 0;
	while (i < hmap.rows)
	{
		j = 0;
		while (j < hmap.cols)
		{
			v = (vec4){j, i, hmap->val[i * hmap.cols + j], 1}
			res->vertex[i][j] = mat24_vec4_mult(mat4, v);
			j++;
		}
		i++;
	}
}

