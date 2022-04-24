/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_counter_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 09:10:57 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/24 09:11:24 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	main_counter(t_philo **table, int *death, int num)
{
	int	i;

	i = 0;
	while (!(*death))
	{
		usleep(5000);
		if (i >= num)
			break ;
		if (!table[i]->fed)
			kill(table[i]->pid, SIGUSR1);
		else
			i++;
	}
	if (i >= num)
		kill_table(table, num);
	return ;
}

void	*deathcounter(t_philo *philo)
{
	unsigned int	counter;
	unsigned int	last;

	counter = 0;
	last = 0;
	fed_state(philo, 0);
	while (counter < philo->params->p_ttdie * 1000 && !*(philo->params->death))
	{
		usleep(100);
		if (philo->eat == 1)
		{
			last = getts(philo->params->init_time);
			fed_state(philo, 1);
			philo->eat = 0;
		}
		counter = getts(philo->params->init_time) - last;
	}
	philo_dying(counter, philo, 0);
	return (NULL);
}
