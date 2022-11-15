/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_handle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:53:31 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/15 17:00:50 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

unsigned long	time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

unsigned long	time_now(t_philo *p)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000) - (*p).t_start);
}

int	check_add_death(t_philo *p)
{
	if (check_death(p))
		return (1);
	if (time_now(p) - (*p).last_eat >= (*p).data.t_die)
	{
		pthread_mutex_lock((*p).d_check);
		(*((*p).dead))++;
		print_action(p, "died\n");
		pthread_mutex_unlock((*p).d_check);
		return (1);
	}
	return (0);
}

int	check_death(t_philo *p)
{
	pthread_mutex_lock((*p).d_check);
	if (*((*p).dead))
	{
		pthread_mutex_unlock((*p).d_check);
		return (1);
	}
	pthread_mutex_unlock((*p).d_check);
	return (0);
}
