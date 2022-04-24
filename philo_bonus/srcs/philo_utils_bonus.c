/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 09:16:08 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/24 11:50:04 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		(*(philo->params->death))++;
	else
	{
		(*(philo->params->death))++;
		sem_post(philo->params->forks);
		sem_post(philo->params->forks);
	}
	philo->death = 1;
}

void	philo_death(t_philo *philo, int timestamp)
{
	int	name;

	name = philo->name;
	philo->death = 1;
	usleep(500);
	printf("%8i" RED " %3i" RES " has died\n", ct(getts(timestamp)), name);
	sem_post(philo->params->forks);
	sem_post(philo->params->forks);
}
