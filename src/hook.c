/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 22:04:11 by y0ja              #+#    #+#             */
/*   Updated: 2015/09/25 06:38:02 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int		exit_hook(SDL_Event event)
{
	if (event.type == SDL_QUIT ||
		(event.type == SDL_KEYDOWN &&
		event.key.keysym.sym == SDLK_ESCAPE))
			return (1);
	return (0);
}

int		key_hook(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_SPACE)
			printf("space\n");
	}
	return (exit_hook(event));
}

void	main_loop(t_dlist *list, t_all *all)
{
	int			skip;
	Uint32 		ticks;
	SDL_Event	event;

	printf("Go : \n");
	skip = FALSE;
	all->pos.x = 0;
	all->pos.y = 0;
	while (skip == FALSE)
	{
		skip = fps_system(list);
		while (SDL_PollEvent(&event))
			skip = key_hook(event);
		display_all(all, list);
		SDL_Flip(all->win);
	}
}
