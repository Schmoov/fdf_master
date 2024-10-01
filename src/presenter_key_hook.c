/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presenter_key_hook.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:47:20 by parden            #+#    #+#             */
/*   Updated: 2024/10/01 20:52:27 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	model = ((t_presenter *)param)->model;
	view = ((t_presenter *)param)->view;
	if (keycode == KEY_ESC)
	{
		presenter_destroy(param);
		exit(0);
	}
	if (is_scaling_key(keycode))
		handle_scaling_key(keycode, &(model->mat_obj));
	else if (is_rotation_key(keycode))
		handle_rotation_key(keycode, &(model->mat_obj));
	else if (is_translation_key(keycode))
		handle_translation_key(keycode, &(model->mat_cam));
	presenter_update(param);
	return (0);
}
