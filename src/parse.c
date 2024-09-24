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

	model->vertex = NULL;
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
	model->vertex = (t_vec4 *)malloc(model->cols * model->rows * sizeof(t_vec4));
	if (!model->vertex)
		return ((void)free(model->height));
}

static void	parse_height(t_model *model, t_list *line_list)
{
	int		i_height;
	int		i_split;
	char	**split;

	i_height = 0;
	while (line_list)
	{
		i_split = 0;
		split = ft_split(line_list->content, ' ');
		if (!split)
		{
			free(model->height);
			free(model->vertex);
			return ;
		}
		while (split[i_split])
			model->height[i_height++] = ft_atoi(split[i_split++]);
		ft_free_split(split);
		line_list = line_list->next;
	}
}

static void get_extremum_height(t_model	*model)
{
	int	i;

	model->hmax = INT_MIN;
	model->hmin = INT_MAX;
	i = 0;
	while (i < model->rows * model->cols)
	{
		if (model->height[i] > model->hmax)
			model->hmax = model->height[i];
		if (model->height[i] < model->hmin)
			model->hmin = model->height[i];
		i++;
	}
	ft_printf("%d %d\n", model->hmax, model->hmin);
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
	if (!model.vertex)
		return ((void)ft_lstclear(&line_list, free));
	parse_height(model, line_list);
	ft_lstclear(&line_list, free);
	get_extremum_height(model);
}
