/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_set_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:53:12 by nle-bret          #+#    #+#             */
/*   Updated: 2016/05/20 17:53:13 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		w_set_texture(t_app *app, char *file_name, char num)
{
	t_texture	texture;
	t_obj		*obj;
	int			height;
	int			width;

	obj = NULL;
	ft_bzero(&texture, sizeof(t_texture));
	if ((obj = (t_obj *)ft_memalloc(sizeof(t_obj))) == NULL)
		ft_putstr_fd("Erreur d'allocation de t_obj\n", 2);
	obj->img = mlx_xpm_file_to_image(app->mlx, file_name,
		&width, &height);
	if (obj->img == NULL)
		return ;
	obj->data = mlx_get_data_addr(obj->img,
		&obj->bpp,
		&obj->sizeline,
		&obj->endian);
	texture.num = num;
	texture.x = 0;
	texture.y = 0;
	texture.width = width;
	texture.height = height;
	texture.obj = obj;
	ft_lstpush_front(&app->lst_texture, &texture, sizeof(t_texture));
}
