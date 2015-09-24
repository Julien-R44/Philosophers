/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/28 18:03:54 by skhatir           #+#    #+#             */
/*   Updated: 2015/09/24 06:19:21 by y0ja             ###   ########.fr       */
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
# include "libft.h"

// Defines
# define MAX_LIFE 10			// philo lifes
# define SEC 1000000            // 1seconde for usleep
# define EAT_T 1  * SEC   		// eat time
# define REST_T 1 * SEC			// time to rest
# define THINK_T 1 * SEC  		// think time
# define TIMEOUT 200	 		// time of game

// Status
# define EATING  1
# define SLEEPING 2
# define THINKING 3
# define DEAD -1

// OpenGL Define
# define WWIN 560
# define HWIN 272

// Object Define
# define TABLE_HEIGHT 1.5
# define TABLE_BASE 1

typedef enum			s_err
{
	CREATE_WINDOW,
	PTHREAD_MUTEX_INIT,
	PTHREAD_CREATE,
	IMG_LOAD,
}						t_err;

typedef struct			s_philo
{
	pthread_t			th;
	int					name;
	int					life;
	int					statut;
	int					stick;
	pthread_mutex_t		mutex_stick;
}						t_philo;

typedef struct	s_sprite
{
	SDL_Surface	*img;
	SDL_Rect	pos;
	SDL_Rect	clip[5];
}				t_sprite;

typedef struct	s_all
{
	SDL_Surface *win;
	SDL_Surface *bg[7];
	SDL_Rect	pos;
	t_sprite	naruto;
	t_sprite	sasuke;
}				t_all;

SDL_Surface		*init_window(void);


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
