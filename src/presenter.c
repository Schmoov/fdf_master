/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   presenter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:47:20 by parden            #+#    #+#             */
/*   Updated: 2024/10/12 20:49:02 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	expose_hook(void *param)
{
	presenter_update(param);
	return (69);
}

void	presenter_init(t_presenter *pres, char *path, int fd)
{
	model_init(pres->model, fd);
	if (!pres->model->color)
		return ((void)(write(2, "Parse error\n", 12)));
	view_init(pres->view, path);
	if (!pres->view->img)
		return ((void)(model_destroy(pres->model), write(2, "Mlx error\n", 10)));
	mlx_key_hook(pres->view->win, key_hook, pres);
	mlx_mouse_hook(pres->view->win, mouse_hook, pres);
	mlx_expose_hook(pres->view->win, expose_hook, pres);
	mlx_hook(pres->view->win, 17, 0L, close_with_cross, pres);
	mlx_loop(pres->view->mlx);
}

void	presenter_update(t_presenter *pres)
{
	model_vertex_shader(pres->model);
	view_update(pres);
}

void	presenter_destroy(t_presenter *pres)
{
	model_destroy(pres->model);
	view_destroy(pres->view);
}
