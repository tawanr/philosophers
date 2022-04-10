/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 08:44:29 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/10 21:30:48 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	isnum(char *str);

t_params	*init_params(int argc, char **argv, int *fed, int *death)
{
	static t_params		params;

	params.p_num = ft_atoi(argv[1]);
	params.p_ttdie = ft_atoi(argv[2]);
	params.p_tteat = ft_atoi(argv[3]);
	params.p_ttsleep = ft_atoi(argv[4]);
	if (argc == 6)
		params.p_numeat = ft_atoi(argv[5]);
	else
		params.p_numeat = 0;
	params.init_time = gettime();
	params.fed = fed;
	params.death = death;
	return (&params);
}

t_philo	*philo_birth(t_params *params, int num, int max)
{
	t_philo	*newphilo;

	if (num > max)
		return (NULL);
	newphilo = (t_philo *)malloc(sizeof(t_philo));
	newphilo->name = num;
	newphilo->tid = 0;
	newphilo->params = params;
	newphilo->eatflag = 0;
	newphilo->deathflag = 0;
	pthread_mutex_init(&(newphilo->rfork), NULL);
	newphilo->next = philo_birth(params, num + 1, max);
	return (newphilo);
}

int	checkargs(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		err_args();
		return (-1);
	}
	while (i < argc)
	{
		if (!isnum(argv[i++]))
		{
			err_args();
			return (-1);
		}
	}
	return (0);
}

static int	isnum(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}
