/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/24 21:55:12 by y0ja              #+#    #+#             */
/*   Updated: 2015/09/24 22:19:54 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	create_thread(t_dlist *list)
{
	t_dlist *nav;
	t_philo	*philo;

	nav = list;
	ft_global(list);
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
