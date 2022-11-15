/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 11:55:32 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/15 11:58:58 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	create_forks(t_forks **forks, int n_phil)
{
	int				i;
	int				*f;
	pthread_mutex_t	*mutexes;

	f = malloc(sizeof(int) * n_phil);
	if (!f)
		return ;
	i = -1;
	while (++i < n_phil)
		f[i] = 0;
	i = -1;
	(*forks) = malloc(sizeof(t_forks) * n_phil);
	(mutexes) = malloc(sizeof(pthread_mutex_t) * n_phil);
	if (!(*forks) || !mutexes)
		return ;
	while (++i < n_phil)
	{
		(*forks)[i].in_use = &(f[i]);
		pthread_mutex_init(&((mutexes)[i]), NULL);
		(*forks)[i].f = &(mutexes[i]);
	}
}

void	create_philos(t_philo **p, t_data d, t_forks **forks)
{
	int			i;

	i = -1;
	while (++i < d.n_phil)
		(*p) = malloc(sizeof(t_philo) * d.n_phil);
	i = -1;
	while (++i < d.n_phil)
	{
		(*p)[i].nbr = i + 1;
		(*p)[i].r = (*forks)[i];
		if (i == 0)
			(*p)[i].l = (*forks)[d.n_phil - 1];
		else
			(*p)[i].l = (*forks)[i - 1];
		(*p)[i].d = d;
		pthread_create(&((*p)[i].id), NULL, philo_routine, (void *)&(p[i]));
	}
}
