/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/28 18:03:54 by skhatir           #+#    #+#             */
/*   Updated: 2015/09/26 04:00:59 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
______________________________AUTHORIZED FUNCTIONS______________________________

◦ malloc.
◦ free.
◦ write, read.
◦ usleep.
◦ time.
◦ exit.
◦ pthread_create.
◦ pthread_detach.
◦ pthread_join.
◦ pthread_mutex_init.
◦ pthread_mutex_destroy.
◦ pthread_mutex_trylock.
◦ pthread_mutex_lock.
◦ pthread_mutex_unlock.
_______________________________________INF______________________________________


-> 3 globals authorized

-> compile:
		gcc -[flag] programme.c -lpthread -o binary_name

* usleep(1 000 000) = 1sec *
________________________________________________________________________________________
|laws:                                                                                 |
|                                                                                      |
|• 7 philosophes devront être assis autour d’une table.                                |
|                                                                                      |
|• Chaque philosophe possède un thread qui lui est propre.                             |
|                                                                                      |
|• À la gauche de chaque philosophe se trouve une baguette (il y a donc 7 baguettes    |
|en tout).                                                                             |
|                                                                                      |
|• Un philosophe ne peut se saisir d’une baguette que si elle se trouve adjacente à lui|
|(droite ou gauche).                                                                   |
|                                                                                      |
|• Deux philosophes ne peuvent pas utiliser la même baguette au même moment            |
|(paraît-il pour des raisons d’hygiène).                                               |
|______________________________________________________________________________________|
|• 3 étapes :                                                                          |
|	◦ Mange avec les 2 baguettes (droite et gauche).                                   |
|	◦ Repos (ne mange pas) et ne détient aucune baguette.                              |
|	◦ Réfléchit, dans ce cas le philosophe a UNE et UNE seule baguette en main.        |
|______________________________________________________________________________________|
|                                                                                      |
|• Un philosophe ne peut se saisir d’une baguette que si elle se trouve adjacente à lui|
|(droite ou gauche)                                                                    |
|                                                                                      |
|• Après l’état repos, un philosophe peut soit manger, soit réfléchir. Si un voisin    |
|réféchit déjà, le philosophe peut acquérir la baguette commune- c’est-à-dire qu’un    |
|philosophe peut se faire prendre la baguette quand il réfléchit.                      |
|                                                                                      |
|• Un philosophe qui ne mange pas perd 1 point de vie par SECONDE.                     |
|                                                                                      |
|• Après qu’un philosophe ait mangé, il récupère toute sa vie, et passe en Repos.      |
|                                                                                      |
|• Un philosophe dont les points de vie tombent à 0 meurt. À cet instant la simulation |
|s’interrompt jusqu’à l’appui d’une touche (dont le choix vous appartient). Cet        |
|appui provoque la libération des ressources et l’arrêt complet du progarmme.          |
|                                                                                      |
|• Les philosophes ne doivent pas manger dans un ordre arbitraire si l’on execute      |
|plusieurs fois le programme avec les mêmes paramètres. Ils ne doivent pas manger      |
|dans un ordre précis, pas de scheduler, un philosophe mange dès qu’il peut. Il faut   |
|respecter le caractère aléatoire des threads et faire avec.                           |
|______________________________________________________________________________________|
*/

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <time.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>
# include "libft.h"

// Defines
# define MAX_LIFE 10			// philo lifes
# define SEC 1000000            // 1seconde for usleep
# define EAT_T 2  * SEC   		// eat time
# define REST_T 5 * SEC			// time to rest
# define THINK_T 1 * SEC  		// think time
# define TIMEOUT 100		 		// time of game

// Status
# define RESTING 0
# define EATING  1
# define SLEEPING 2
# define THINKING 3
# define DEAD -1

// Graphics Define
# define FRAMERATE 110
# define WWIN 560
# define HWIN 272

typedef enum		s_err
{
	SYSCALL,
	CREATE_WINDOW,
	PTHREAD_MUTEX_INIT,
	PTHREAD_CREATE,
	IMG_LOAD,
	FONT_ERR,
}					t_err;

typedef struct		s_philo
{
	pthread_t		th;
	int				name;
	int				life;
	int				statut;
	int				stick;
	pthread_mutex_t	mutex_stick;
}					t_philo;

typedef struct	s_text
{
	TTF_Font	*font;
	SDL_Color	color;
}				t_text;

typedef struct		s_sprite
{
	SDL_Surface		*img;
	SDL_Surface		*bar;
	SDL_Rect		pos;
	SDL_Rect		clip[6];
}					t_sprite;

typedef struct		s_all
{
	SDL_Surface 	*win;
	SDL_Surface 	*bg[7];
	SDL_Rect		pos;
	SDL_Surface		*rect_bar;
	t_sprite		*sprites;
	t_text			text;
	int				timeleft;
	SDL_Surface		*heal;
}					t_all;

SDL_Surface		*init_window(void);
void	display_all(t_all *all, t_dlist *list);
void	main_loop(t_dlist *list, t_all *all);

void	cut_sheets(t_sprite *naruto, t_sprite *sasuke, t_sprite *sakura, t_sprite *neji, t_sprite *kakashi);
void	cut_sheets2(t_sprite *lee, t_sprite *orochimaru);

void	remove_life(t_dlist *list);
void	analyse(t_dlist *list);

/*
** init_graphics.c
*/
void					init_graphics(t_all *all);

/*
** init_philo.c
*/
t_dlist					*init_philo_list(void);
void					create_thread(t_dlist *list);

/*
** Main.c
*/
// void					ft_hungry(t_dlist *list);

/*
** Thread.c
*/
void					create_thread(t_dlist *philosopher);
void					*func_th(void *name);
void					*time_func(void *name);

/*
** Misc.c
*/
int						get_random(void);
t_dlist					*ft_global(t_dlist *list);
void					ft_error(int er);
void					SDL_Blit2(SDL_Surface *src, SDL_Surface *dst, int x, int y, SDL_Rect *clip);


#endif
