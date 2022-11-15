/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:59:19 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/15 11:59:11 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	*philo_routine(void *phil)
{
	t_philo	p;

	p = *((t_philo *)phil);
	printf("Hi! Philo nbr %d here.\n", p.nbr + 1);
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data			d;
	t_forks			*forks;
	t_philo			*p;
	int				i;

	check_args(ac, av, &d);
	printf("args checked!\n");
	create_forks(&forks, d.n_phil);
	printf("forks created!\n");
	if (!forks)
		return (1);
	create_philos(&p, d, &forks);
	i = -1;
	while (++i < d.n_phil)
		pthread_join(p[i].id, NULL);
}
