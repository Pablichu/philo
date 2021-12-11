/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 17:34:56 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/12/07 18:48:38 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_philo.h"

static void	philo_free(t_philo *philo)
{
	int	i;

	i = -1;
	while ((*philo).param->num_philos > ++i)
		pthread_mutex_destroy(&(*philo).param->fmutex[i]);
	free((*philo).param->fmutex);
	free((*philo).param->forks);
	free(philo);
}

static t_philo	*init_philo(t_param *param)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(param->num_philos * sizeof(t_philo));
	param->fmutex = (pthread_mutex_t *)malloc(param->num_philos
			* sizeof(pthread_mutex_t));
	param->forks = (int *)malloc(param->num_philos * sizeof(int) + 1);
	if (!(philo) || !param->fmutex || !param->forks)
		printf("Malloc has fail!!\n");
	memset(param->forks, 1, param->num_philos * sizeof(int));
	param->forks[param->num_philos + 1] = 0;
	return (philo);
}

static t_philo	*philo_born(t_param *param)
{
	int		i;
	t_philo	*philo;

	philo = init_philo(param);
	i = -1;
	while (param->num_philos > ++i)
		pthread_mutex_init(&param->fmutex[i], NULL);
	i = 0;
	while (param->num_philos > i)
	{
		philo[i].n = i + 1;
		philo[i].lfork = i;
		if ((i + 1) == param->num_philos)
			philo[i].rfork = 0;
		else
			philo[i].rfork = (i + 1);
		philo[i].param = param;
		i++;
	}
	return (philo);
}

void	philo_loop(t_param *param)
{
	int		i;
	t_philo	*philo;

	philo = philo_born(param);
	i = 0;
	while (param->num_philos > i)
	{
		pthread_create(&philo[i].h, NULL, philosopher, &(philo[i]));
		i++;
	}
	i = -1;
	while (param->num_philos > ++i)
		pthread_join(philo[i].h, NULL);
	philo_free(philo);
}
