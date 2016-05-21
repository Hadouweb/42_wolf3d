/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_player_direction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:52:56 by nle-bret          #+#    #+#             */
/*   Updated: 2016/05/20 17:52:57 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		w_player_direction_up(t_app *app)
{
	double	pos_x;
	double	pos_y;
	int		x;

	pos_x = app->player.pos_x;
	pos_y = app->player.pos_y;
	x = (int)(pos_x + app->player.dir_x * app->speed);
	if (app->map.tab[x][(int)pos_y] == 0)
		app->player.pos_x += app->player.dir_x * app->speed;
	if (app->map.tab[(int)pos_x][(int)(pos_y +
		app->player.dir_y * app->speed)] == 0)
		app->player.pos_y += app->player.dir_y * app->speed;
}

void		w_player_direction_right(t_app *app)
{
	double	old_dir_x;
	double	old_plane_x;
	double	pos_x;
	double	pos_y;

	pos_x = app->player.pos_x;
	pos_y = app->player.pos_y;
	old_dir_x = app->player.dir_x;
	app->player.dir_x = app->player.dir_x * cos(-ROT_SPEED) -
		app->player.dir_y * sin(-ROT_SPEED);
	app->player.dir_y = old_dir_x * sin(-ROT_SPEED) +
		app->player.dir_y * cos(-ROT_SPEED);
	old_plane_x = app->player.cam_plane_x;
	app->player.cam_plane_x = app->player.cam_plane_x * cos(ROT_SPEED) -
		app->player.cam_plane_y * sin(-ROT_SPEED);
	app->player.cam_plane_y = old_plane_x * sin(-ROT_SPEED) +
		app->player.cam_plane_y * cos(-ROT_SPEED);
}

void		w_player_direction_left(t_app *app)
{
	double	old_dir_x;
	double	old_plane_x;
	double	pos_x;
	double	pos_y;

	pos_x = app->player.pos_x;
	pos_y = app->player.pos_y;
	old_dir_x = app->player.dir_x;
	app->player.dir_x = app->player.dir_x * cos(ROT_SPEED) -
		app->player.dir_y * sin(ROT_SPEED);
	app->player.dir_y = old_dir_x * sin(ROT_SPEED) +
		app->player.dir_y * cos(ROT_SPEED);
	old_plane_x = app->player.cam_plane_x;
	app->player.cam_plane_x = app->player.cam_plane_x * cos(ROT_SPEED) -
		app->player.cam_plane_y * sin(ROT_SPEED);
	app->player.cam_plane_y = old_plane_x * sin(ROT_SPEED) +
		app->player.cam_plane_y * cos(ROT_SPEED);
}

void		w_player_direction_down(t_app *app)
{
	double	pos_x;
	double	pos_y;

	pos_x = app->player.pos_x;
	pos_y = app->player.pos_y;
	if (app->map.tab[(int)(pos_x - app->player.dir_x *
		app->speed)][(int)pos_y] == 0)
		app->player.pos_x -= app->player.dir_x * app->speed;
	if (app->map.tab[(int)pos_x][(int)(pos_y -
		app->player.dir_y * app->speed)] == 0)
		app->player.pos_y -= app->player.dir_y * app->speed;
}
