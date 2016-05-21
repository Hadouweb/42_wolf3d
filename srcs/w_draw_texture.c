/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_draw_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 18:20:59 by nle-bret          #+#    #+#             */
/*   Updated: 2016/05/20 18:21:00 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void			w_set_pixel_texture(t_app *app, int x, int y,
	t_texture *texture)
{
	int		index;
	int		d;
	int		texture_y;
	int		index_texture;
	int		wall_height;

	if (y < 0 || y > SIZE_H - 1 || x < 0 || x > SIZE_W - 1)
		return ;
	wall_height = app->current_vline.y_end - app->current_vline.y_start;
	d = y * 256 - SIZE_H * 128 + wall_height * 128;
	texture_y = ((d * texture->height) / wall_height) / 256;
	index_texture = texture_y * texture->obj->sizeline +
		texture->x * texture->obj->bpp / 8;
	index = y * app->obj->sizeline + x * app->obj->bpp / 8;
	app->obj->data[index] = texture->obj->data[index_texture];
	app->obj->data[index + 1] = texture->obj->data[index_texture + 1];
	app->obj->data[index + 2] = texture->obj->data[index_texture + 2];
}

t_texture		*w_preparation_for_texture(t_app *app,
	double perp_wall_dist, char elem)
{
	double		wall_x;
	t_texture	*texture;

	texture = w_get_texture(app, elem);
	if (texture == NULL)
		return (NULL);
	if (app->ray.side == 0)
		wall_x = app->ray.ray_pos_y + perp_wall_dist * app->ray.ray_dir_y;
	else
		wall_x = app->ray.ray_pos_x + perp_wall_dist * app->ray.ray_dir_x;
	wall_x -= floor(wall_x);
	texture->x = (int)(wall_x * (double)texture->width);
	if (app->ray.side == 0 && app->ray.ray_dir_y > 0)
		texture->x = texture->width - texture->x - 1;
	if (app->ray.side == 1 && app->ray.ray_dir_x < 0)
		texture->x = texture->width - texture->x - 1;
	return (texture);
}

void			w_draw_vline_with_texture(t_app *app, int x, t_texture *texture)
{
	int		y;
	int		max;

	y = app->current_vline.y_start;
	max = app->current_vline.y_end;
	while (y < max)
	{
		w_set_pixel_texture(app, x, y, texture);
		y++;
	}
}
