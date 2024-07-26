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
t_mat4s	mat_scale(float factor);
t_mat4s	mat_scale_axis(int axis, float factor);
t_mat4s	mat_rot(int axis, float angle);
t_mat4s	mat_trans(int axis, float mag);
t_mat4s	mat4s_mult(t_mat4s left, t_mat4s right);
t_vec4	mat4s_vec4_mult(t_mat4s mat, t_vec4 v);

//			PARSING
typedef struct s_hmap{
	int		cols;
	int		rows;
	float	*height;
}			t_hmap;
t_hmap	not_a_hmap(void);
t_hmap	parse_hmap(char *path);

//			MLX
# define WIN_WIDTH		1600
# define WIN_HEIGHT		900

# define KEY_ESC		65307
# define KEY_PLUS		65451
# define KEY_MINUS		65453
# define KEY_MULT		65450
# define KEY_DIV		65455
# define KEY_LEFT		65361
# define KEY_DOWN		65364
# define KEY_UP			65362
# define KEY_RIGHT		65363

# define COLOR_WHITE	0xffffff
typedef struct s_vmap {
	int		cols;
	int		rows;
	t_vec4	*val;
}			t_vmap;

typedef struct s_mlx {
	void	*ptr;
	void	*win;
}			t_mlx;

typedef struct s_state {
	t_mlx	mlx;
	t_hmap	hmap;
	t_mat4s	mat;
	t_vmap	vmap;
	void	*img;
	void	*overlay;
}				t_state;
//			INPUT HANDLING
int	key_hook(int keycode, void *param);
//			RENDERING
t_vmap	init_vmap(t_hmap hmap);
void	update_vmap(t_state st);
void	draw_segment(t_state st, t_vec4 start, t_vec4 end);
void	draw_moire(t_mlx mlx, float nb_radius);
void	draw_fdf(t_state st);

#endif
