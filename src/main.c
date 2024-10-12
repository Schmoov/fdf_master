/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:47:20 by parden            #+#    #+#             */
/*   Updated: 2024/10/12 20:02:28 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_presenter	pres;
	t_view		view;
	t_model		model;
	int			fd;

	if (argc != 2)
		return (write(2, "Fdf expects a single file\n", 26));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		write(2, "Fdf cannot open ", 16);
		write(2, argv[1], ft_strlen(argv[1]));
		write(2, "\n", 1);
		return (0);
	}
	pres.view = &view;
	pres.model = &model;
	presenter_init(&pres, argv[1], fd);
}
