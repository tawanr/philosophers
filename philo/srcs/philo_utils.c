/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 09:16:08 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/10 12:06:34 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	gettime(void)
{
	struct timeval	tv;
	int				time;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	time = tv.tv_sec % 1000 * 1000;
	time += tv.tv_usec / 1000;
	return (time);
}

unsigned int	gettstamp(int init_time)
{
	int	now;

	now = gettime();
	return (now - init_time);
}
