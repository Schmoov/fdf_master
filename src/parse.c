/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 20:47:20 by parden            #+#    #+#             */
/*   Updated: 2024/10/01 20:53:54 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_list	*list_lines(int fd)
{
	char	*line;
	t_list	*head;
	t_list	*tmp;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
	tmp = ft_lstnew(line);
	if (!tmp)
		return (free(line), NULL);
	head = tmp;
	line = get_next_line(fd);
	while (line)
	{
		tmp->next = ft_lstnew(line);
		if (!tmp->next)
			return (ft_lstclear(&head, free), NULL);
		tmp = tmp->next;
		line = get_next_line(fd);
	}
	return (head);
}

static void	parse_alloc(t_model *model, t_list *line_list)
{
	char	**split;

	model->color = NULL;
	model->rows = ft_lstsize(line_list);
	split = ft_split(line_list->content, ' ');
	if (!split)
		return ;
	model->cols = 0;
	while (split[model->cols])
		model->cols++;
	ft_free_split(split);
	model->height = (float *)malloc(model->cols * model->rows * sizeof(float));
	if (!model->height)
		return ;
	model->vertex = (t_vec4 *)malloc(model->cols * model->rows
			* sizeof(t_vec4));
	if (!model->vertex)
		return ((void)free(model->height));
	model->color = (int *)malloc(model->cols * model->rows * sizeof(int));
	if (!model->color)
		return ((void)free(model->height), free(model->color));
}

static void	parse_map(t_model *model, t_list *line_list)
{
	int		i_h;
	int		i_s;
	char	**split;
	char	*endptr;

	i_h = 0;
	while (line_list)
	{
		i_s = 0;
		split = ft_split(line_list->content, ' ');
		if (!split)
			return ((void)model_destroy(model));
		while (split[i_s])
		{
			model->height[i_h] = ft_strtoll(split[i_s++], &endptr, NULL);
			if (*endptr == ',')
				model->color[i_h++] = ft_strtoll(endptr + 1, NULL, NULL);
			else
				model->color[i_h++] = COLOR_WHITE;
		}
		ft_free_split(split);
		line_list = line_list->next;
	}
}

//should become "normalise"
static void	get_extremum_height(t_model	*model)
{
	int	i;

	model->hmax = INT_MIN;
	i = 0;
	while (i < model->rows * model->cols)
	{
		if (model->height[i] > model->hmax)
			model->hmax = model->height[i];
		i++;
	}
}

void	parse_fdf(t_model *model, char *path)
{
	int		fd;
	t_list	*line_list;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return ;
	line_list = list_lines(fd);
	close(fd);
	if (!line_list)
		return ;
	parse_alloc(model, line_list);
	if (!model->color)
		return ((void)ft_lstclear(&line_list, free));
	parse_map(model, line_list);
	ft_lstclear(&line_list, free);
	get_extremum_height(model);
}
