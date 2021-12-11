/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 20:13:25 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/12/11 18:30:03 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_philo.h"

void	delayer(t_philo *philo)
{
	unsigned int	time_left;

	time_left = philo->param->die_time
		- (update_time(philo->param->begin) - philo->lteat);
	time_left /= 2;
	usleep(time_left);
}

int	init_in_philo(t_philo *philo)
{
	int	phase;

	if ((philo->n - 1) % 2 == 0)
	{
		if ((philo->param->num_philos % 2 != 0
				&& philo->param->num_philos == philo->n))
			phase = 2;
		else
			phase = 0;
	}
	else
		phase = 1;
	philo->eats = 0;
	philo->lteat = update_time(philo->param->begin);
	usleep(philo->n * 10);
	return (phase);
}

void	still_alive(t_philo *philo)
{
	unsigned int	actual;

	actual = update_time(philo->param->begin);
	usleep(philo->n);
	if ((actual - philo->lteat) >= (unsigned)philo->param->die_time
		&& !philo->param->anybody_died)
	{
		philo->param->anybody_died = 1;
		printf("\033[0;31m%ums %d died\n\033[0m", actual, philo->n);
	}
}

void	sleeper(struct timeval ref, unsigned int time)
{
	unsigned int	actual;

	actual = update_time(ref);
	while (time > (update_time(ref) - actual))
		usleep(100);
}

unsigned int	update_time(struct timeval begin)
{
	struct timeval	actual;

	gettimeofday(&actual, NULL);
	return ((actual.tv_sec - begin.tv_sec) * 1000
		+ (actual.tv_usec - begin.tv_usec) / 1000);
}
