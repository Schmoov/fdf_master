#include "fdf.h"


int	key_hook(int keycode, void *param)
{
	t_mlx	*mlx = param;
	
	ft_printf("Pressed %c code is %d\n", keycode, keycode);

	//		MOIRE
	if (keycode == 'm')
	{
		t_vec4	c = {{WIN_WIDTH/2.f, WIN_HEIGHT/2.f, 0, 1}};
		float	r = fmin(WIN_WIDTH, WIN_HEIGHT)/2;
		for (int theta = 0; theta < 180; theta++)
		{
			float angle = theta * 2.f * M_PI / 180.f;
			t_vec4 p = {c.e[0]+r*cos(angle), c.e[1]+r*sin(angle), c.e[2], c.e[3]};
			draw_segment(c, p, mlx);
		}
	}

	if (keycode == KEY_ESC)
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
	mlx.win = mlx_new_window(mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "win0");
	mlx_key_hook(mlx.win, key_hook, &mlx);
	mlx_loop(mlx.ptr);
}
