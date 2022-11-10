/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:39:18 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/10 16:41:02 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h> 
# include <pthread.h>
# include <sys/time.h>

typedef struct s_fork
{
	int				in_use;
	pthread_mutex_t	f;
}	t_forks;

typedef struct s_data
{
	int		n_phil;
	int		t_die;
	int		t_eat;
	int		t_sleep;
	int		n_eat;
}	t_data;

typedef struct s_philo
{
	int				last_eat;
	int				times_eat;
	int				nbr;
	pthread_mutex_t	*r;
	pthread_mutex_t	*l;
	int				*dead;
	t_data			d;
}	t_philo;

//philosophers.c

//utils.c
long int	ft_atoi(const char *str);

//args_check.c
int			is_number(char *str);
void		not_number(int nbr);
void		check_arg_count(int ac);
void		save_args(int ac, char **av, t_data *d);
void		check_args(int ac, char **av, t_philo *p);

#endif