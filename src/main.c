/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/28 18:03:51 by skhatir           #+#    #+#             */
/*   Updated: 2015/09/26 02:54:15 by y0ja             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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

int main(int ac, char **av)
{
	t_dlist		*list;
	pthread_t	time_th;
	t_all		all;

	all.timeleft = TIMEOUT;
	init_graphics(&all);
	list = init_philo_list();
	create_thread(list);
	main_loop(list, &all);
	return (0);
}
