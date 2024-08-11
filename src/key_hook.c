#include "fdf.h"

static bool	is_scaling_key(int keycode)
{
	return (keycode == KEY_PLUS || keycode == KEY_MINUS
			|| keycode == KEY_MULT || keycode == KEY_DIV);
}

static bool	is_rotation_key(int keycode)
{
	return (keycode == 'u' || keycode == 'i' || keycode == 'o'
			|| keycode == 'j' || keycode == 'k' || keycode == 'l');
}

static bool	is_translation_key(int keycode)
{
	return (keycode == 'q' || keycode == 'w' || keycode == 'e'
			|| keycode == 'a' || keycode == 's' || keycode == 'd');
}

static bool	is_special_key(int keycode)
{
	return (keycode == KEY_ESC || keycode == 'c');
}

int	key_hook(int keycode, void *param)
{
	ft_printf("Pressed %c code is %d\n", keycode, keycode);
	if (is_scaling_key(keycode))
		handle_scaling_key(keycode, param);
	else if (is_rotation_key(keycode))
		handle_rotation_key(keycode, param);
	else if (is_translation_key(keycode))
		handle_translation_key(keycode, param);
	else if (is_special_key(keycode))
		handle_special_key(keycode, param);
	/*
	if (keycode == 'x')
	{
		t_state	*st = param;
		int w, h;
		void *img = mlx_xpm_file_to_image(st->mlx.ptr, "xpm/arrow.xpm", &w, &h);
		ft_printf("%d, %d\n", w, h);
		mlx_put_image_to_window(st->mlx.ptr, st->mlx.win, img, 100, 100);
	}
	*/
	return (0);
}
