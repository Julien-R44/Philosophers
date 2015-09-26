/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 22:04:11 by y0ja              #+#    #+#             */
/*   Updated: 2015/09/26 02:53:47 by y0ja             ###   ########.fr       */
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

int		fps_system(t_all *all, t_dlist *list)
{
	static int				start_time;
	static int				current_time = 0;
	int						tmp_time;

	if (!start_time)
		start_time = time(NULL);
	tmp_time = current_time;
	current_time = time(NULL) - start_time;
	if (tmp_time != current_time)
		remove_life(list);
	if (all->timeleft != TIMEOUT - current_time)
	{
		if (all->timeleft == 0) {
			printf("\nTime to dance fdp\n");
			exit(0);
		}
		printf("\n----- TIME LEFT = [%d] -----\n", all->timeleft);
		analyse(list);
		all->timeleft = TIMEOUT - current_time;
	}
	return (FALSE);
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
		skip = fps_system(all, list);
		while (SDL_PollEvent(&event))
			skip = key_hook(event);
		display_all(all, list);
		SDL_Flip(all->win);
	}
}
