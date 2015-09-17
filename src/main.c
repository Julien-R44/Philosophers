/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/28 18:03:51 by skhatir           #+#    #+#             */
/*   Updated: 2015/09/17 02:47:03 by jripoute         ###   ########.fr       */
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

void	ft_hungry(t_dlist *list)
{
	t_dlist	*nav;
	t_philo *philo;

	nav = list;
	philo = nav->content;
	while (philo->statut != DEAD)
	{
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

	// list = init_philo_list();
	// ft_global(list);
	// create_thread(list);
	// if ((pthread_create(&time_th, NULL, time_func, list)) != 0)
	// 	ft_putstr("err\n");
	// ft_hungry(list);
	// pthread_join(time_th, NULL);

	SDL_Init(SDL_INIT_VIDEO);

	SDL_Quit();
	return (0);
}
