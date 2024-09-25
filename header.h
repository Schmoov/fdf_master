void	model_vertex_shader(t_model *m);
void	model_init(t_model *model, char *path);
void	model_destroy(t_model *model);




void	presenter_update(t_model *model, t_view *view);
void	presenter_init(t_presenter *pres, char *path);
void	presenter_destroy(t_model *model, t_view *view);




void	view_init(t_view *view, char *name);
void view_clear_img(t_view *view);
void	view_update(t_view *view, t_vec4 *vmap, int cols, int rows);
void	view_destroy(t_view *view);
void	view_draw_img(t_view *view, t_vec4 *vmap, int cols, int rows);
