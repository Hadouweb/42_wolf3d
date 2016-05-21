/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nle-bret <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 17:52:42 by nle-bret          #+#    #+#             */
/*   Updated: 2016/05/20 17:52:43 by nle-bret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		w_print_error_exit(char *str, char *error)
{
	ft_putstr_fd(str, 2);
	ft_putendl_fd(error, 2);
	exit(1);
}

void		w_check_directive(t_app *app, char *str)
{
	int		i;

	i = 0;
	if (str[1] && str[1] >= '0' && str[1] <= '9')
	{
		i++;
		while (str[i] && str[i] != ' ')
			i++;
		if (str[i] && str[i] == ' ')
		{
			i++;
			w_set_directive(app, str, i);
			return ;
		}
	}
	ft_putstr_fd("Mauvais format de directive\n", 2);
	exit(1);
}

int			w_check_line(t_app *app, char *str)
{
	int		i;

	i = 0;
	if (str)
	{
		if (str[0] && str[0] == '!')
		{
			w_check_directive(app, str);
			return (1);
		}
		else
		{
			while (str[i])
			{
				if (str[i] != ' ' && (str[i] > '9' || str[i] < '0'))
				{
					ft_putstr_fd("Mauvais format de map\n", 2);
					exit(1);
				}
				i++;
			}
		}
	}
	return (0);
}

int			w_check_position(t_app *app, char *str, char d)
{
	int		p;

	p = ft_atoi(str);
	if (d == 'x' && p >= 0 && p <= app->map.x)
		return (p);
	else if (d == 'y' && p >= 0 && p <= app->map.y)
		return (p);
	ft_putstr_fd("Mauvaise position de la camera\n", 2);
	exit(1);
	return (0);
}
