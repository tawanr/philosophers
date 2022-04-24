/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cleanup_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 09:10:16 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/24 09:10:31 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_table(t_philo **table, int total)
{
	int	i;

	i = 0;
	while (i < total)
		kill(table[i++]->pid, SIGUSR2);
}
