/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_counter_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 09:10:57 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/24 11:20:33 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*deathcounter(t_philo *philo)
{
	unsigned int	counter;
	unsigned int	last;
	unsigned int	fed;

	counter = 0;
	last = 0;
	fed = 0;
	while (counter < philo->params->p_ttdie * 1000 && !*(philo->params->death))
	{
		usleep(100);
		if (philo->eat == 1)
		{
			last = getts(philo->params->init_time);
			fed++;
			if (fed == philo->params->p_numeat)
				exit(FULL);
			philo->eat = 0;
		}
		counter = getts(philo->params->init_time) - last;
	}
	philo_dying(counter, philo, 0);
	exit(STARVE);
}
