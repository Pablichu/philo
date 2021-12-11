/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmira-pe <pmira-pe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 20:39:31 by pmira-pe          #+#    #+#             */
/*   Updated: 2021/12/07 18:52:57 by pmira-pe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_philo.h"
#define MINUS_PHILO "Are you -1 person? You exist, that means you are 1\n"

static void	valid_param(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) && argv[i][j] != '+'
				&& argv[i][j] != '-')
				bad_param(argv[i]);
			j++;
		}
		i++;
	}
}

static void	init_param(int argc, char **argv, t_param *param)
{
	valid_param(argc - 1, argv);
	param->num_philos = ft_atoi(argv[0]);
	param->die_time = ft_atoi(argv[1]);
	param->eat_time = ft_atoi(argv[2]);
	param->sleep_time = ft_atoi(argv[3]);
	if (argc == 6)
		param->nb_eat = ft_atoi(argv[4]);
	else
		param->nb_eat = -1;
	if (param->die_time < 1 || param->eat_time < 1
		|| param->sleep_time < 1 || param->num_philos < 1)
	{
		if (param->num_philos < 1)
			printf("%s", MINUS_PHILO);
		else
			printf("Fuck you, no philo\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	t_param	param;

	if (argc == 5 || argc == 6)
	{
		gettimeofday(&param.begin, NULL);
		init_param(argc, argv + 1, &param);
		param.anybody_died = 0;
		philo_loop(&param);
	}
	else
		write(STDOUT_FILENO, "You dumbass didn't put enough arguments\n", 41);
	return (0);
}

/*
	system("leaks philo");
		printf("Filoseros --> %d\n", param.num_philos);
		printf("Hora pa mori --> %d\n", param.die_time);
		printf("Hora pa come --> %d\n", param.eat_time);
		printf("Hora de la puta siesta --> %d\n", param.sleep_time);
		printf("Cuantas veces se come --> %d\n", param.nb_eat);
*/