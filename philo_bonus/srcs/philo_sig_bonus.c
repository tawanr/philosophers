/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_sig_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 09:34:05 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/24 08:46:02 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_childhandler(t_philo *philo)
{
	struct sigaction	sa;

	sa.sa_sigaction = child_handler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	child_state(philo, 0);
}

void	sig_handler(int signo, siginfo_t *info, void *other)
{
	(void)other;
	if (signo == SIGUSR1)
		death_state(NULL, NULL, 0, info->si_pid);
	if (signo == SIGUSR2)
		fedphilo(NULL, 0, info->si_pid, 1);
}

void	child_handler(int signo, siginfo_t *info, void *other)
{
	(void)info;
	(void)other;
	if (signo == SIGUSR1)
	{
		if (fed_state(NULL, 2))
			kill(info->si_pid, SIGUSR2);
	}
	else if (signo == SIGUSR2)
		child_state(NULL, 1);
}

void	child_state(t_philo *philo, int flag)
{
	static t_philo	*philo_state;

	if (flag == 0)
		philo_state = philo;
	else if (flag == 1)
	{
		philo_state->death++;
		free(philo_state);
		exit(0);
	}
	return ;
}

void	death_state(t_philo **table, int *death, int num, int flag)
{
	static t_philo	**table_state;
	static int		*death_state;
	static int		total;
	static int		fed = 0;

	if (flag == 0)
	{
		table_state = table;
		death_state = death;
		total = num;
	}
	else if (flag == -1)
	{
		fed++;
		if (fed == total)
			kill_table(table_state, total);
		(*death_state)++;
	}
	else if (flag > 0 && !(*death_state))
	{
		philo_death(table_state, flag);
		kill_table(table_state, total);
		(*death_state)++;
	}
}
