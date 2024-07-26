#include "fdf.h"

int	key_hook(int keycode, void *param)
{
	/*
	mat.val[0][0] = 30;
	mat.val[1][1] = 30;
	mat.val[2][2] = 3;
	mat = mat4s_mult(mat_rot(0, 0.7854), mat);
	mat = mat4s_mult(mat_rot(1, 0.6155), mat);
	*/
	t_state	*st = param;
	
	ft_printf("Pressed %c code is %d\n", keycode, keycode);

	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(st->mlx.ptr, st->mlx.win);
		exit(0);
	}
	if (keycode == KEY_PLUS)
	{
		st->mat = mat4s_mult(st->mat, mat_scale(1.5f));
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
		draw_fdf(*st);
	}
	if (keycode == KEY_MINUS)
	{
		st->mat = mat4s_mult(st->mat, mat_scale(2.f/3));
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
		draw_fdf(*st);
	}
	if (keycode == KEY_MULT)
	{
		st->mat = mat4s_mult(st->mat, mat_scale_axis(2, 1.5f));
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
		draw_fdf(*st);
	}
	if (keycode == KEY_DIV)
	{
		st->mat = mat4s_mult(st->mat, mat_scale_axis(2, 2.f/3));
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
		draw_fdf(*st);
	}
	if (keycode == 'i')
	{
		st->mat = mat4s_mult(st->mat, mat_rot(0, M_PI/12));
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
		draw_fdf(*st);
	}
	if (keycode == 'k')
	{
		st->mat = mat4s_mult(st->mat, mat_rot(0, -M_PI/12));
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
		draw_fdf(*st);
	}
	if (keycode == 'j')
	{
		st->mat = mat4s_mult(st->mat, mat_rot(1, M_PI/12));
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
		draw_fdf(*st);
	}
	if (keycode == 'l')
	{
		st->mat = mat4s_mult(st->mat, mat_rot(1, -M_PI/12));
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
		draw_fdf(*st);
	}
	if (keycode == 'u')
	{
		st->mat = mat4s_mult(st->mat, mat_rot(2, M_PI/12));
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
		draw_fdf(*st);
	}
	if (keycode == 'o')
	{
		st->mat = mat4s_mult(st->mat, mat_rot(2, -M_PI/12));
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
		draw_fdf(*st);
	}
	if (keycode == 'w')
	{
		st->mat = mat4s_mult(mat_trans(1, -30), st->mat);
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
		draw_fdf(*st);
	}
	if (keycode == 's')
	{
		st->mat = mat4s_mult(mat_trans(1, 30), st->mat);
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
		draw_fdf(*st);
	}
	if (keycode == 'a')
	{
		st->mat = mat4s_mult(mat_trans(0, -30), st->mat);
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
		draw_fdf(*st);
	}
	if (keycode == 'd')
	{
		st->mat = mat4s_mult(mat_trans(0, 30), st->mat);
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
		draw_fdf(*st);
	}
	if (keycode == 'c')
		mlx_clear_window(st->mlx.ptr, st->mlx.win);

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
	t_state	st;

	st.mlx.ptr = mlx_init();
	st.mlx.win = mlx_new_window(st.mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "win0");
	st.hmap = parse_hmap("maps/42.fdf");
	st.mat = mat_id();
	st.vmap = init_vmap(st.hmap);
	mlx_key_hook(st.mlx.win, key_hook, &st);
	mlx_loop(st.mlx.ptr);
}
