/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/17 20:40:04 by jripoute          #+#    #+#             */
/*   Updated: 2015/09/25 00:03:21 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

SDL_Surface		*init_window(void)
{
	SDL_Surface *win;

	SDL_Init(SDL_INIT_VIDEO);
	win = SDL_SetVideoMode(WWIN, HWIN, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Philosophers", NULL);
	SDL_FillRect(win, NULL, SDL_MapRGB(win->format, 10, 120, 236));
	return (win);
}
