#include "fdf.h"

int	main(int argc, char **argv)
{
	t_presenter	pres;
	t_view view;
	t_model model;

	if (argc != 2)
		return (write(2, "Fdf expects a single file\n", 26));
	pres.view = &view;
	pres.model = &model;
	presenter_init(&pres, argv[1]);
}
