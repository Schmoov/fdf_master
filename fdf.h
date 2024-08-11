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

t_mat4s	mat_nul(void);
t_mat4s	mat_id(void);
t_mat4s	mat_scale(float factor);
t_mat4s	mat_scale_axis(int axis, float factor);
t_mat4s	mat_rot(int axis, float angle);
t_mat4s	mat_trans(int axis, float mag);
t_mat4s	mat4s_mult(t_mat4s left, t_mat4s right);
t_vec4	mat4s_vec4_mult(t_mat4s mat, t_vec4 v);

//			PARSING
enum e_error {
	E_SUCCESS = 0,
	E_NOMEM,
	E_ACCESS,
	E_EMPTY,
	E_MLXPTR,
	E_MLXWIN,
	E_NEWIMG,
	E_OVERLAY,
};

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

typedef struct s_model {
	int		cols;
	int		rows;
	float	*hmap;
	t_mat4s	mat_obj;
	t_mat4s	mat_cam;
	t_mat4s	mat_proj;
	t_vec4	*vmap;
	enum e_error	err;
}				t_model;
typedef struct s_view {
	void	*mlx;
	void	*win;
	void	*img;
	void	*overlay;
	enum e_error	err;
}				t_view;
typedef struct	s_controller {
	t_model		*model;
	t_view		*view;
}				t_controller;
//			INPUT HANDLING
void	handle_scaling_key(int keycode, t_mat4s *mat_obj);
void	handle_rotation_key(int keycode, t_mat4s *mat_obj);
void	handle_translation_key(int keycode, t_mat4s *mat_cam);
int		key_hook(int keycode, void *param);
//			DRAW
void	draw_line_naive(void *img, t_vec4 start, t_vec4 end);
//			MODEL
void	model_alloc_and_parse(t_model *model, char *path);
void	model_init(t_model *model, char *path);
void	model_update(t_model *model);
void	model_destroy(t_model *model);

//			VIEW
void	view_init(t_view *view, char *path);
void	view_destroy(t_view *view);

#endif
