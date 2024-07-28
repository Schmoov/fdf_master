#include "fdf.h"

int	main()
{
	t_state	st;

	st.mlx.ptr = mlx_init();
	st.mlx.win = mlx_new_window(st.mlx.ptr, WIN_WIDTH, WIN_HEIGHT, "win0");
	st.hmap = parse_hmap("maps/mars.fdf");
	st.mat = mat_id();
	st.img = mlx_new_image(st.mlx.ptr, WIN_WIDTH, WIN_HEIGHT);
	st.vmap = init_vmap(st.hmap);
	mlx_key_hook(st.mlx.win, key_hook, &st);
	mlx_loop(st.mlx.ptr);
}
