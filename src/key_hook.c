#include "fdf.h"

bool	is_scaling_key(int keycode)
{
	return (keycode == KEY_PLUS || keycode == KEY_MINUS
			|| keycode == KEY_MULT || keycode == KEY_DIV);
}

bool	is_rotation_key(int keycode)
{
	return (keycode == 'u' || keycode == 'i' || keycode == 'o'
			|| keycode == 'j' || keycode == 'k' || keycode == 'l');
}

bool	is_translation_key(int keycode)
{
	return (keycode == 'q' || keycode == 'w' || keycode == 'e'
			|| keycode == 'a' || keycode == 's' || keycode == 'd');
}

bool	is_special_key(int keycode)
{
	return (keycode == KEY_ESC || keycode == 'c');
}


void	handle_scaling_key(int keycode, void *param)
{
	t_state	*st;

	st = param;
	if (keycode == KEY_PLUS)
		st->mat = mat4s_mult(st->mat, mat_scale(1.5f));
	else if (keycode == KEY_MINUS)
		st->mat = mat4s_mult(st->mat, mat_scale(2.f/3));
	else if (keycode == KEY_MULT)
		st->mat = mat4s_mult(st->mat, mat_scale_axis(2, 1.5f));
	else if (keycode == KEY_DIV)
		st->mat = mat4s_mult(st->mat, mat_scale_axis(2, 2.f/3));
	mlx_clear_window(st->mlx.ptr, st->mlx.win);
	draw_fdf(*st);
}

void	handle_rotation_key(int keycode, void *param)
{
	t_state	*st;
	int		axis;
	float	angle;

	st = param;
	if (keycode == 'i' || keycode == 'k')
		axis = 0;
	else if (keycode == 'j' || keycode == 'l')
		axis = 1;
	else
		axis = 2;
	if (keycode == 'i' || keycode == 'j' || keycode == 'u')
		angle = M_PI/12;
	else
		angle = -M_PI/12;
	st->mat = mat4s_mult(st->mat, mat_rot(axis, angle));
	mlx_clear_window(st->mlx.ptr, st->mlx.win);
	draw_fdf(*st);
}

void	handle_translation_key(int keycode, void *param)
{
	t_state	*st;
	int		axis;
	float	mag;

	st = param;
	if (keycode == 'a' || keycode == 'd')
		axis = 0;
	else if (keycode == 'w' || keycode == 's')
		axis = 1;
	else
		axis = 2;
	if (keycode == 'd' || keycode == 's' || keycode == 'e')
		mag = 30.f;
	else
		mag = -30.f;
	st->mat = mat4s_mult(mat_trans(axis, mag), st->mat);
	mlx_clear_window(st->mlx.ptr, st->mlx.win);
	draw_fdf(*st);
}

void	handle_special_key(int keycode, void *param)
{
	t_state	*st;

	st = param;
	if (keycode == 'c')
		mlx_clear_window(st->mlx.ptr, st->mlx.win);
	else if (keycode == KEY_ESC)
	{
		mlx_destroy_window(st->mlx.ptr, st->mlx.win);
		exit(0);
	}
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
	return (0);
}

	/*
	mat.val[0][0] = 30;
	mat.val[1][1] = 30;
	mat.val[2][2] = 3;
	mat = mat4s_mult(mat_rot(0, 0.7854), mat);
	mat = mat4s_mult(mat_rot(1, 0.6155), mat);
	*/
