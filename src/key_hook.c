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

int	key_hook(int keycode, void *param)
{
	t_model	*model;
	t_view	*view;

	model = &(((t_controller *) param)->model);
	view = &(((t_controller *) param)->view);
	ft_printf("Pressed %c code is %d\n", keycode, keycode);
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(view->mlx, view->win);
		exit(0);
	}
	if (is_scaling_key(keycode))
		handle_scaling_key(keycode, &(model->mat_obj));
	else if (is_rotation_key(keycode))
		handle_rotation_key(keycode, &(model->mat_obj));
	else if (is_translation_key(keycode))
		handle_translation_key(keycode, &(model->mat_cam));
	model_update_vmap(model);
	controller_update_view(model, view);
	return (0);
}
