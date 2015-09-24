/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 20:13:14 by jripoute          #+#    #+#             */
/*   Updated: 2015/09/24 05:18:22 by y0ja             ###   ########.fr       */
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
	if (er == IMG_LOAD)
		ft_putstr("IMG_LOAD");
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

void	SDL_Blit2(SDL_Surface *src, SDL_Surface *dst, int x, int y, SDL_Rect *clip)
{
	SDL_Rect	offset;

	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, clip, dst, &offset);
}
