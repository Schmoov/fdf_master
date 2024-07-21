#include <mlx.h>
#include <math.h>
#include "libft/libft.h"

#define KEY_LEFT	65361
#define KEY_DOWN	65364
#define KEY_UP		65362
#define KEY_RIGHT	65363

#define COLOR_WHITE	0xffffff

typedef struct s_mlx{
	void	*ptr;
	void	*win;
}			t_mlx;

typedef struct s_v2{
	int		e1;
	int		e2;
}			t_v2;

void	draw_segment(t_v2 v1, t_v2 v2, t_mlx *mlx)
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

	t_v2	o = {320, 240};
	t_v2	l = {220, 240};
	t_v2	d = {320, 340};
	t_v2	u = {320, 140};
	t_v2	r = {420, 240};
	
	ft_printf("Pressed %c code is %d\n", keycode, keycode);

	if (keycode == 'c')
		for (int theta = 0; theta < 360; theta++)
		{
			t_v2 p = {o.e1 + 240*cos(theta*2*M_PI/360), o.e2 + 240*sin(theta*2*M_PI/360)};
			draw_segment(o, p, mlx);
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
