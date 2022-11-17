/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:48:23 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/17 11:33:08 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

void	take_forks(t_philo *p)
{
	while (!check_add_death(p))
	{
		pthread_mutex_lock((*p).r.check);
		if (!((*(*p).r.in_use)))
		{
			*((*p).r.in_use) = 1;
			pthread_mutex_unlock((*p).r.check);
			break ;
		}
		pthread_mutex_unlock((*p).r.check);
	}
	if (!check_death(p))
		print_action(p, "has taken a fork\n");
	while (!check_add_death(p))
	{
		pthread_mutex_lock((*p).l.check);
		if (!((*(*p).l.in_use)))
		{
			*((*p).l.in_use) = 1;
			pthread_mutex_unlock((*p).l.check);
			break ;
		}
		pthread_mutex_unlock((*p).l.check);
	}
}

void	philo_drop_forks(t_philo *p)
{
	pthread_mutex_lock((*p).l.check);
	*((*p).l.in_use) = 0;
	pthread_mutex_unlock((*p).l.check);
	pthread_mutex_lock((*p).r.check);
	*((*p).r.in_use) = 0;
	pthread_mutex_unlock((*p).r.check);
}

int	philo_eat(t_philo *p)
{
	take_forks(p);
	if (!check_death(p))
		print_action_eat(p);
	(*p).times_eat++;
	(*p).last_eat = time_now(p);
	if (philo_sleep(p, (*p).data->t_eat))
		return (1);
	philo_drop_forks(p);
	return (0);
}

//Return 1 means death
//Return 0 no deaths
int	philo_sleep(t_philo *p, unsigned long action)
{
	unsigned long	s_start;
	unsigned long	t_passed;

	t_passed = 0;
	s_start = time_now(p);
	while (!check_add_death(p) && !(t_passed >= action))
	{
		if (check_death(p))
			return (1);
		usleep(100);
		t_passed = time_now(p) - s_start;
	}
	if (t_passed >= action)
		return (0);
	return (1);
}
