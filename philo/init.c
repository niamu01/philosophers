/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:20:18 by yeju              #+#    #+#             */
/*   Updated: 2021/12/14 18:27:47 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_mutex(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	while (i--)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(rules->print_state), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->eating), NULL))
		return (1);
	return (0);
}

int	init_philo(t_rules *rules)
{
	int	i;

	i = rules->nb_philo;
	while (i--)
	{
		rules->philosophers[i].id = i;
		rules->philosophers[i].nb_ate = 0;
		rules->philosophers[i].left_fork_id = i;
		rules->philosophers[i].right_fork_id = (i + 1) % rules->nb_philo;
		rules->philosophers[i].last_eat = 0;
		rules->philosophers[i].rules = rules;
	}
	return (0);
}

int	init_all(t_rules *rules, char **argv)
{
	rules->nb_philo = ft_atoi(argv[1]);
	rules->time_die = ft_atoi(argv[2]);
	rules->time_eat = ft_atoi(argv[3]);
	rules->time_sleep = ft_atoi(argv[4]);
	rules->all_ate = 0;
	rules->dieded = 0;
	if (rules->nb_philo < 0 || 200 < rules->nb_philo || rules->time_die < 0
		||rules->time_eat < 0 || rules->time_sleep < 0)
		return (1);
	if (argv[5])
	{
		rules->to_eat = ft_atoi(argv[5]);
		if (rules->to_eat < 1)
			return (1);
	}
	else
		rules->to_eat = -1;
	if (init_mutex(rules))
		return (1);
	init_philo(rules);
	return (0);
}
