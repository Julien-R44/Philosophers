/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/26 00:24:25 by y0ja              #+#    #+#             */
/*   Updated: 2015/09/26 00:28:01 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "philosopher.h"

# define X_OFB 27
# define Y_OFB 3

static void		display_time(t_all *all, int time_left)
{
	SDL_Surface	*(img[2]);
	char		*str;

	str = ft_itoa(time_left);
	img[0] = TTF_RenderText_Solid(all->text.font, str, all->text.color);
	SDL_Blit2(img[0], all->win, (WWIN - 160), 10, NULL);
	img[1] = TTF_RenderText_Solid(all->text.font, "pts", all->text.color);
	SDL_Blit2(img[1], all->win, (WWIN - 80), 10, NULL);
	SDL_FreeSurface(img[0]);
	SDL_FreeSurface(img[1]);
	free(str);
}

void	display_sprites(t_all *all, Uint32 ticks)
{
	SDL_Blit2(all->naruto.img, all->win, all->naruto.pos.x, all->naruto.pos.y,
		&all->naruto.clip[(ticks)%6]);
	SDL_Blit2(all->sasuke.img, all->win, all->sasuke.pos.x, all->sasuke.pos.y,
		&all->sasuke.clip[(ticks)%6]);
	SDL_Blit2(all->sakura.img, all->win, all->sakura.pos.x, all->sakura.pos.y,
		&all->sakura.clip[(ticks)%6]);
	SDL_Blit2(all->neji.img, all->win, all->neji.pos.x, all->neji.pos.y,
		&all->neji.clip[(ticks)%6]);
	SDL_Blit2(all->kakashi.img, all->win, all->kakashi.pos.x, all->kakashi.pos.y,
		&all->kakashi.clip[(ticks)%4]);
	SDL_Blit2(all->lee.img, all->win, all->lee.pos.x, all->lee.pos.y,
		&all->lee.clip[(ticks)%4]);
	SDL_Blit2(all->orochimaru.img, all->win, all->orochimaru.pos.x, all->orochimaru.pos.y,
		&all->orochimaru.clip[(ticks)%4]);
}

void	display_health_bar(SDL_Surface *bar, SDL_Surface *win, int x, int y, int health)
{
	SDL_Rect	clip;

	clip.x = 0;
	clip.y = 0;
	clip.h = 40;
	clip.w = health * clip.h / MAX_LIFE;
	SDL_Blit2(bar, win, x, y , &clip);
}

void	display_health(t_all *all, t_dlist *list)
{
	t_philo *philo;

	philo = list->content;
	SDL_Blit2(all->naruto.bar, all->win, 32, 32, NULL);
	display_health_bar(all->rect_bar, all->win, 32 + X_OFB, 32 + Y_OFB, philo->life);

	philo = list->next->content;
	SDL_Blit2(all->sasuke.bar, all->win, 120, 32, NULL);
	display_health_bar(all->rect_bar, all->win, 120 + X_OFB, 32 + Y_OFB, philo->life);

	philo = list->next->next->content;
	SDL_Blit2(all->sakura.bar, all->win, 32, 70, NULL);
	display_health_bar(all->rect_bar, all->win, 32 + X_OFB, 70 + Y_OFB, philo->life);

	philo = list->next->next->next->content;
	SDL_Blit2(all->kakashi.bar, all->win, 120, 70, NULL);
	display_health_bar(all->rect_bar, all->win, 120 + X_OFB, 70 + Y_OFB, philo->life);

	philo = list->next->next->next->next->content;
	SDL_Blit2(all->neji.bar, all->win, 440, 32, NULL);
	display_health_bar(all->rect_bar, all->win, 440 + 8, 32 + 3, philo->life);

	philo = list->next->next->next->next->next->content;
	SDL_Blit2(all->lee.bar, all->win, 440, 70, NULL);
	display_health_bar(all->rect_bar, all->win, 440 + 8, 70 + 3, philo->life);

	philo = list->next->next->next->next->next->next->content;
	SDL_Blit2(all->orochimaru.bar, all->win, 350, 32, NULL);
	display_health_bar(all->rect_bar, all->win, 350 + 8, 32 + 3, philo->life);
}

void	display_all(t_all *all, t_dlist *list)
{
	// BG
	Uint32 ticks = SDL_GetTicks() / FRAMERATE;
	SDL_BlitSurface(all->bg[ticks%7], NULL, all->win, &all->pos);

	// SDL_Blit2(all->orochimaru.img, all->win, all->orochimaru.pos.x, all->orochimaru.pos.y,
	// 	&all->orochimaru.clip[0]);
	// SDL_Blit2(all->orochimaru.img, all->win, all->orochimaru.pos.x, all->orochimaru.pos.y - 70,
	// 	&all->orochimaru.clip[1]);
	// SDL_Blit2(all->orochimaru.img, all->win, all->orochimaru.pos.x, all->orochimaru.pos.y - 150,
	// 	&all->orochimaru.clip[2]);
	// SDL_Blit2(all->orochimaru.img, all->win, all->orochimaru.pos.x, all->orochimaru.pos.y - 220,
	// 	&all->orochimaru.clip[3]);

	display_health(all, list);
	display_sprites(all, ticks);
	// display_time();
}
