#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include "libft/libft.h"

//			PARSING
typedef struct s_hmap{
	int		col;
	int		row;
	int		*height;
}			t_hmap;
t_hmap	not_a_hmap(void);
t_hmap	parse_hmap(char *path)

//			LINEAR ALGEBRA
typedef struct	s_vec2{
	double		e1;
	double		e2;
}				t_vec2;

typedef struct	s_vec4{
	double		e1;
	double		e2;
	double		e3;
	double		e4;
}				t_vec4;

typedef struct	s_mat4s{
	double		val[4][4];
}				t_mat4s;

//			MLX
# define KEY_LEFT		65361
# define KEY_DOWN		65364
# define KEY_UP			65362
# define KEY_RIGHT		65363

# define COLOR_WHITE	0xffffff
typedef struct s_mlx{
	void	*ptr;
	void	*win;
}			t_mlx;


#endif
