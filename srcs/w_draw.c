/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_draw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:52:32 by nle-bret          #+#    #+#             */
/*   Updated: 2016/05/20 17:52:34 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			w_draw(t_app *app)
{
	mlx_clear_window(app->mlx, app->win);
	mlx_put_image_to_window(app->mlx, app->win, app->obj->img, 0, 0);
	mlx_string_put(app->mlx, app->win, 20, 10, 0xFFFFFF, "FPS : ");
	mlx_string_put(app->mlx, app->win, 80, 10, 0xFFFFFF, app->fps.str_fps);
	ft_bzero(app->obj->data, SIZE_W * SIZE_H * 4);
}

void			w_set_pixel(t_obj *obj, int x, int y, t_color color)
{
	int		index;

	if (y < 0 || y > SIZE_H - 1 || x < 0 || x > SIZE_W - 1)
		return ;
	index = y * obj->sizeline + x * obj->bpp / 8;
	obj->data[index] = color.r;
	obj->data[index + 1] = color.g;
	obj->data[index + 2] = color.b;
}

t_obj			*w_init_obj_info(void *mlx, int width, int height)
{
	t_obj	*obj;

	if ((obj = (t_obj *)ft_memalloc(sizeof(t_obj))) == NULL)
		ft_putstr_fd("Erreur d'allocation de t_obj\n", 2);
	obj->img = mlx_new_image(mlx, width, height);
	obj->data = mlx_get_data_addr(obj->img,
		&obj->bpp,
		&obj->sizeline,
		&obj->endian);
	ft_bzero(obj->data, width * height * 4);
	return (obj);
}

static double	w_correction_fisheye_effect(t_app *app)
{
	double	perp_wall_dist;

	if (app->ray.side == 0)
		perp_wall_dist = (app->ray.map_x - app->ray.ray_pos_x +
			(1 - app->ray.step_x) / 2) / app->ray.ray_dir_x;
	else
		perp_wall_dist = (app->ray.map_y - app->ray.ray_pos_y +
			(1 - app->ray.step_y) / 2) / app->ray.ray_dir_y;
	return (perp_wall_dist);
}

void			w_preparation_for_vline(t_app *app, int x, char elem)
{
	int			wall_height;
	int			down_wall;
	int			top_wall;
	double		perp_wall_dist;

	perp_wall_dist = w_correction_fisheye_effect(app);
	wall_height = (int)(SIZE_H / perp_wall_dist);
	down_wall = -wall_height / 2 + SIZE_H / 2;
	if (down_wall < 0)
		down_wall = 0;
	top_wall = wall_height / 2 + SIZE_H / 2;
	if (top_wall >= SIZE_H)
		top_wall = SIZE_H - 1;
	app->current_vline = w_get_vline(x, down_wall, top_wall,
		w_get_cardinal_color(app));
	w_draw_color_or_texture(app, perp_wall_dist, x, elem);
}
