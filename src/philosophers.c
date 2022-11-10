/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:59:19 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/10 16:52:01 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	create_forks(pthread_mutex_t	**forks, int n_phil)
{
	int	i;

	i = 0;
	*forks = malloc(sizeof(pthread_mutex_t) * n_phil);
	while (i < n_phil)
	{
		pthread_mutex_init(&((*forks)[i]), NULL);
		i++;
	}
}

int	time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	create_philos(t_data *d)
{
	int		i;
	t_philo	p;

	i = -1;
	while (++i < (*d).n_phil)
	{
		pthread_create(&philo[i], philo_routine, NULL);
	}
}

int main(int ac, char **av)
{
	t_data			d;
	pthread_mutex_t	*forks;

	check_args(ac, av, &d);
	create_forks(&forks, d.n_phil);
	create_philos(&d);
}