/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 08:12:05 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/10 20:33:10 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_loop(t_philo *head);

int	main(int argc, char **argv)
{
	t_philo		*table;
	int			num;
	char		death;
	int			fed;

	fed = 0;
	if (checkargs(argc, argv))
		return (-1);
	num = ft_atoi(argv[1]);
	table = philo_birth(init_params(argc, argv, &fed), 1, num);
	philo_loop(table);
	memset(&death, 0, 1);
	if (philo_thread(table, &death, num))
		return (-1);
	while (fed < num || table->params->p_numeat == 0)
		usleep(1000);
	return (0);
}

static void	philo_loop(t_philo *head)
{
	t_philo	*temp;

	temp = head;
	while (temp->next)
		temp = temp->next;
	if (temp->next == NULL)
		temp->next = head;
}

int	philo_thread(t_philo *table, char *death, int num)
{
	t_philo		*temp;
	pthread_t	*tid;
	int			i;

	(void)death;
	temp = table;
	i = 0;
	while (i < num)
	{
		tid = (pthread_t *)malloc(sizeof(pthread_t));
		temp->tid = tid;
		if (pthread_create(tid, NULL, philo_patt, (void *)temp))
			return (-1);
		temp = temp->next;
		free(tid);
		i++;
	}
	return (0);
}

void	*philo_patt(void *temp)
{
	t_philo		*philo;
	pthread_t	tid;

	philo = (t_philo *)temp;
	if (pthread_create(&tid, NULL, (void *)deathcounter, temp))
		return (NULL);
	pthread_detach(tid);
	while (1)
	{
		pthread_mutex_lock(&philo->rfork);
		philo_action(philo, A_FORK);
		pthread_mutex_lock(&philo->next->rfork);
		philo_action(philo, A_FORK);
		philo->eatflag = 1;
		philo_action(philo, A_EAT);
		usleep(1000 * philo->params->p_tteat);
		pthread_mutex_unlock(&philo->rfork);
		pthread_mutex_unlock(&philo->next->rfork);
		philo_action(philo, A_SLEEP);
		usleep(1000 * philo->params->p_ttsleep);
		philo_action(philo, A_THINK);
	}
}

void	*deathcounter(t_philo *philo)
{
	unsigned int	counter;
	unsigned int	last;
	unsigned int	fed;
	int				full;

	counter = 0;
	fed = 0;
	full = 0;
	while (counter < philo->params->p_ttdie)
	{
		usleep(100);
		if (philo->eatflag == 1)
		{
			last = gettstamp(philo->params->init_time);
			fed++;
			if (philo->params->p_numeat != 0)
				if (fed >= philo->params->p_numeat && !full)
					full = !!(++(*philo->params->fed));
			philo->eatflag = 0;
		}
		counter = gettstamp(philo->params->init_time) - last;
	}
	philo_action(philo, A_DEAD);
	exit(1);
}
