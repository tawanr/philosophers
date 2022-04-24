/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_fed.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 07:34:49 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/24 09:09:40 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	fed_state(t_philo *philo, int flag)
{
	static t_philo	*philo_state;
	static int		fednum = 0;
	static int		numeat = 0;

	if (flag == 0)
	{
		philo_state = philo;
		numeat = philo_state->params->p_numeat;
	}
	else if (flag == 1)
		fednum++;
	if (numeat != 0 && fednum == numeat)
		kill(philo->params->head_pid, SIGUSR2);
	return (0);
}

void	fedphilo(t_philo **table, int num, int pid, int flag)
{
	static t_philo	**table_state;
	static int		tablesize;
	int				i;

	i = 0;
	if (flag == 0)
	{
		table_state = table;
		tablesize = num;
	}
	else if (flag == 1)
	{
		while (i < tablesize)
		{
			if (table_state[i]->pid == pid)
				break ;
			i++;
		}
		if (table_state[i]->pid == pid)
			table_state[i]->fed = 1;
	}
}
