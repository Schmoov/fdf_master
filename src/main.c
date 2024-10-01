/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:47:20 by parden            #+#    #+#             */
/*   Updated: 2024/10/01 20:54:18 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_presenter	pres;
	t_view		view;
	t_model		model;

	if (argc != 2)
		return (write(2, "Fdf expects a single file\n", 26));
	pres.view = &view;
	pres.model = &model;
	presenter_init(&pres, argv[1]);
}
