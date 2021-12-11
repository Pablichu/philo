/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_philo.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:44:12 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/12/10 21:43:07 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef H_PHILO_H
# define H_PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_param
{
	int				num_philos;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				nb_eat;

	int				anybody_died;
	struct timeval	begin;
	pthread_mutex_t	*fmutex;
	int				*forks;
}				t_param;

typedef struct s_philo
{
	int				n;
	pthread_t		h;
	int				eats;
	int				lfork;
	int				rfork;
	unsigned int	lteat;
	t_param			*param;
}				t_philo;

void			*philosopher(void *args);
void			philo_loop(t_param *param);
int				init_in_philo(t_philo *philo);

void			delayer(t_philo *philo);
void			still_alive(t_philo *philo);
unsigned int	update_time(struct timeval begin);
void			sleeper(struct timeval ref, unsigned int time);

int				ft_isspace(int c);
int				ft_isdigit(int c);
int				ft_atoi(const char *str);

void			bad_param(char *s);
#endif