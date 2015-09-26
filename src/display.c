/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/26 00:24:25 by y0ja              #+#    #+#             */
/*   Updated: 2015/09/26 04:19:06 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

static void		display_time(t_all *all, int time_left)
{
	SDL_Surface	*img[2];
	char		*str;
	char		*str2;

	str = ft_itoa(time_left);
	str2 = ft_strjoin("TIME LEFT : ", str);
	img[0] = TTF_RenderText_Solid(all->text.font, str2, all->text.color);
	SDL_Blit2(img[0], all->win, 215, 32, NULL);
	SDL_FreeSurface(img[0]);
	free(str);
	free(str2);
}

static void	display_sprites(t_all *all, Uint32 ticks)
{
	int i;
	int	limit;

	i = 0;
	limit = 6;
	while (i < 7)
	{
		if (i == 3)
			limit = 4;
		SDL_Blit2(all->sprites[i].img, all->win, all->sprites[i].pos.x, \
			all->sprites[i].pos.y, &all->sprites[i].clip[(ticks%limit)]);
		i++;
	}
}

static void		display_health_bar(SDL_Surface *bar, SDL_Surface *win, int x, int y, int health)
{
	SDL_Rect	clip;

	clip.x = 0;
	clip.y = 0;
	clip.h = 40;
	clip.w = health * clip.h / MAX_LIFE;
	SDL_Blit2(bar, win, x, y , &clip);
}

static void		display_health(t_all *all, t_dlist *list)
{
	t_dlist		*nav;
	int			i;
	int			posx[] = {32, 120, 32, 120, 440, 440, 350};
	int			posy[] = {32, 32, 70, 70, 32, 70, 32};
	int			offsetx;

	i = 0;
	nav = list;
	offsetx = 27;
	while (i < 7)
	{
		if (i == 4)
			offsetx = 8;
		SDL_Blit2(all->sprites[i].bar, all->win, posx[i], posy[i], NULL);
		display_health_bar(all->rect_bar, all->win, posx[i] + offsetx, \
			posy[i] + 3, ((t_philo *)nav->content)->life);
		nav = nav->next;
		i++;
	}
}

void			display_all(t_all *all, t_dlist *list)
{
	// Background
	Uint32 ticks = SDL_GetTicks() / FRAMERATE;
	SDL_BlitSurface(all->bg[ticks%7], NULL, all->win, &all->pos);

	SDL_Blit2(all->heal, all->win, 250, 80, NULL);

	display_health(all, list);
	display_sprites(all, ticks);
	display_time(all, all->timeleft);
}
