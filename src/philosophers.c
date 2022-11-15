/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:59:19 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/15 17:17:43 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*philo_routine(void *phil)
{
	t_philo	*p;

	p = ((t_philo *)phil);
	p->t_start = time_ms();
	// printf("%ld, Hi! Philo nbr %d here.\n", time_now(p), (*p).nbr);
	while (!check_death(p))
	{
		philo_eat(p);
		if (!check_death(p))
			print_action(p, "is sleeping\n");
		philo_sleep(p, (*p).data.t_sleep);
		if (!check_death(p))
			print_action(p, "is thinking\n");
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data			d;
	t_forks			*forks;
	t_philo			*p;
	int				i;
	int				dead;

	dead = 0;
	check_args(ac, av, &d);
	create_forks(&forks, d.n_phil);
	if (!forks)
		return (1);
	create_philos(&p, d, &forks, &dead);
	i = -1;
	while (++i < d.n_phil)
		pthread_join(p[i].id, NULL);
}
