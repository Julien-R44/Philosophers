/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 20:13:14 by jripoute          #+#    #+#             */
/*   Updated: 2015/09/16 01:25:56 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		get_random(void)
{
	return (time(NULL) % 10 + 1);
}

void	ft_error(int er)
{
	ft_putstr("Error : ");
	if (er == PTHREAD_MUTEX_INIT)
		ft_putstr("PTHREAD_MUTEX_INIT");
	if (er == PTHREAD_CREATE)
		ft_putstr("PTHREAD_CREATE");
	ft_putchar('\n');
	exit(-1);
}

t_dlist	*ft_global(t_dlist *list)
{
	static t_dlist	*tmp;

	if (list)
		tmp = list;
	return (tmp);
}
