#include "libft/libft.h"

typedef struct s_hmap{
	int		col;
	int		row;
	int		*height;
}			t_hmap;

t_hmap	not_a_hmap(void)
{
	return ((t_hmap){-1, -1, NULL});
}

t_list	*list_lines(int fd)
{
	int		fd;
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
			return (ft_lstclear(head, free), NULL);
		tmp = tmp->next;
		line = get_next_line(fd);
	}
	return (head);
}

t_hmap	init_hmap(t_list *line_list)
{
	t_hmap	res;
	char	**splited;
	int		col_count;

	t_hmap.row = ft_lstsize(line_list);
	splitted = ft_split(line_list->content, ' ');
	if (!splitted)
		return (not_a_hmap());
	i = 0;
	while (splitted[col_count])
		col_count++;
	free_split(splitted);
	t_hmap.col = col_count;
	t_hmap.height = (int *)malloc(t_hmap.col * t_hmap.row * sizeof(int));
	if (!t_hmap.height)
		return (not_a_hmap());
	return (t_hmap);
}

t_hmap	build_hmap(t_list *line_list)
{
	int		i_map;
	int		i_split;
	char	**splitted;
	t_hmap	map;

	map = init_hmap(line_list);
	if (!map.height)
		return (not_a_hmap());
	i_map = 0;
	while (line_list)
	{
		i_split = 0;
		splitted = ft_split(line_list->content, ' ');
		if (!splitted)
			return (free(hmap.height), not_a_hmap());
		while (splitted[i_split])
			map.height[i_map++] = ft_atoi(splitted[i_split++]);
		free_split(splitted);
		line_list = line_list->next;
	}
	return (map);
}

t_hmap	parse_hmap(char *path)
{
	int		fd;
	t_list	*line_list;
	t_hmap	map;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (not_a_hmap());
	line_list = list_lines(fd);
	if (!line_list)
		return (not_a_hmap());
	map = build_hmap(line_list);
	ft_lstclear(line_list, free);
	return (map);
}
