/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:20:34 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/24 09:11:26 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

// static int	checkend(t_philo **table, int num);

int	main(int argc, char **argv)
{
	t_philo	**table;
	int		num;
	int		death;
	int		fed;

	fed = 0;
	death = 0;
	if (checkargs(argc, argv))
		return (-1);
	num = ft_atoi(argv[1]);
	table = philo_birth(init_params(argc, argv, &fed, &death), num);
	init_sighandler();
	death_state(table, &death, num, 0);
	fedphilo(table, num, 0, 0);
	main_counter(table, &death, num);
	death++;
	usleep(5000);
	philo_clean(table, num);
	return (0);
}

t_philo	**philo_birth(t_params *params, int num)
{
	int		name;
	t_philo	**table;
	pid_t	pid;

	name = 0;
	params->head_pid = getpid();
	table = (t_philo **)malloc((num) * sizeof(t_philo *));
	sem_init(&params->forks, 1, num);
	while (name < num)
	{
		table[name] = (t_philo *)malloc(sizeof(t_philo));
		table[name]->name = name + 1;
		table[name]->eat = 0;
		table[name]->params = params;
		table[name]->death = 0;
		table[name]->fed = 0;
		pid = fork();
		if (pid == 0)
			break ;
		table[name]->pid = pid;
		name++;
	}
	if (pid == 0)
		philo_create_loop(table[name], params);
	return (table);
}

void	philo_create_loop(t_philo *philo, t_params *params)
{
	pid_t	pid;
	pid_t	int_pid;

	int_pid = getpid();
	pid = fork();
	if (pid == 0)
	{
		philo->params->head_pid = int_pid;
		philo_loop(philo, params);
	}
	signal_direction(philo, 0, 0, 0);
	philo->pid = pid;
	philo_buffer_state();
	while (!buffer_state(-1))
		usleep(5000);
	exit(0);
}

void	philo_loop(t_philo *philo, t_params *params)
{
	pthread_t	tid;
	int			it;

	pthread_create(&tid, NULL, (void *)deathcounter, philo);
	init_childhandler(philo);
	it = gettime();
	pthread_detach(tid);
	while (!(philo->death))
	{
		sem_wait(&params->forks);
		philo_action(philo, A_FORK, it);
		sem_wait(&params->forks);
		philo->eat = 1;
		philo_action(philo, A_FORK, it);
		philo_action(philo, A_EAT, it);
		usleep(1000 * philo->params->p_tteat);
		sem_post(&params->forks);
		sem_post(&params->forks);
		philo_action(philo, A_SLEEP, it);
		usleep(1000 * philo->params->p_ttsleep);
		philo_action(philo, A_THINK, it);
	}
	while (!philo->death)
		usleep(1000);
	exit(0);
}
