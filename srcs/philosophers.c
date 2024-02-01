/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 01:13:44 by pmira-pe          #+#    #+#             */
/*   Updated: 2024/02/01 19:49:39 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_philo.h"

static void	where_are_my_forks(t_philo *philo)
{
	int	can_eat;

	can_eat = 0;
	while (1)
	{
		delayer(philo);
		pthread_mutex_lock(&philo->param->fmutex[philo->lfork]);
		pthread_mutex_lock(&philo->param->fmutex[philo->rfork]);
		if (philo->param->forks[philo->lfork]
			&& philo->param->forks[philo->rfork])
		{
			philo->param->forks[philo->lfork] = 0;
			philo->param->forks[philo->rfork] = 0;
			can_eat = 1;
		}
		pthread_mutex_unlock(&philo->param->fmutex[philo->lfork]);
		pthread_mutex_unlock(&philo->param->fmutex[philo->rfork]);
		still_alive(philo);
		if (can_eat || philo->param->anybody_died)
			break ;
	}
}

static void	eating(t_philo *philo)
{
	if (philo->param->num_philos == 1)
	{
		sleeper(philo->param->begin, (unsigned)philo->param->die_time);
		still_alive(philo);
		return ;
	}
	where_are_my_forks(philo);
	if (!philo->param->anybody_died)
	{
		philo->lteat = update_time(philo->param->begin);
		printf("\033[0;32m%ums %d is eating\n\033[0m",
			update_time(philo->param->begin), philo->n);
		sleeper(philo->param->begin, (unsigned)philo->param->eat_time);
	}
	if (!philo->param->anybody_died)
	{
		pthread_mutex_lock(&philo->param->fmutex[philo->lfork]);
		pthread_mutex_lock(&philo->param->fmutex[philo->rfork]);
		philo->param->forks[philo->lfork] = 1;
		philo->param->forks[philo->rfork] = 1;
		pthread_mutex_unlock(&philo->param->fmutex[philo->lfork]);
		pthread_mutex_unlock(&philo->param->fmutex[philo->rfork]);
	}
	philo->eats++;
}

static void	sleeping(t_philo *philo)
{
	if (philo->param->sleep_time
		>= (philo->param->die_time - philo->param->eat_time))
	{
		printf("\033[0;34m%ums %d is sleeping\n\033[0m",
			update_time(philo->param->begin), philo->n);
		sleeper(philo->param->begin, (unsigned)philo->param->die_time);
		still_alive(philo);
	}
	else if (!philo->param->anybody_died)
	{
		printf("\033[0;34m%ums %d is sleeping\n\033[0m",
			update_time(philo->param->begin), philo->n);
		sleeper(philo->param->begin, (unsigned)philo->param->sleep_time);
	}
}

void	thinking(t_philo *philo)
{
	still_alive(philo);
	if (!philo->param->anybody_died)
		printf("\033[0;33m%ums %d is thinking\n\033[0m",
			update_time(philo->param->begin), philo->n);
}

void	*philosopher(void *args)
{
	t_philo	*philo;
	int		phase;

	philo = (t_philo *)args;
	phase = init_in_philo(philo);
	while (1)
	{
		if (!phase)
			eating(philo);
		else if (phase == 1 && !philo->param->anybody_died)
			sleeping(philo);
		else
			thinking(philo);
		phase++;
		if (phase == 3)
			phase = 0;
		if (philo->param->anybody_died || (philo->eats == philo->param->nb_eat))
			break ;
	}
	return (NULL);
}
