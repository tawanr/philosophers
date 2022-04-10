/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 10:52:17 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/10 20:23:08 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_action(t_philo *philo, int action)
{
	int	timestamp;
	int	name;

	name = philo->name;
	timestamp = gettstamp(philo->params->init_time);
	if (action == A_FORK)
		printf(MAG "%8i" RED " %3i" RES " has taken a fork\n", timestamp, name);
	else if (action == A_EAT)
		printf(MAG "%8i" RED " %3i" RES " is eating\n", timestamp, name);
	else if (action == A_SLEEP)
		printf(MAG "%8i" RED " %3i" RES " is sleeping\n", timestamp, name);
	else if (action == A_THINK)
		printf(MAG "%8i" RED " %3i" RES " is thinking\n", timestamp, name);
	else if (action == A_DEAD)
		printf(MAG "%8i" RED " %3i" RES " died\n", timestamp, name);
}
