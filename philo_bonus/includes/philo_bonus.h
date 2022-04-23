/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 08:19:09 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/23 08:35:43 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <fcntl.h>
# include <signal.h>
# include <semaphore.h>
# include <sys/time.h>
# include <sys/types.h>

# define A_FORK 1
# define A_EAT 2
# define A_SLEEP 3
# define A_THINK 4
# define A_DEAD 5

# define RED "\e[1;31m"
# define GRN "\e[1;32m"
# define YEL "\e[1;33m"
# define BLU "\e[1;34m"
# define MAG "\e[1;35m"
# define CYN "\e[1;36m"
# define WHT "\e[1;37m"
# define RES "\e[0m"

typedef struct s_params
{
	unsigned int	p_num;
	unsigned int	p_ttdie;
	unsigned int	p_tteat;
	unsigned int	p_ttsleep;
	unsigned int	p_numeat;
	unsigned int	init_time;
	int				*fed;
	int				*death;
	sem_t			forks;
	pid_t			head_pid;
}	t_params;

typedef struct s_philo
{
	int			name;
	int			eat;
	int			death;
	int			fed;
	t_params	*params;
	pid_t		pid;
}	t_philo;

int				philo_thread(t_philo *table, char *death, int num);
void			philo_loop(t_philo *philo, t_params *params);
void			*deathcounter(t_philo *temp);
void			philo_action(t_philo *philo, int action, int ts);
void			philo_clean(t_philo **table, int num);
void			philo_dying(unsigned int counter, t_philo *philo, int fed);
void			philo_death(t_philo **table, int pid);
int				fed_state(t_philo *philo, int flag);
void			fedphilo(t_philo **table, int num, int pid, int flag);
void			main_counter(t_philo **table, int *death, int num);

// Init Functions Prototypes
t_params		*init_params(int argc, char **argv, int *fed, int *death);
t_philo			**philo_birth(t_params *params, int num);
int				checkargs(int argc, char **argv);

// Time Handling Functions Prototypes
unsigned int	gettime(void);
unsigned int	getts(int init_time);
int				ct(int usec);

// Error Handling Functions Prototypes
void			err_args(void);

// Utility Function Prototypes
int				ft_atoi(const char *str);

// Signal Handling Prototypes
void			init_sighandler(void);
void			init_childhandler(t_philo *philo);
void			sig_handler(int signo, siginfo_t *info, void *other);
void			child_handler(int signo, siginfo_t *info, void *other);
void			child_state(t_philo *philo, int flag);
void			death_state(t_philo **table, int *death, int num, int flag);
void			kill_table(t_philo **table, int total);

#endif