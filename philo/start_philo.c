/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:20:08 by yeju              #+#    #+#             */
/*   Updated: 2021/12/14 18:21:55 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*handle_thread(void *p_temp)
{
	t_philosopher	*p;
	t_rules			*r;

	p = (t_philosopher *)p_temp;
	r = p->rules;
	if (p->id % 2)
		usleep(10000);
	while (!(r->dieded))
	{
		philo_eats(p);
		if (r->all_ate)
			break ;
		action_print(r, p->id, "is sleeping");
		take_time(r->time_sleep, r);
		action_print(r, p->id, "is thinking");
	}
	return (NULL);
}

void	check_death(t_rules *r, t_philosopher *p)
{
	int	i;

	while (!(r->all_ate))
	{
		i = 0;
		while (i < r->nb_philo && !(r->dieded))
		{
			pthread_mutex_lock(&(r->eating));
			if (time_diff(p[i].last_eat, timestamp()) > r->time_die)
			{
				action_print(r, i, "died");
				r->dieded = 1;
			}
			pthread_mutex_unlock(&(r->eating));
			usleep(100);
			i++;
		}
		if (r->dieded)
			break ;
		i = 0;
		while (i < r->nb_philo && r->to_eat != -1 && p[i].nb_ate >= r->to_eat)
			i++;
		if (i == r->nb_philo)
			r->all_ate = 1;
	}
}

void	philo_eats(t_philosopher *p)
{
	t_rules	*r;

	r = p->rules;
	pthread_mutex_lock(&(r->forks[p->left_fork_id]));
	action_print(r, p->id, "has taken a fork");
	pthread_mutex_lock(&(r->forks[p->right_fork_id]));
	action_print(r, p->id, "has taken a fork");
	pthread_mutex_lock(&(r->eating));
	action_print(r, p->id, "is eating");
	p->last_eat = timestamp();
	pthread_mutex_unlock(&(r->eating));
	take_time(r->time_eat, r);
	(p->nb_ate)++;
	pthread_mutex_unlock(&(r->forks[p->left_fork_id]));
	pthread_mutex_unlock(&(r->forks[p->right_fork_id]));
}

int	start_philo(t_rules *r)
{
	int				i;
	t_philosopher	*p;

	i = 0;
	p = r->philosophers;
	r->start_time = timestamp();
	while (i < r->nb_philo)
	{
		if (pthread_create(&(p[i].thread_id), NULL, handle_thread, &(p[i])))
			return (1);
		p[i].last_eat = timestamp();
		i++;
	}
	check_death(r, r->philosophers);
	exit_start_philo(r, p);
	return (0);
}
