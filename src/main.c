#include "fdf.h"

int	main(int argc, char **argv)
{
	t_presenter	pres;

	if (argc > 2)
		return (write(2, "Fdf expects a single file\n", 26));
	if (argc == 1)
		return (write(2, "Reading from stdin not yet implemented\n", 39));
	presenter_init(&pres, argv[1]);
}
