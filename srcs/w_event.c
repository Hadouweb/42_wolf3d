/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_event.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:52:47 by nle-bret          #+#    #+#             */
/*   Updated: 2016/05/20 17:52:48 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			w_event_arrow_key(int keycode, t_app *app)
{
	if (keycode == KEY_UP || keycode == KEY_UP2)
	{
		w_player_direction_up(app);
	}
	else if (keycode == KEY_RIGHT || keycode == KEY_RIGHT2)
	{
		w_player_direction_right(app);
	}
	else if (keycode == KEY_LEFT || keycode == KEY_LEFT2)
	{
		w_player_direction_left(app);
	}
	else if (keycode == KEY_DOWN || keycode == KEY_DOWN2)
	{
		w_player_direction_down(app);
	}
	return (1);
}

int			w_event_repeat(int keycode, t_app *app)
{
	w_event_arrow_key(keycode, app);
	return (1);
}

int			w_event(int keycode, t_app *app)
{
	if (keycode == 53)
		exit(1);
	if (keycode == KEY_FLASH && app->speed == MOVE_SPEED)
	{
		app->speed *= 4;
	}
	else if (keycode == KEY_FLASH && app->speed > MOVE_SPEED)
	{
		app->speed = MOVE_SPEED;
	}
	if (app)
		;
	return (1);
}
