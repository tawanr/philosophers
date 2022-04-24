/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fed_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 06:55:55 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/24 09:05:56 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_buffer_state(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = buffer_handler;
	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

void	buffer_handler(int signo, siginfo_t *info, void *other)
{
	(void)other;
	signal_direction(NULL, signo, info->si_pid, 1);
}

void	signal_direction(t_philo *philo, int signo, int pid, int flag)
{
	static t_philo	*philo_state;
	static pid_t	child;

	if (flag == 0)
	{
		child = philo->pid;
		philo_state = philo;
	}
	else if (signo == SIGUSR2 && pid == philo_state->params->head_pid)
	{
		buffer_state(1);
		kill(child, SIGUSR2);
	}
	else if (signo == SIGUSR1 && pid == philo_state->params->head_pid)
	{
		if (buffer_state(-2))
			kill(philo_state->params->head_pid, SIGUSR2);
	}
	else if (signo == SIGUSR1)
	{
		kill(philo_state->params->head_pid, SIGUSR1);
		buffer_state(1);
	}
	else if (signo == SIGUSR2)
		buffer_state(2);
}

int	buffer_state(int flag)
{
	static int		death = 0;
	static int		fed = 0;

	if (flag == -1)
		return (death);
	else if (flag == -2)
		return (fed);
	else if (flag == 1)
		death = 1;
	else if (flag == 2)
		fed = 1;
	return (0);
}
