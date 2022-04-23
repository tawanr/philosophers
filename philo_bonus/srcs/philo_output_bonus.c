/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_output_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 10:52:17 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/22 09:08:06 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	philo_action(t_philo *philo, int action, int ts)
{
	int	name;

	name = philo->name;
	if (action == A_FORK && !*(philo->params->death))
		printf("%8i" RED " %3i" RES " has taken a fork\n", ct(getts(ts)), name);
	else if (action == A_EAT && !*(philo->params->death))
		printf("%8i" RED " %3i" RES " is eating\n", ct(getts(ts)), name);
	else if (action == A_SLEEP && !*(philo->params->death))
		printf("%8i" RED " %3i" RES " is sleeping\n", ct(getts(ts)), name);
	else if (action == A_THINK && !*(philo->params->death))
		printf("%8i" RED " %3i" RES " is thinking\n", ct(getts(ts)), name);
	else if (action == A_DEAD && !*(philo->params->death))
		printf("%8i" RED " %3i" RES " died\n", ct(getts(ts)), name);
}
