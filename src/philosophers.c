/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:59:19 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/16 17:12:10 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	free_all(t_philo *p, t_forks *forks, t_data d)
{
	int	i;

	i = -1;
	pthread_mutex_destroy(p->print);
	pthread_mutex_destroy(p->d_check);
	while (++i < d.n_phil)
	{
		pthread_mutex_destroy(forks[i].check);
		pthread_mutex_destroy(p[i].r.check);
	}
	free(p->print);
	free(p->d_check);
	free(forks->in_use);
	free(forks->check);
	free(forks);
	free(p);
}

	// print_action(p, "Has appeared!\n");
	// printf("mutex = %p\n", (*p).print);
	// printf("%ld, Hi! Philo nbr %d here.\n", time_now(p), (*p).nbr);
void	*philo_routine(void *phil)
{
	t_philo	*p;

	p = ((t_philo *)phil);
	p->last_eat = 0;
	if (!((*p).nbr % 2))
		usleep(10000);
	while (!check_add_death(p))
	{
		philo_eat(p);
		if (!check_add_death(p))
			print_action(p, "is sleeping\n");
		philo_sleep(p, (*p).data->t_sleep);
		if (!check_add_death(p))
			print_action(p, "is thinking\n");
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_data			d;
	t_forks			*forks;
	t_philo			*p;
	int				dead;
	int				i;

	dead = 0;
	check_args(ac, av, &d);
	create_forks(&forks, d.n_phil);
	if (!forks)
		return (1);
	create_philos(&p, &d, &forks, &dead);
	i = -1;
	while (++i < d.n_phil)
		pthread_join(p[i].id, NULL);
	free_all(p, forks, d);
}
