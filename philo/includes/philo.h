/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 08:19:09 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/11 00:28:10 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <fcntl.h>
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
}	t_params;

typedef struct s_philo
{
	int				name;
	int				eatflag;
	int				deathflag;
	pthread_t		tid;
	t_params		*params;
	pthread_mutex_t	rfork;
	struct s_philo	*next;
}	t_philo;

int				philo_thread(t_philo *table, int *death, int num);
void			*philo_patt(t_philo *temp);
void			*deathcounter(t_philo *temp);
void			philo_action(t_philo *philo, int action, int ts);
void			philo_death(t_philo *philo);
void			philo_clean(t_philo *philo);
void			philo_dying(unsigned int counter, t_philo *philo, int fed);
int				checkdead(t_philo *philo, int num);

// Init Functions Prototypes
t_params		*init_params(int argc, char **argv, int *fed, int *death);
t_philo			*philo_birth(t_params *params, int num, int max);
int				checkargs(int argc, char **argv);

// Time Handling Functions Prototypes
unsigned int	gettime(void);
unsigned int	getts(int init_time);

// Error Handling Functions Prototypes
void			err_args(void);

// Utility Function Prototypes
int				ft_atoi(const char *str);

#endif