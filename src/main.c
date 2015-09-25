/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/28 18:03:51 by skhatir           #+#    #+#             */
/*   Updated: 2015/09/25 06:41:15 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

# define X_OFB 27
# define Y_OFB 3

void	display_sprites(t_all *all, Uint32 ticks)
{
	SDL_Blit2(all->naruto.img, all->win, all->naruto.pos.x, all->naruto.pos.y,
		&all->naruto.clip[(ticks)%6]);
	SDL_Blit2(all->sasuke.img, all->win, all->sasuke.pos.x, all->sasuke.pos.y,
		&all->sasuke.clip[(ticks+4)%6]);
	SDL_Blit2(all->sakura.img, all->win, all->sakura.pos.x, all->sakura.pos.y,
		&all->sakura.clip[(ticks)%6]);
	SDL_Blit2(all->neji.img, all->win, all->neji.pos.x, all->neji.pos.y,
		&all->neji.clip[(ticks)%6]);
	SDL_Blit2(all->kakashi.img, all->win, all->kakashi.pos.x, all->kakashi.pos.y,
		&all->kakashi.clip[(ticks)%4]);
	SDL_Blit2(all->lee.img, all->win, all->lee.pos.x, all->lee.pos.y,
		&all->lee.clip[(ticks)%4]);
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
	SDL_Blit2(all->neji.bar, all->win, 440, 32, NULL);
	display_health_bar(all->rect_bar, all->win, 440 + 8, 32 + 3, philo->life);

	philo = list->next->next->next->next->content;
	SDL_Blit2(all->kakashi.bar, all->win, 350, 32, NULL);
	display_health_bar(all->rect_bar, all->win, 350 + 8, 32 + 3, philo->life);

	philo = list->next->next->next->next->next->content;
	SDL_Blit2(all->lee.bar, all->win, 440, 70, NULL);
	display_health_bar(all->rect_bar, all->win, 440 + 8, 70 + 3, philo->life);
}

void	display_all(t_all *all, t_dlist *list)
{
	// BG
	Uint32 ticks = SDL_GetTicks() / 110;
	SDL_BlitSurface(all->bg[ticks%7], NULL, all->win, &all->pos);

	// SDL_Blit2(all->lee.img, all->win, all->lee.pos.x, all->lee.pos.y,
	// 	&all->lee.clip[0]);
	// SDL_Blit2(all->lee.img, all->win, all->lee.pos.x, all->lee.pos.y - 50,
	// 	&all->lee.clip[1]);
	// SDL_Blit2(all->lee.img, all->win, all->lee.pos.x, all->lee.pos.y - 100,
	// 	&all->lee.clip[2]);
	// SDL_Blit2(all->lee.img, all->win, all->lee.pos.x, all->lee.pos.y - 150,
	// 	&all->lee.clip[3]);

	display_health(all, list);
	display_sprites(all, ticks);
}

void	remove_life(t_dlist *list)
{
	t_dlist *nav;

	nav = list;
	while (nav)
	{
		if (((t_philo *)nav->content)->statut != EATING)
			((t_philo *)nav->content)->life--;
		nav = nav->next;
	}
}

void	analyse(t_dlist *list)
{
	t_dlist *nav;

	nav = list;
	while (nav)
	{
		printf("Philo %d", ((t_philo *)nav->content)->name);
		if (((t_philo *)nav->content)->statut == RESTING)
			printf(" [RESTING]");
		else if (((t_philo *)nav->content)->statut == EATING)
			printf(" [EATING]");
		else if (((t_philo *)nav->content)->statut == SLEEPING)
			printf(" [SLEEPING] ");
		else if (((t_philo *)nav->content)->statut == THINKING)
			printf(" [THINKING] ");
		printf(" Life = [%d]\n", ((t_philo *)nav->content)->life);
		nav = nav->next;
	}
}

int		fps_system(t_dlist *list)
{
	static int				start_time;
	static int				current_time = 0;
	static int				time_left = TIMEOUT;
	int						tmp_time;

	if (!start_time)
		start_time = time(NULL);
	tmp_time = current_time;
	current_time = time(NULL) - start_time;
	if (tmp_time != current_time)
		remove_life(list);
	if (time_left != TIMEOUT - current_time)
	{
		if (time_left == 0) {
			printf("\nTime to dance fdp\n");
			exit(0);
		}
		printf("\n----- TIME LEFT = [%d] -----\n", time_left);
		analyse(list);
		time_left = TIMEOUT - current_time;
	}
	return (FALSE);
}

int main(int ac, char **av)
{
	t_dlist		*list;
	pthread_t	time_th;
	t_all		all;

	init_graphics(&all);
	list = init_philo_list();
	create_thread(list);
	main_loop(list, &all);
	// hook(&all, list);
	return (0);
}
