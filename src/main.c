#include "fdf.h"

int	key_hook(int keycode, void *param)
{
	t_mlx	*mlx = param;
	
	ft_printf("Pressed %c code is %d\n", keycode, keycode);

	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(mlx->ptr, mlx->win);
		exit(0);
	}
	if (keycode == 'c')
		mlx_clear_window(mlx->ptr, mlx->win);
	if (keycode == 'd')
		draw_fdf(*mlx);
	//		MOIRE
	if (keycode == 's')
		draw_moire(*mlx, 11);
	if (keycode == 'm')
		draw_moire(*mlx, 64);
	if (keycode == 'l')
		draw_moire(*mlx, 217);

	return (0);
}

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
	t_mlx	mlx;

	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "win0");
	mlx.hmap = parse_hmap("maps/42.fdf");
	t_mat4s mat = mat_id();
	mat.val[0][0] = 30;
	mat.val[1][1] = 30;
	mat.val[2][2] = 3;
	mat = mat4s_mult(mat_rot(0, 0.7854), mat);
	mat = mat4s_mult(mat_rot(1, 0.6155), mat);
	mlx.vmap = hmap_to_vmap(mlx.hmap, mat);
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_loop(mlx.ptr);
}
