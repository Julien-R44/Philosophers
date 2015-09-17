/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jripoute <jripoute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/11 00:37:35 by skhatir           #+#    #+#             */
/*   Updated: 2015/09/17 00:20:53 by jripoute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosopher.h"

void	*time_func(void *list)
{
	int			time_out;
	t_dlist		*nav;

	nav = list;
	time_out = TIMEOUT;
	while (time_out)
	{
		printf("\n--time : %d--\n", time_out);
		nav = list;
		while (nav != NULL)
		{
			if (((t_philo *)nav->content)->statut == DEAD)
			{
				printf("%d is dead\n", ((t_philo *)nav->content)->name);
				exit(0);
			}
			nav = nav->next;
		}
		usleep(SEC);
		time_out--;
	}
	printf("TIMEOUT: time to dance\n");
	exit(EXIT_SUCCESS);
	return (NULL);
}

int		func2_th(t_philo *philo, t_philo *next_philo)
{
	if (!next_philo->stick && !philo->stick)
		return (0);
	if (!pthread_mutex_trylock(&philo->mutex_stick) && !pthread_mutex_trylock(&next_philo->mutex_stick))
	{
		philo->statut = EATING;
		philo->stick = 0;
		next_philo->stick = 0;
		return (1);
	}
	return (0);
}

void	*func_th(void *arg)
{
	t_dlist *list;
	t_dlist *head;
	t_philo *philo;
	t_philo *next_philo;

	head = ft_global(NULL);
	list = head;
	while (((t_philo *)list->content)->name != ft_atoi(arg))
		list = list->next;
	philo = list->content;
	next_philo = (list->next == NULL ? head->content : list->next->content);
	while (philo->statut != DEAD)
	{
		usleep((get_random() * SEC) / 10);
		if (func2_th(philo, next_philo))
		{
			philo->statut = EATING;
			philo->life = MAX_LIFE;
			printf("philo %d eat life = %d\n", philo->name, philo->life);
			usleep(EAT_T);
			philo->statut = SLEEPING;
			philo->stick = 1;
			next_philo->stick = 1;
			usleep(REST_T);
		}
		pthread_mutex_unlock(&philo->mutex_stick);
		pthread_mutex_unlock(&next_philo->mutex_stick);
	}
	return (NULL);
}


