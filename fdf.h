/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parden <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 20:06:40 by parden            #+#    #+#             */
/*   Updated: 2024/10/12 20:52:55 by parden           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <stdio.h>
# include <math.h>
# include "libft/libft.h"

//			LINEAR ALGEBRA
typedef struct s_vec4{
	float		e[4];
}				t_vec4;

typedef struct s_mat4s{
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

//			MLX
# define WIN_WIDTH		1600
# define WIN_HEIGHT		900
# define COLOR_WHITE	0xffffff
# define KEY_ESC		65307
# define KEY_PLUS		65451
# define KEY_MINUS		65453
# define KEY_MULT		65450
# define KEY_DIV		65455
# define KEY_LEFT		65361
# define KEY_DOWN		65364
# define KEY_UP			65362
# define KEY_RIGHT		65363

typedef struct s_model {
	int		cols;
	int		rows;
	int		hmax;
	t_mat4s	mat_obj;
	t_mat4s	mat_cam;
	float	*height;
	int		*color;
	t_vec4	*vertex;
}				t_model;

typedef struct s_view {
	void	*mlx;
	void	*win;
	void	*img;
}				t_view;

typedef struct s_presenter {
	t_model		*model;
	t_view		*view;
}				t_presenter;

//		UTILS
int		color_mid(int c1, int c2, float b);
t_vec4	vec_mid(t_vec4 v1, t_vec4 v2, float b);
bool	is_offcam(t_vec4 v);

//			INPUT HANDLING
void	handle_scaling_key(int keycode, t_mat4s *mat_obj);
void	handle_rotation_key(int keycode, t_mat4s *mat_obj);
void	handle_translation_key(int keycode, t_mat4s *mat_cam);
int		key_hook(int keycode, void *param);
int		mouse_hook(int button, int x, int y, void *param);
int		close_with_cross(void *param);

//			MODEL
void	parse_fdf(t_model *model, int fd);
void	model_init(t_model *model, int fd);
void	model_vertex_shader(t_model *m);
void	model_destroy(t_model *model);
void	model_make_side(t_model *m);
void	model_make_topdown(t_model *m);
void	model_make_iso(t_model *m);

//			VIEW
void	view_init(t_view *view, char *path);
void	view_update(t_presenter *pres);
void	draw_img(t_presenter *pres);
void	view_destroy(t_view *view);

//			PRESENTER
void	presenter_init(t_presenter *pres, char *path, int fd);
void	presenter_update(t_presenter *pres);
void	presenter_destroy(t_presenter *pres);
#endif
