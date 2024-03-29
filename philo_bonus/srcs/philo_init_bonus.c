/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 08:44:29 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/24 11:30:25 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	params.f = -1;
	return (&params);
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

int	ct(int usec)
{
	return (usec / 1000);
}
