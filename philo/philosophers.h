#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

struct	s_rules;

typedef struct s_philosopher
{
	int					id;
	int					nb_ate;
	long long int		last_eat;
	int					left_fork_id;
	int					right_fork_id;
	struct s_rules		*rules;
	pthread_t			thread_id;
}						t_philosopher;

typedef struct s_rules
{
	int					nb_philo;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					to_eat;
	int					dieded;
	int					all_ate;
	long long int		start_time;
	pthread_mutex_t		eating;
	pthread_mutex_t		print_state;
	pthread_mutex_t		forks[250];
	t_philosopher		philosophers[250];
}						t_rules;

int				print_error(char *str);

int				init_all(t_rules *rules, char **argv);
int				init_philo(t_rules *rules);
int				init_mutex(t_rules *rules);

int				start_philo(t_rules *rules);
void			check_death(t_rules *rules, t_philosopher *philo);
void			*handle_thread(void *philo_temp);
void			exit_start_philo(t_rules *rules, t_philosopher *philo);

long long int	timestamp(void);
long long int	time_diff(long long int past, long long int now);
void			take_time(long long int time, t_rules *rules);
void			action_print(t_rules *rules, int id, char *str);
void			philo_eats(t_philosopher *philo);

int				ft_atoi(const char *str);

#endif
