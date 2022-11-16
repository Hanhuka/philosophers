/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralves-g <ralves-g@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:39:18 by ralves-g          #+#    #+#             */
/*   Updated: 2022/11/16 16:29:56 by ralves-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define OCCUPIED 0
# define WAITING 1
# define DELAY 200

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h> 
# include <pthread.h>
# include <sys/time.h>

typedef struct s_fork
{
	int				*in_use;
	pthread_mutex_t	*check;
}	t_forks;

typedef struct s_data
{
	unsigned long		start;
	int					n_phil;
	unsigned long		t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;
}	t_data;

typedef struct s_philo
{
	pthread_t		id;
	unsigned long	t_start;
	unsigned long	last_eat;
	int				times_eat;
	int				nbr;
	t_forks			r;
	t_forks			l;
	pthread_mutex_t	*print;
	pthread_mutex_t	*d_check;
	int				*dead;
	t_data			*data;
}	t_philo;

//philosophers.c

//utils.c
long int		ft_atoi(const char *str);

//time_handle.c
unsigned long	time_ms(void);
unsigned long	time_now(t_philo *p);
int				check_add_death(t_philo *p);
int				check_death(t_philo *p);

//args_check.c
int				is_number(char *str);
void			not_number(int nbr);
void			check_arg_count(int ac);
void			save_args(int ac, char **av, t_data *d);
void			check_args(int ac, char **av, t_data *d);

//init_philos.c
void			create_forks(t_forks	**forks, int n_phil);
void			create_philos(t_philo **p, t_data *d, t_forks **forks, \
				int *dead);

//philo_actions.c
int				philo_eat(t_philo *p);
int				philo_sleep(t_philo *p, unsigned long action);

//print_actions.c
void			print_action_eat(t_philo *p);
void			print_action(t_philo *p, char *message);

//philosophers.c
void			*philo_routine(void *phil);

#endif