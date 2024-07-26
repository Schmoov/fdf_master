#include "fdf.h"

t_hmap	not_a_hmap(void)
{
	return ((t_hmap){-1, -1, NULL});
}

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

static t_hmap	init_hmap(t_list *line_list)
{
	t_hmap	map;
	char	**split;

	map.rows = ft_lstsize(line_list);
	split = ft_split(line_list->content, ' ');
	if (!split)
		return (not_a_hmap());
	map.cols = 0 ;
	while (split[map.cols])
		map.cols++;
	ft_free_split(split);
	map.height = (float *)malloc(map.cols * map.rows * sizeof(int));
	if (!map.height)
		return (not_a_hmap());
	return (map);
}

void	fill_hmap(t_list *line_list, t_hmap *map)
{
	int		i_map;
	int		i_split;
	char	**split;

	i_map = 0;
	while (line_list)
	{
		i_split = 0;
		split = ft_split(line_list->content, ' ');
		if (!split)
		{
			free(map->height);
			*map = not_a_hmap();
			return ;
		}
		while (split[i_split])
			map->height[i_map++] = ft_atoi(split[i_split++]);
		ft_free_split(split);
		line_list = line_list->next;
	}
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
	close(fd);
	if (!line_list)
		return (not_a_hmap());
	map = init_hmap(line_list);
	if (!map.height)
		return (ft_lstclear(&line_list, free), not_a_hmap());
	fill_hmap(line_list, &map);
	ft_lstclear(&line_list, free);
	return (map);
}

/*
int main()
{
	t_hmap map = parse_hmap("maps/42.fdf");
	for (int i = 0; i < map.rows; i++)
	{
		for (int j = 0; j < map.cols; j++)
		{
			printf("%f ", map.height[j + i*map.cols]);
		}
	printf("\n");
	}
}
*/
