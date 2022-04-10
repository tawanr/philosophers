/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 09:16:08 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/11 01:24:38 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	gettime(void)
{
	struct timeval	tv;
	int				time;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	time = tv.tv_sec % 1000 * 1000000;
	time += tv.tv_usec;
	return (time);
}

unsigned int	getts(int init_time)
{
	int	now;

	now = gettime();
	return (now - init_time);
}

void	philo_clean(t_philo *philo)
{
	unsigned int	i;
	t_philo			*temp;
	unsigned int	num;

	i = 0;
	num = philo->params->p_num;
	while (i++ < num)
	{
		temp = philo;
		if (i < num)
			philo = philo->next;
		pthread_mutex_destroy(&philo->rfork);
		free(temp);
	}
}

void	philo_dying(unsigned int counter, t_philo *philo, int fed)
{
	unsigned int	ttdie;
	int				numeat;
	int				full;

	ttdie = philo->params->p_ttdie;
	numeat = philo->params->p_numeat;
	if (numeat > 0)
		full = fed >= numeat;
	else
		full = 0;
	if (counter >= ttdie && !*(philo->params->death) && !full)
	{
		(*philo->params->death)++;
		philo->deathflag = 1;
		philo_death(philo);
	}
	else
	{
		(*philo->params->death)++;
		philo->deathflag = 1;
		pthread_mutex_unlock(&philo->rfork);
		pthread_mutex_unlock(&philo->next->rfork);
	}
}

void	philo_death(t_philo *philo)
{
	int	timestamp;
	int	name;

	name = philo->name;
	timestamp = getts(philo->params->init_time);
	philo->deathflag = 1;
	usleep(100);
	printf("%8i" RED " %3i" RES " has died\n", ct(timestamp), name);
	pthread_mutex_unlock(&philo->rfork);
}
