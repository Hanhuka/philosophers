/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:59:05 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/17 13:19:04 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	error_init_mutexes(pthread_mutex_t	*print, pthread_mutex_t	*dead)
{
	if (print)
		free(print);
	if (dead)
		free(dead);
	printf("Error: malloc failed!\n");
	return (1);
}

int	error_create_forks(t_forks *forks, pthread_mutex_t *check)
{
	if (check)
		free(check);
	if (forks)
		free(forks);
	printf("Error: malloc failed!\n");
	return (1);
}

long int	ft_atoi(const char *str)
{
	long int	i;
	long int	num;
	long int	neg;

	num = 0;
	neg = 1;
	i = 0;
	while ((str[i] >= '\t' && str[i] <= '\r') || str[i] == ' ')
		i++;
	if (str[i] == '-')
	{
		neg *= -1;
		i++;
	}
	if (str[i] == '+' && str[i - 1] != '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && neg != 0)
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * neg);
}
