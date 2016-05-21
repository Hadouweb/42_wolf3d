/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_util.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:53:16 by nle-bret          #+#    #+#             */
/*   Updated: 2016/05/20 17:53:17 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		w_del_node(void *content, size_t content_size)
{
	ft_strdel((char**)&content);
	content_size = 0;
}

void		w_print_fps(t_app *app)
{
	app->fps.old_time = app->fps.time;
	app->fps.time = clock();
	app->fps.frame_time = (app->fps.time - app->fps.old_time) / 1000.0;
	if (app->fps.delay > 10000)
	{
		ft_strdel(&app->fps.str_fps);
		app->fps.str_fps = ft_itoa((int)(1.0 / app->fps.frame_time));
		app->fps.delay = 0;
	}
	app->fps.delay++;
}
