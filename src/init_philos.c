/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:55:32 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/17 13:19:24 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

static int	init_mutexes(t_philo **p, int n_phil)
{
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead;
	int				i;

	print = malloc(sizeof(pthread_mutex_t));
	dead = malloc(sizeof(pthread_mutex_t));
	if (!dead || !print)
		return (error_init_mutexes(print, dead));
	if (pthread_mutex_init(print, NULL) || pthread_mutex_init(dead, NULL))
	{
		printf("Error creating mutex\n");
		return (1);
	}
	i = -1;
	while (++i < n_phil)
	{
		(*p)[i].print = print;
		(*p)[i].d_check = dead;
	}
	return (0);
}

int	create_forks(t_forks **forks, int n_phil)
{
	int				i;
	int				*f;
	pthread_mutex_t	*check;

	f = malloc(sizeof(int) * n_phil);
	if (!f)
		return (1);
	i = -1;
	while (++i < n_phil)
		f[i] = 0;
	i = -1;
	(*forks) = malloc(sizeof(t_forks) * n_phil);
	(check) = malloc(sizeof(pthread_mutex_t) * n_phil);
	if (!(*forks) || !check)
		return (error_create_forks(*forks, check));
	while (++i < n_phil)
	{
		(*forks)[i].in_use = &(f[i]);
		pthread_mutex_init(&((check)[i]), NULL);
		(*forks)[i].check = &(check[i]);
	}
	return (0);
}

static int	allocate_philos(t_philo **p, t_data *d, t_forks **forks, int *dead)
{
	int			i;

	i = -1;
	(*p) = malloc(sizeof(t_philo) * d->n_phil);
	if (!(*p))
	{
		printf("Error creating mutex\n");
		return (1);
	}
	i = -1;
	while (++i < d->n_phil)
	{
		(*p)[i].dead = dead;
		(*p)[i].nbr = i + 1;
		(*p)[i].r = (*forks)[i];
		(*p)[i].times_eat = 0;
		if (i == 0)
			(*p)[i].l = (*forks)[d->n_phil - 1];
		else
			(*p)[i].l = (*forks)[i - 1];
		(*p)[i].data = d;
	}
	return (0);
}

int	create_philos(t_philo **p, t_data *d, t_forks **forks, int *dead)
{
	int	i;

	if (allocate_philos(p, d, forks, dead) || init_mutexes(p, d->n_phil))
		return (1);
	i = -1;
	d->start = time_ms();
	while (++i < d->n_phil)
	{
		if (pthread_create(&((*p)[i].id), NULL, philo_routine, \
		(void *)(&((*p)[i]))))
		{
			printf("Error creating thread\n");
			return (1);
		}
	}
	return (0);
}
