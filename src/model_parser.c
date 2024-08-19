#include "fdf.h"

static t_list	*list_lines(int fd, enum e_error *err)
{
	char	*line;
	t_list	*head;
	t_list	*tmp;

	line = get_next_line(fd);
	if (!line)
		return (*err = E_EMPTY, NULL);
	tmp = ft_lstnew(line);
	if (!tmp)
		return (free(line), *err = E_NOMEM, NULL);
	head = tmp;
	line = get_next_line(fd);
	while (line)
	{
		tmp->next = ft_lstnew(line);
		if (!tmp->next)
			return (ft_lstclear(&head, free), *err = E_NOMEM, NULL);
		tmp = tmp->next;
		line = get_next_line(fd);
	}
	return (head);
}

static void	alloc_model(t_model *model, t_list *line_list)
{
	char	**split;

	model->rows = ft_lstsize(line_list);
	split = ft_split(line_list->content, ' ');
	if (!split)
		return ((void)(model->err = E_NOMEM));
	model->cols = 0;
	while (split[model->cols])
		model->cols++;
	ft_free_split(split);
	model->hmap = (float *)malloc(model->cols * model->rows * sizeof(float));
	if (!model->hmap)
		return ((void)(model->err = E_NOMEM));
	model->vmap = (t_vec4 *)malloc(model->cols * model->rows * sizeof(t_vec4));
	if (!model->vmap)
		return (free(model->hmap), (void)(model->err = E_NOMEM));
}

static void	fill_hmap(t_model *model, t_list *line_list)
{
	int		i_hmap;
	int		i_split;
	char	**split;

	i_hmap = 0;
	while (line_list)
	{
		i_split = 0;
		split = ft_split(line_list->content, ' ');
		if (!split)
		{
			free(model->hmap);
			free(model->vmap);
			model->err = E_NOMEM;
			return ;
		}
		while (split[i_split])
			model->hmap[i_hmap++] = ft_atoi(split[i_split++]);
		ft_free_split(split);
		line_list = line_list->next;
	}
}

void	model_alloc_and_parse(t_model *model, char *path)
{
	int		fd;
	t_list	*line_list;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return ((void)(model->err = E_ACCESS));
	line_list = list_lines(fd, &(model->err));
	close(fd);
	if (model->err)
		return ;
	alloc_model(model, line_list);
	if (model->err)
		return (ft_lstclear(&line_list, free));
	fill_hmap(model, line_list);
	ft_lstclear(&line_list, free);
	return ;
}
