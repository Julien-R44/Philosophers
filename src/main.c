/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/28 18:03:51 by skhatir           #+#    #+#             */
/*   Updated: 2015/09/24 06:20:25 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	create_thread(t_dlist *list)
{
	t_dlist *nav;
	t_philo	*philo;

	nav = list;
	while (nav)
	{
		philo = nav->content;
		if (pthread_create(&philo->th, NULL, func_th, ft_itoa(philo->name)) != 0)
			ft_error(PTHREAD_CREATE);
		nav = nav->next;
	}
}

t_dlist	*init_philo_list(void)
{
	t_dlist		*list;
	t_philo		philo;

	list = NULL;
	philo.name = 0;
	philo.life = MAX_LIFE;
	philo.statut = 0;
	philo.stick = 1;
	while (philo.name < 7)
	{
		if (pthread_mutex_init(&philo.mutex_stick, NULL) != 0)
			ft_error(PTHREAD_MUTEX_INIT);
		ft_dlstadd_end(&list, ft_dlstnew(&philo, sizeof(t_philo)));
		philo.name += 1;
	}
	return (list);
}

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

void	display_all(t_all *all)
{
	// BG
	printf("WOH\n");
	Uint32 ticks = SDL_GetTicks() / 110;
	SDL_BlitSurface(all->bg[ticks%7], NULL, all->win, &all->pos);

	// SDL_Blit2(all->sasuke.img, all->win, all->sasuke.pos.x, all->sasuke.pos.y,
	// 	&all->sasuke.clip[0]);
	// SDL_Blit2(all->sasuke.img, all->win, all->sasuke.pos.x, all->sasuke.pos.y - 50,
	// 	&all->sasuke.clip[1]);
	// SDL_Blit2(all->sasuke.img, all->win, all->sasuke.pos.x, all->sasuke.pos.y - 100,
	// 	&all->sasuke.clip[2]);
	// SDL_Blit2(all->sasuke.img, all->win, all->sasuke.pos.x, all->sasuke.pos.y - 150,
	// 	&all->sasuke.clip[3]);

	SDL_Blit2(all->sasuke.img, all->win, all->sasuke.pos.x, all->sasuke.pos.y,
		&all->sasuke.clip[(ticks+2)%4]);
	SDL_Blit2(all->naruto.img, all->win, all->naruto.pos.x, all->naruto.pos.y,
		&all->naruto.clip[(ticks)%4]);
}

SDL_Surface		*init_sprite(char *filename)
{
	SDL_Surface *img;

	img = IMG_Load(filename);
	if (!img)
		ft_error(IMG_LOAD);
	return (img);
}

void	load_background(SDL_Surface *bg[8])
{
	bg[0] = init_sprite("./img/bg/gif/frame_0.gif");
	bg[1] = init_sprite("./img/bg/gif/frame_1.gif");
	bg[2] = init_sprite("./img/bg/gif/frame_2.gif");
	bg[3] = init_sprite("./img/bg/gif/frame_3.gif");
	bg[4] = init_sprite("./img/bg/gif/frame_4.gif");
	bg[5] = init_sprite("./img/bg/gif/frame_5.gif");
	bg[6] = init_sprite("./img/bg/gif/frame_6.gif");
}

static void		cut_sprite_sheet(SDL_Rect *clip, int x, int y, int w, int h)
{
	clip->x = x;
	clip->y = y;
	clip->h = h;
	clip->w = w;
}

void	load_sprite(t_sprite *sprite, char *filename, int posx, int posy)
{
	// sprite->img = init_sprite(filename);
	sprite->img = SDL_LoadBMP(filename);
	if (sprite->img == NULL)
		ft_error(IMG_LOAD);
	sprite->pos.x = posx;
	sprite->pos.y = posy;
}

static void		set_transparency(t_sprite *sprite, Uint8 r, Uint8 g, Uint8 b)
{
	SDL_SetColorKey(sprite->img, SDL_SRCCOLORKEY,
		SDL_MapRGB(sprite->img->format, r, g, b));
}

void	cut_sheets(t_sprite *naruto, t_sprite *sasuke)
{
	int len;

	// Naruto
	len = naruto->img->h;
	cut_sprite_sheet(&naruto->clip[0], 0, 0, 35, len);
	cut_sprite_sheet(&naruto->clip[1], 46, 0, 35, len);
	cut_sprite_sheet(&naruto->clip[2], 95, 0, 50, len);
	cut_sprite_sheet(&naruto->clip[3], 147, 0, 50, len);
	// Sasuke
	len = sasuke->img->h;
	cut_sprite_sheet(&sasuke->clip[0], 0, 0, 45, len);
	cut_sprite_sheet(&sasuke->clip[1], 45, 0, 45, len);
	cut_sprite_sheet(&sasuke->clip[2], 90, 0, 45, len);
	cut_sprite_sheet(&sasuke->clip[3], 135, 0, 45, len);

}

void	update_philo(t_dlist *list)
{
	t_dlist	*nav;
	t_philo *philo;

	nav = list;
	philo = nav->content;
	while (nav)
	{
		if (philo->statut != EATING)
			philo->life--;
		if (philo->life < 1)
		{
			philo->statut = DEAD;
			printf("%d, DEAD BRUH\n", philo->name);
		}
		nav = nav->next;
		if (nav)
			philo = nav->content;
	}
}

void	hook(t_all *all, t_dlist *list)
{
	int			skip;
	SDL_Event	event;

	skip = FALSE;
	all->pos.x = 0;
	all->pos.y = 0;
		// ft_hungry(list);
	while (skip == FALSE)
	{
		printf("WOH\n");
		usleep(SEC / 7);
		// while (SDL_PollEvent(&event))
			// skip = key_hook(event);
		display_all(all);
		SDL_Flip(all->win);
	}
}

void	ft_hungry(t_dlist *list, t_all *all)
{
	t_dlist	*nav;
	t_philo *philo;

	nav = list;
	philo = nav->content;
	while (philo->statut != DEAD)
	{
		display_all(all);
		SDL_Flip(all->win);
		usleep(SEC / 7);
		if (philo->statut != EATING)
			philo->life--;
		if (philo->life < 1)
			philo->statut = DEAD;
		if (philo->statut != DEAD)
		{
			nav = nav->next == NULL ? list : nav->next;
			philo = nav->content;
		}
	}
}

int main(int ac, char **av)
{
	t_dlist		*list;
	pthread_t	time_th;
	t_all		all;

	all.win = init_window();
	load_background(all.bg);
	load_sprite(&all.naruto, "./img/standingNaruto.bmp", 20, 205);
	load_sprite(&all.sasuke, "./img/standingSasuke.bmp", 70, 205);
	set_transparency(&all.naruto, 51, 212, 2);
	set_transparency(&all.sasuke, 0, 158, 4);
	cut_sheets(&all.naruto, &all.sasuke);
	cut_sheets(&all.naruto, &all.sasuke);

	list = init_philo_list();
	ft_global(list);
	create_thread(list);
	if ((pthread_create(&time_th, NULL, time_func, list)) != 0)
		ft_putstr("err\n");
	ft_hungry(list, &all);
	// hook(&all, list);
	pthread_join(time_th, NULL);
	return (0);
}
