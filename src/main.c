#include "fdf.h"

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

int	main()
{
	t_state	st;

	st.mlx.ptr = mlx_init();
	st.mlx.win = mlx_new_window(st.mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "win0");
	st.hmap = parse_hmap("maps/42.fdf");
	st.mat = mat_id();
	st.img = mlx_new_image(st.mlx.ptr, WIN_WIDTH, WIN_HEIGHT);
	st.vmap = init_vmap(st.hmap);
	mlx_key_hook(st.mlx.win, key_hook, &st);
	mlx_loop(st.mlx.ptr);
}
