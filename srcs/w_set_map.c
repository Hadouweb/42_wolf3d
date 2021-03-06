/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_set_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:53:07 by nle-bret          #+#    #+#             */
/*   Updated: 2016/05/20 17:53:08 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		w_set_directive(t_app *app, char *str, int i)
{
	if (str[i] && str[1] == '0')
		app->player.pos_x = w_check_position(app, &str[i], 'x');
	else if (str[i] && str[1] == '1')
		app->player.pos_y = w_check_position(app, &str[i], 'y');
	else if (str[i] && str[1] >= '2' && str[1] <= '9')
		w_set_texture(app, &str[i], str[1]);
}

void		w_set_map(t_app *app, t_list **lst)
{
	app->map.tab = w_set_tab(*lst, app->map.y);
	if ((app->player.pos_x == -1 || app->player.pos_y == -1) ||
		app->map.tab[(int)app->player.pos_x][(int)app->player.pos_y] != 0)
	{
		ft_putstr_fd("Mauvaise position de la camera\n", 2);
		exit(1);
	}
	w_clear_list(lst);
}

void		w_set_map_or_directive(t_app *app, t_list **lst,
	char *line)
{
	int		size;
	char	*new_line;

	size = 0;
	new_line = NULL;
	if ((line[0] >= '0' && line[0] <= '9') || line[0] == '!')
	{
		if (w_check_line(app, line) == 0)
		{
			new_line = ft_del_char(line, ' ');
			if (new_line != NULL && new_line[0])
			{
				size = ft_strlen(new_line) + 2;
				if (new_line[size - 3] == '0')
					new_line[size - 3] = '1';
				if (new_line[0] == '0')
					new_line[0] = '1';
				ft_lstpush_back(lst, new_line, size);
				ft_strdel(&new_line);
				app->map.y++;
				if (size > app->map.x)
					app->map.x = size - 2;
			}
		}
	}
}

void		w_adjust_limit_map(t_app *app, t_list **lst)
{
	t_list	*l;
	char	*str;
	int		i;

	l = *lst;
	str = (char*)l->content;
	i = 0;
	while (str[i])
	{
		if (str[i] == '0')
			str[i] = '1';
		i++;
	}
	i = 0;
	while (l->next && ++i < app->map.y)
		l = l->next;
	str = l->content;
	i = 0;
	while (str[i])
	{
		if (str[i] == '0')
			str[i] = '1';
		i++;
	}
}

void		w_read_map(t_app *app, char *file)
{
	int		fd;
	char	*line;
	t_list	*lst;

	fd = open(file, O_RDONLY);
	lst = NULL;
	app->player.pos_x = -1;
	app->player.pos_y = -1;
	if (fd == -1)
		w_print_error_exit("Erreur d'ouverture du fichier : ", file);
	while (get_next_line(fd, &line) > 0)
	{
		if (line[0])
			w_set_map_or_directive(app, &lst, line);
		ft_strdel(&line);
	}
	if (app->map.y == 0)
	{
		ft_putstr_fd("Mauvais format de fichier\n", 2);
		exit(1);
	}
	w_adjust_limit_map(app, &lst);
	w_set_map(app, &lst);
}
