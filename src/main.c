/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: y0ja <y0ja@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/07/28 18:03:51 by skhatir           #+#    #+#             */
/*   Updated: 2015/09/26 00:27:39 by y0ja             ###   ########.fr       */
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
	return (0);
}
