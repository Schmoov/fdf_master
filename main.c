#include <mlx.h>
#include "libft/include/libft.h"

#define LEFT	65361
#define DOWN	65364
#define UP		65362
#define RIGHT	65363

typedef struct {
	void	*ptr;
	void	*win;
}			t_mlx;

typedef struct {
	int		x;
	int		y;
}			vec2;

int	**parse_map(char *path)
{
	int		**res;
	int		fd = open(path, O_RDONLY);
	int		nb_line = 0;
	char	*line = get_next_line(fd);

	while (line)
	{
		nb_line++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);

	res = malloc((nb_line + 1) * sizeof(int *));
	res[nb_line] = NULL;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);

	int i = 0;
	while (line)
	{
		char	**split = ft_split(line, ' ')
		res[i] = 

void	draw_line(vec2 start, vec2 end, t_mlx *mlx)
{
	float slope = (end.y - start.y)/(end.x - start.y);

	for (int i = start.x ; i <= end.x; i++)
	{
		mlx_pixel_put(mlx->ptr, mlx->win, i, slope*i, INT_MAX);
	}
}

int	key_hook(int keycode, void *param)
{
	t_mlx	*mlx = param;

	vec2	start = {0, 0};
	vec2	end = {100, 100};
	
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
