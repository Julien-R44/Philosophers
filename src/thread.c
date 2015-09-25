/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/08/11 00:37:35 by skhatir           #+#    #+#             */
/*   Updated: 2015/09/25 06:44:51 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philosopher.h"

int		func2_th(t_philo *philo, t_philo *next_philo)
{
	if (!next_philo->stick && !philo->stick)
		return (0);
	if (!pthread_mutex_trylock(&philo->mutex_stick) && !pthread_mutex_trylock(&next_philo->mutex_stick))
	{
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
			usleep(EAT_T);
			philo->statut = SLEEPING;
			philo->stick = 1;
			next_philo->stick = 1;
			philo->statut = RESTING;
			usleep(REST_T);
		}
		pthread_mutex_unlock(&philo->mutex_stick);
		pthread_mutex_unlock(&next_philo->mutex_stick);
	}
	return (NULL);
}


