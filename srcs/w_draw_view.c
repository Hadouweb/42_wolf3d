/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_draw_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:52:37 by nle-bret          #+#    #+#             */
/*   Updated: 2016/05/20 17:52:38 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			w_current_position_of_ray(t_app *app, int x)
{
	app->player.camera_x = 2 * x / (double)SIZE_W - 1;
	app->ray.ray_pos_x = app->player.pos_x;
	app->ray.ray_pos_y = app->player.pos_y;
	app->ray.ray_dir_x = app->player.dir_x + app->player.cam_plane_x *
		app->player.camera_x;
	app->ray.ray_dir_y = app->player.dir_y + app->player.cam_plane_y *
		app->player.camera_x;
	app->ray.map_x = (int)app->ray.ray_pos_x;
	app->ray.map_y = (int)app->ray.ray_pos_y;
}

void			w_draw_color_or_texture(t_app *app, double perp_wall_dist,
	int x, char elem)
{
	t_texture	*texture;

	texture = NULL;
	if (elem > '1')
	{
		texture = w_preparation_for_texture(app, perp_wall_dist, elem);
		if (texture != NULL)
		{
			w_draw_vline_with_texture(app, x, texture);
			return ;
		}
	}
	w_draw_vline(app, x);
}

void			w_draw_vline(t_app *app, int x)
{
	int		y;
	int		max;
	int		height;

	y = app->current_vline.y_start;
	max = app->current_vline.y_end;
	height = max - y;
	while (y < max)
	{
		w_set_pixel(app->obj, x, y, app->current_vline.color);
		y++;
	}
}

void			w_draw_floor(t_app *app, int x)
{
	int		max;
	int		y;

	max = SIZE_H / 2;
	y = SIZE_H;
	while (y > max)
	{
		w_set_pixel(app->obj, x, y, w_get_color(100, 100, 100, 0));
		y--;
	}
}

int				w_draw_view(t_app *app)
{
	int		x;
	char	elem;

	x = 0;
	while (x < SIZE_W)
	{
		w_draw_floor(app, x);
		w_current_position_of_ray(app, x);
		w_preparation_for_dda_algorithm(app);
		elem = w_dda_algorithm(app);
		w_preparation_for_vline(app, x, elem);
		w_print_fps(app);
		x++;
	}
	w_draw(app);
	return (1);
}
