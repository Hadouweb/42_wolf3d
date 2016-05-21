/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_dda_algorithm.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:52:23 by nle-bret          #+#    #+#             */
/*   Updated: 2016/05/20 17:52:25 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		w_calcul_delta_dist(t_app *app)
{
	app->ray.delta_dist_x = sqrt(1 + (app->ray.ray_dir_y * app->ray.ray_dir_y) /
		(app->ray.ray_dir_x * app->ray.ray_dir_x));
	app->ray.delta_dist_y = sqrt(1 + (app->ray.ray_dir_x * app->ray.ray_dir_x) /
		(app->ray.ray_dir_y * app->ray.ray_dir_y));
}

void		w_preparation_for_dda_algorithm(t_app *app)
{
	w_calcul_delta_dist(app);
	if (app->ray.ray_dir_x < 0)
	{
		app->ray.step_x = -1;
		app->ray.side_dist_x = (app->ray.ray_pos_x - app->ray.map_x);
	}
	else
	{
		app->ray.step_x = 1;
		app->ray.side_dist_x = (app->ray.map_x + 1.0 - app->ray.ray_pos_x);
	}
	if (app->ray.ray_dir_y < 0)
	{
		app->ray.step_y = -1;
		app->ray.side_dist_y = (app->ray.ray_pos_y - app->ray.map_y);
	}
	else
	{
		app->ray.step_y = 1;
		app->ray.side_dist_y = (app->ray.map_y + 1.0 - app->ray.ray_pos_y);
	}
	app->ray.side_dist_x *= app->ray.delta_dist_x;
	app->ray.side_dist_y *= app->ray.delta_dist_y;
}

void		w_move_raycast(t_app *app)
{
	if (app->ray.side_dist_x < app->ray.side_dist_y)
	{
		app->ray.side_dist_x += app->ray.delta_dist_x;
		app->ray.map_x += app->ray.step_x;
		app->ray.side = 0;
	}
	else
	{
		app->ray.side_dist_y += app->ray.delta_dist_y;
		app->ray.map_y += app->ray.step_y;
		app->ray.side = 1;
	}
}

char		w_dda_algorithm(t_app *app)
{
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		w_move_raycast(app);
		if (app->ray.map_x < app->map.x && app->ray.map_y < app->map.y &&
			app->ray.map_x >= 0 && app->ray.map_y >= 0)
		{
			if (app->map.tab[app->ray.map_x][app->ray.map_y] > 0)
				return (app->map.tab[app->ray.map_x][app->ray.map_y] + '0');
		}
		else
			hit = 1;
	}
	return ('0');
}
