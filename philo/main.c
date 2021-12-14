/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeju <yeju@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 17:19:57 by yeju              #+#    #+#             */
/*   Updated: 2021/12/14 17:06:15 by yeju             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_error(char *str)
{
	write(1, str, 6);
	return (1);
}

int	main(int argc, char **argv)
{
	t_rules	rules;
	int		check_error;

	if (argc != 5 && argc != 6)
		return (print_error("Error\n"));
	check_error = init_all(&rules, argv);
	if (check_error)
		return (print_error("Error\n"));
	if (start_philo(&rules))
		return (print_error("Error\n"));
	return (0);
}
