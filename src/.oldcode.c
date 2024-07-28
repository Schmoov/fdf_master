
#include <stdio.h>
void	print_mat(t_mat4s m)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			printf("%.2f", m.val[i][j]);
			if (j != 3)
				printf("|");
		}
		printf("\n");
	}
}

void	print_vmap(t_vmap vmap)
{
	int r = vmap.rows;
	int c = vmap.cols;
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			printf("(%.0f, %.0f, %.0f, %.0f)", vmap.val[i*c+j].e[0], vmap.val[i*c+j].e[1], vmap.val[i*c+j].e[2], vmap.val[i*c+j].e[3]);
		}
		printf("\n");
	}
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

