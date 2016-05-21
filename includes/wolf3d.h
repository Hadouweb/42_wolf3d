#ifndef WOLF3D_H
# define WOLF3D_H

#include "mlx.h"
#include "libft.h"
#include <fcntl.h>
#include <math.h>
#include <time.h>

# define SIZE_W 960
# define SIZE_H 540

# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125

# define KEY_UP2 13
# define KEY_LEFT2 0
# define KEY_RIGHT2 2
# define KEY_DOWN2 1

# define KEY_FLASH 257

# define KEY_JUMP 49

# define MOVE_SPEED 0.2
# define ROT_SPEED 0.2

typedef struct		s_obj
{
	void			*img;
	int				bpp;
	int				sizeline;
	int				endian;
	char			*data;
}					t_obj;

typedef struct 		s_texture
{
	t_obj			*obj;
	int 			width;
	int 			height;
	int 			x;
	int 			y;
	char 			num;
}					t_texture;

typedef struct 		s_vector
{
	int				x;
	int				y;
}					t_vector;

typedef struct		s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	unsigned char	a;
}					t_color;

typedef struct 		s_vline
{
	int				x;
	int				y_start;
	int				y_end;
	t_color			color;
}					t_vline;

typedef struct 		s_map
{
	int				x;
	int				y;
	int				**tab;
}					t_map;

typedef struct  	s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			cam_plane_x;
	double			cam_plane_y;
	double			camera_x;
}					t_player;

typedef struct  	s_ray
{
	double			ray_pos_x;
	double			ray_pos_y;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				side;
}					t_ray;

typedef struct 		s_fps
{
	double			time;
	double			old_time;
	double			frame_time;
	int 			delay;
	char			*str_fps;
}					t_fps;

typedef struct  	s_app
{
	void			*mlx;
	void			*win;
	t_obj			*obj;
	t_map			map;
	int				end;
	t_vline			current_vline;
	int				up;
	t_player		player;
	t_ray			ray;
	t_fps			fps;
	t_list			*lst_texture;
	double 			speed;
}					t_app;

int			w_event_arrow_key(int keycode, t_app *app);
int			w_event_repeat(int keycode, t_app *app);
int			w_test(t_app *app);
int			w_event(int keycode, t_app *app);

void		w_draw(t_app *app);
void		w_draw_vline(t_app *app, int x);
t_vline		w_get_vline(int x, int y_start, int y_end, t_color color);
void		w_set_pixel(t_obj *obj, int x, int y, t_color color);
t_color		w_get_color(unsigned char r, unsigned char g,
	unsigned char b, unsigned char a);
t_obj		*w_init_obj_info(void *mlx, int width, int height);

void		w_del_node(void *content, size_t content_size);
t_color		w_get_cardinal_color(t_app *app);
void		w_print_fps(t_app *app) ;

void		w_read_map(t_app *app, char *file);
void		w_set_texture(t_app *app, char *file_name, char num);
void		w_set_one_dim(int **tab, t_list *l);
int			**w_set_tab(t_list *l, int size);
void		w_set_directive(t_app *app, char *str, int i);
void		w_set_view(t_app *app);

void		w_print_error_exit(char *str, char *error);
void		w_check_directive(t_app *app, char *str);
int			w_check_line(t_app *app, char *str);
int			w_check_position(t_app *app, char *str, char d);

void		w_debug_map(t_app *app);
void		w_debug_player(t_app *app); 
void		w_debug_ray(t_app *app);

void		w_preparation_for_dda_algorithm(t_app *app);
char		w_dda_algorithm(t_app *app);
void		w_print_lst_texture(void *data);
void		w_current_position_of_ray(t_app *app, int x);
void		w_preparation_for_vline(t_app *app, int x, char elem);
void		w_print_fps(t_app *app);
void		w_draw_vline(t_app *app, int x);
int			w_draw_view(t_app *app);

void		w_player_direction_up(t_app *app);
void		w_player_direction_right(t_app *app);
void		w_player_direction_left(t_app *app);
void		w_player_direction_down(t_app *app);

void			w_set_pixel_texture(t_app *ap, int x, int y,
	t_texture *texture);
t_texture		*w_preparation_for_texture(t_app *app,
	double perp_wall_dist, char elem);
void			w_draw_vline_with_texture(t_app *app, int x, t_texture *texture);

t_color		w_get_color(unsigned char r, unsigned char g,
	unsigned char b, unsigned char a);
t_texture		*w_get_texture(t_app *app, char elem);
t_color			w_get_cardinal_color(t_app *app);

void			w_draw_color_or_texture(t_app *app, double perp_wall_dist,
	int x, char elem);

#endif