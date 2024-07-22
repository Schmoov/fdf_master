#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include "libft/libft.h"

//			LINEAR ALGEBRA
typedef struct	s_vec2{
	double		e[2];
}				t_vec2;

typedef struct	s_vec4{
	double		e[4];
}				t_vec4;

typedef struct	s_mat4s{
	double		val[4][4];
}				t_mat4s;

typedef struct	s_mat24{
	double		val[2][4];
}				t_mat24;
t_vec2	mat24_vec4_mult(t_mat24 mat, t_vec4 v);

//			PARSING
typedef struct s_hmap{
	int		cols;
	int		rows;
	int		*height;
}			t_hmap;
t_hmap	not_a_hmap(void);
t_hmap	parse_hmap(char *path);

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

//			RENDERING
typedef struct s_screen_vertex{
	int		cols;
	int		rows;
	t_vec2	*vertex;
}			t_screen_vertex;

void	hmap_to_screen_vert(t_mat24 mat24, t_hmap *hmap, t_screen_vertex *res);

#endif
