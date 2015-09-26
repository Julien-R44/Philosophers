/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/15 20:13:14 by jripoute          #+#    #+#             */
/*   Updated: 2015/09/26 02:41:41 by y0ja             ###   ########.fr       */
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
	if (er == SYSCALL)
		ft_putstr("SYCALL");
	else if (er == FONT_ERR)
		ft_putstr("FONT_ERR");
	else if (er == CREATE_WINDOW)
		ft_putstr("SDL_ERROR");
	else if (er == PTHREAD_MUTEX_INIT)
		ft_putstr("PTHREAD_MUTEX_INIT");
	else if (er == PTHREAD_CREATE)
		ft_putstr("PTHREAD_CREATE");
	else if (er == IMG_LOAD)
		ft_putstr("IMG_LOAD");
	ft_putstr("\nExit... \n");
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
