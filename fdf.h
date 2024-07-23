#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include "libft/libft.h"

//			LINEAR ALGEBRA
typedef struct	s_vec2{
	float		e[2];
}				t_vec2;

typedef struct	s_vec4{
	float		e[4];
}				t_vec4;

typedef struct	s_mat4s{
	float		val[4][4];
}				t_mat4s;

typedef struct	s_mat24{
	float		val[2][4];
}				t_mat24;
t_mat4s	mat_nul(void);
t_mat4s	mat_id(void);
t_mat4s	mat_rot(int axis, float angle);
t_mat4s	mat4s_mult(t_mat4s left, t_mat4s right);
t_vec4	mat4s_vec4_mult(t_mat4s mat, t_vec4 v);

//			PARSING
typedef struct s_hmap{
	int		cols;
	int		rows;
	int		*height;
}			t_hmap;
t_hmap	not_a_hmap(void);
t_hmap	parse_hmap(char *path);

//			MLX
# define WIN_WIDTH		640
# define WIN_HEIGHT		480

# define KEY_LEFT		65361
# define KEY_DOWN		65364
# define KEY_UP			65362
# define KEY_RIGHT		65363
# define KEY_ESC		65307

# define COLOR_WHITE	0xffffff
typedef struct s_vmap{
	int		cols;
	int		rows;
	t_vec4	*val;
}			t_vmap;

typedef struct s_mlx{
	void	*ptr;
	void	*win;
	t_hmap	hmap;
	t_vmap	vmap;
}			t_mlx;

//			RENDERING
void	draw_segment(t_mlx mlx, t_vec4 start, t_vec4 end);
void	draw_moire(t_mlx mlx, float nb_radius);
void	draw_fdf(t_mlx mlx);
t_vmap	hmap_to_vmap(t_hmap hmap, t_mat4s mat);

#endif
