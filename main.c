#include "fdf.h"

void	draw_segment(t_vec2 v1, t_vec2 v2, t_mlx *mlx)
{
	int dx;
	int dy;
	int	i;
	int	first;

	dx = v2.e1 - v1.e1;
	dy = v2.e2 - v1.e2;
	if (!dx && !dy)
		return ;
	i = 0;
	if (ft_iabs(dx) >= ft_iabs(dy))
	{
		if (dx < 0)
			return (draw_segment(v2, v1, mlx));
		while (i <= dx)
		{
			mlx_pixel_put(mlx->ptr, mlx->win, v1.e1 + i, v1.e2 + (i * dy / dx), COLOR_WHITE);
			i++;
		}
	}
	else
	{
		if (dy < 0)
			return (draw_segment(v2, v1, mlx));
		while (i <= dy)
		{
			mlx_pixel_put(mlx->ptr, mlx->win, v1.e1 + (i * dx / dy), v1.e2 + i, COLOR_WHITE);
			i++;
		}
	}
	return ;
}

int	key_hook(int keycode, void *param)
{
	t_mlx	*mlx = param;

	t_vec2	o = {320, 240};
	t_vec2	l = {220, 240};
	t_vec2	d = {320, 340};
	t_vec2	u = {320, 140};
	t_vec2	r = {420, 240};
	
	ft_printf("Pressed %c code is %d\n", keycode, keycode);

	if (keycode == 'c')
		for (int theta = 0; theta < 360; theta++)
		{
			t_vec2 p = {o.e1 + 240*cos(theta*2*M_PI/360), o.e2 + 240*sin(theta*2*M_PI/360)};
			draw_segment(o, p, mlx);
		}
	if (keycode == 'd')
	{
		t_hmap map = parse_hmap("maps/42.fdf");
		for (int i = 0; i < map.row; i++)
		{
			for (int j = 0; j < map.col; j++)
			{
				t_vec2 v1;
				t_vec2 v2;
				if (j)
				{
					v1 = (t_vec2){(j-1)*20+50, i*20+50};
					v2 = (t_vec2){j*20 + 50, i*20 + 50};
					draw_segment(v1, v2, mlx);
				}
				if (i)
				{
					v1 = (t_vec2){j*20+50, (i-1)*20+50};
					v2 = (t_vec2){j*20 + 50, i*20 + 50};
					draw_segment(v1, v2, mlx);
				}
			}
		}
	}
	if (keycode == 'r')
	{
		t_hmap map = parse_hmap("maps/42.fdf");
		for (int i = 0; i < map.row; i++)
		{
			for (int j = 0; j < map.col; j++)
			{
				t_vec2 v1;
				t_vec2 v2;
				if (j)
				{
					v1 = (t_vec2){(j-1)*20+50, i*20+50};
					v2 = (t_vec2){j*20 + 50, i*20 + 50};
					v1.e1 = cos(M_PI/12)*v1.e1 - sin(M_PI/12)*v1.e2+50-5*map.height[i*map.col+j-1];
					v1.e2 = sin(M_PI/12)*v1.e1 + cos(M_PI/12)*v1.e2-5*map.height[i*map.col+j-1];
					v2.e1 = cos(M_PI/12)*v2.e1 - sin(M_PI/12)*v2.e2+50-5*map.height[i*map.col+j];
					v2.e2 = sin(M_PI/12)*v2.e1 + cos(M_PI/12)*v2.e2-5*map.height[i*map.col+j];
					draw_segment(v1, v2, mlx);
				}
				if (i)
				{
					v1 = (t_vec2){j*20+50, (i-1)*20+50};
					v2 = (t_vec2){j*20 + 50, i*20 + 50};
					v1.e1 = cos(M_PI/12)*v1.e1 - sin(M_PI/12)*v1.e2+50-5*map.height[(i-1)*map.col+j];
					v1.e2 = sin(M_PI/12)*v1.e1 + cos(M_PI/12)*v1.e2-5*map.height[(i-1)*map.col+j];
					v2.e1 = cos(M_PI/12)*v2.e1 - sin(M_PI/12)*v2.e2+50-5*map.height[i*map.col+j];
					v2.e2 = sin(M_PI/12)*v2.e1 + cos(M_PI/12)*v2.e2-5*map.height[i*map.col+j];
					draw_segment(v1, v2, mlx);
				}
			}
		}
	}
	if (keycode == KEY_LEFT)
		draw_segment(o, l, mlx);
	if (keycode == KEY_DOWN)
		draw_segment(o, d, mlx);
	if (keycode == KEY_UP)
		draw_segment(o, u, mlx);
	if (keycode == KEY_RIGHT)
		draw_segment(o, r, mlx);
	/*
	if (keycode == DOWN)
		draw_square(300, 440, 40, mlx);
	if (keycode == UP)
		draw_square(300, 0, 40, mlx);
	if (keycode == RIGHT)
		draw_square(600, 220, 40, mlx);
	*/
	if (keycode == 'q')
	{
		mlx_destroy_window(mlx->ptr, mlx->win);
		exit(0);
	}
	return (0);
}

int	main()
{
	t_mlx	mlx;

	mlx.ptr = mlx_init();
	mlx.win = mlx_new_window(mlx.ptr, 640, 480, "win0");
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_loop(mlx.ptr);
}
