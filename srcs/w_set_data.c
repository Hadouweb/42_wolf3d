/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_set_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:53:02 by nle-bret          #+#    #+#             */
/*   Updated: 2016/05/20 17:53:03 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	w_set_view(t_app *app)
{
	app->player.dir_x = -1;
	app->player.dir_y = 0;
	app->player.cam_plane_x = 0;
	app->player.cam_plane_y = 0.60;
	app->fps.time = 0;
	app->fps.old_time = 0;
	app->fps.delay = 0;
	app->fps.str_fps = ft_strdup("0");
}

void	w_set_one_dim(int **tab, t_list *l)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char*)l->content;
	while (i < l->content_size)
	{
		(*tab)[i] = (int)str[i] - '0';
		i++;
	}
	(*tab)[i] = '\0';
}

int		**w_set_tab(t_list *l, int size)
{
	int		**tab;
	int		i;

	if ((tab = (int **)ft_memalloc(size * sizeof(int *) + 1)) == NULL)
		return (NULL);
	i = 0;
	while (i < size && l)
	{
		if ((tab[i] = (int *)ft_memalloc(l->content_size *
			sizeof(int)) + 1) == NULL)
			return (NULL);
		w_set_one_dim(&tab[i], l);
		l = l->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
