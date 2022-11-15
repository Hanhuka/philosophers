/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:36:30 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/15 11:59:16 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	is_number(char *str)
{
	int	i;
	int	swt;

	swt = 0;
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	while (str[i])
	{
		if (!swt && str[i] <= '9' && str[i] >= '0')
			swt++;
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	if (!swt)
		return (0);
	return (1);
}

void	not_number(int nbr)
{
	if (nbr == 2)
		printf("Error: The 2nd argument is not a number\n");
	else if (nbr == 3)
		printf("Error: The 3rd argument is not a number\n");
	else
		printf("Error: The %dth argument is not a number\n", nbr);
	exit(1);
}

void	check_arg_count(int ac)
{
	if (ac < 5 || ac > 6)
	{
		printf("Error: Wrong number of arguments\n");
		exit(1);
	}
}

void	save_args(int ac, char **av, t_data *d)
{
	(*d).n_phil = ft_atoi(av[1]);
	(*d).t_die = ft_atoi(av[2]);
	(*d).t_eat = ft_atoi(av[3]);
	(*d).t_sleep = ft_atoi(av[4]);
	if (ac == 5)
		(*d).n_eat = -1;
	else
		(*d).n_eat = ft_atoi(av[5]);
	printf("n_phil  = %d\n", (*d).n_phil);
	printf("t_die   = %d\n", (*d).t_die);
	printf("t_eat   = %d\n", (*d).t_eat);
	printf("t_sleep = %d\n", (*d).t_sleep);
}

void	check_args(int ac, char **av, t_data *d)
{
	int	i;

	i = 1;
	check_arg_count(ac);
	while (i < ac)
	{
		if (!is_number(av[i]))
			not_number(i + 1);
		if (i == 1 && !ft_atoi(av[i]))
		{
			printf("Error: There needs to be at least one philosopher\n");
			exit(1);
		}
		if (ft_atoi(av[i]) > 2147483647 || ft_atoi(av[i]) <= 0)
		{
			printf("Error: Every number needs to be positive and ");
			printf("not bigger than INT MAX\n");
			exit(1);
		}
		i++;
	}
	save_args(ac, av, d);
}
