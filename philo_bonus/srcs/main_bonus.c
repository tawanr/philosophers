/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 18:20:34 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/24 11:49:07 by tratanat         ###   ########.fr       */
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
	while (!death)
		usleep(50);
	if (!fed && table[0]->params->f >= 0)
		philo_death(table[table[0]->params->f], table[0]->params->init_time);
	kill_table(table, num);
	philo_clean(table, num);
	return (0);
}

t_philo	**philo_birth(t_params *params, int num)
{
	int			name;
	t_philo		**table;

	name = 0;
	params->head_pid = getpid();
	table = (t_philo **)malloc((num) * sizeof(t_philo *));
	params->forks = sem_open("/forks", O_CREAT, 0777, num);
	while (name < num)
	{
		table[name] = philo_create_loop(params, name + 1);
		sem_post(params->forks);
		name++;
	}
	return (table);
}

t_philo	*philo_create_loop(t_params *params, int name)
{
	pthread_t	tid;
	t_philo		*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	philo->name = name;
	philo->eat = 0;
	philo->params = params;
	philo->death = 0;
	philo->fed = 0;
	philo->params = params;
	pthread_create(&tid, NULL, (void *)waitloop, philo);
	return (philo);
}

void	waitloop(t_philo *philo)
{
	pid_t	pid;
	int		status;
	int		exit_code;

	pid = fork();
	if (pid == 0)
		philo_loop(philo, philo->params);
	philo->pid = pid;
	waitpid(pid, &status, 0);
	exit_code = WEXITSTATUS(status);
	if (exit_code == FULL)
		(*philo->params->fed)++;
	if (exit_code == STARVE && philo->params->f < 0)
		philo->params->f = philo->name;
	(*philo->params->death)++;
	return ;
}

void	philo_loop(t_philo *philo, t_params *params)
{
	pthread_t	tid;
	int			it;
	sem_t		*forks;

	(void)params;
	pthread_create(&tid, NULL, (void *)deathcounter, philo);
	forks = sem_open("/forks", 0);
	it = gettime();
	pthread_detach(tid);
	while (!(philo->death))
	{
		sem_wait(forks);
		philo_action(philo, A_FORK, it);
		sem_wait(forks);
		philo->eat = 1;
		philo_action(philo, A_FORK, it);
		philo_action(philo, A_EAT, it);
		usleep(1000 * philo->params->p_tteat);
		sem_post(forks);
		sem_post(forks);
		philo_action(philo, A_SLEEP, it);
		usleep(1000 * philo->params->p_ttsleep);
		philo_action(philo, A_THINK, it);
	}
}
