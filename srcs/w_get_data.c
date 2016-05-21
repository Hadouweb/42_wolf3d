/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_get_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 18:38:55 by nle-bret          #+#    #+#             */
/*   Updated: 2016/05/20 18:38:56 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

t_color			w_get_color(unsigned char r, unsigned char g,
	unsigned char b, unsigned char a)
{
	t_color		color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return (color);
}

t_texture		*w_get_texture(t_app *app, char elem)
{
	t_list		*l;
	t_texture	*texture;

	l = app->lst_texture;
	while (l)
	{
		texture = (t_texture*)l->content;
		if (elem == texture->num)
			return (texture);
		l = l->next;
	}
	return (NULL);
}

t_color			w_get_cardinal_color(t_app *app)
{
	t_color		color;

	if (app->ray.side == 0 && app->ray.ray_dir_x < 0)
		color = w_get_color(0, 255, 0, 0);
	else if (app->ray.side == 0 && app->ray.ray_dir_x > 0)
		color = w_get_color(255, 0, 0, 0);
	else if (app->ray.side == 1 && app->ray.ray_dir_y < 0)
		color = w_get_color(0, 0, 255, 0);
	else if (app->ray.side == 1 && app->ray.ray_dir_y > 0)
		color = w_get_color(255, 255, 0, 0);
	else
		color = w_get_color(0, 255, 0, 0);
	return (color);
}

t_vline			w_get_vline(int x, int y_start, int y_end, t_color color)
{
	t_vline		vline;

	vline.x = x;
	vline.y_start = y_start;
	vline.y_end = y_end;
	vline.color = color;
	return (vline);
}
