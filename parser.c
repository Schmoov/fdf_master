#include "libft/include/libft.h"

typedef struct {
	int		len_line;
	int		nb_line;
	t_list	*head;
}			t_map;

t_map	parse_map(char *path)
{
	int		fd;
	t_map	res;
	char	*line;

	res.nb_line = 0;
	res.head = NULL;
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);

	char	**split = ft_split(line, ' ');
	int	i = 0;
	while (split)
	while (line)
	{

}
