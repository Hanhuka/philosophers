/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 14:48:23 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/15 17:15:59 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

// void	take_forks(t_philo *p)
// {
// 	pthread_mutex_lock((*p).r.check);
// 	if (!((*p).r.in_use))
// 	{
// 		(*p).r.in_use = 1;
		
// 	}
// 	pthread_mutex_unlock((*p).r.check);
// }

int	philo_eat(t_philo *p)
{
	// take_forks(*p);
	pthread_mutex_lock((*p).r.f);
	if (!check_death(p))
		print_action(p, "has taken a fork\n");
	else
		return (pthread_mutex_unlock((*p).r.f));
	pthread_mutex_lock((*p).l.f);
	if (!check_death(p))
		print_action_eat(p);
	else
	{
		pthread_mutex_unlock((*p).l.f);
		return (pthread_mutex_unlock((*p).r.f));
	}
	(*p).last_eat = time_now(p);
	if (philo_sleep(p, (*p).data.t_eat))
		return (1);
	pthread_mutex_unlock((*p).r.f);
	pthread_mutex_unlock((*p).l.f);
	return (0);
}

//Return 1 means death
//Return 0 no deaths
int	philo_sleep(t_philo *p, unsigned long action)
{
	unsigned long	s_start;
	unsigned long	t_passed;

	t_passed = 0;
	s_start = time_now(p) * 1000;
	while (!check_add_death(p) && !(t_passed >= action * 1000))
	{
		if (check_death(p))
			return (1);
		usleep(100);
		t_passed = time_now(p) * 1000 - s_start;
	}
	if (t_passed >= action * 1000)
		return (0);
	return (1);
}

void	print_action_eat(t_philo *p)
{
	pthread_mutex_lock((*p).print);
	printf("%lu %d %s", time_now(p), (*p).nbr, "has taken a fork\n");
	printf("%lu %d %s", time_now(p), (*p).nbr, "is eating\n");
	pthread_mutex_unlock((*p).print);
}

//prints: "(timestamp_in_ms) (philo_nbr) (message)"
void	print_action(t_philo *p, char *message)
{
	pthread_mutex_lock((*p).print);
	printf("%lu %d %s", time_now(p), (*p).nbr, message);
	pthread_mutex_unlock((*p).print);
}
