/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:20:33 by yeju              #+#    #+#             */
/*   Updated: 2021/12/14 18:28:01 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long int	timestamp(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

long long int	time_diff(long long int past, long long int now)
{
	return (now - past);
}

void	take_time(long long int time, t_rules *r)
{
	long long int	func_start_time;

	func_start_time = timestamp();
	while (!(r->dieded))
	{
		if (time_diff(func_start_time, timestamp()) >= time)
			break ;
		usleep(50);
	}
}

void	action_print(t_rules *r, int id, char *str)
{
	pthread_mutex_lock(&(r->print_state));
	if (!(r->dieded))
	{
		printf("%lli ", timestamp() - r->start_time);
		printf("%i ", id + 1);
		printf("%s\n", str);
	}
	pthread_mutex_unlock(&(r->print_state));
	return ;
}

void	exit_start_philo(t_rules *r, t_philosopher *p)
{
	int	i;

	i = 0;
	while (i++ < r->nb_philo)
		pthread_join(p[i].thread_id, NULL);
	i = 0;
	while (i++ < r->nb_philo)
		pthread_mutex_destroy(&(r->forks[i]));
	pthread_mutex_destroy(&(r->print_state));
	pthread_mutex_destroy(&(r->eating));
}
