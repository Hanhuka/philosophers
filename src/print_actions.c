/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:29:09 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/16 16:29:31 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

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
