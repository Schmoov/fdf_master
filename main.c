#include <mlx.h>
#include "libft/libft.h"

#define LEFT	65361
#define DOWN	65364
#define UP		65362
#define RIGHT	65363

typedef struct s_mlx{
	void	*ptr;
	void	*win;
}			t_mlx;

typedef struct s_v2{
	int		e1;
	int		e2;
}			t_v2;

void	draw_segment(t_v2 start, t_v2 end, t_mlx *mlx)
{
	int dx;
	int dy;
	int	i;

	dx = end.e1 - start.e1;
	dy = end.e2 - start.e2;
	if (dx >= dy)
	{
		i = start.x;
		while (i
		for (int i = start.x ; i <= end.x; i++)
		{
			mlx_pixel_put(mlx->ptr, mlx->win, i, slope*i, INT_MAX);
		}
	}
}

int	key_hook(int keycode, void *param)
{
	t_mlx	*mlx = param;

	t_v2	start = {0, 0};
	t_v2	end = {100, 100};
	
	ft_printf("Pressed %c code is %d\n", keycode, keycode);

	if (keycode == LEFT)
		draw_line(start, end, mlx);
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
