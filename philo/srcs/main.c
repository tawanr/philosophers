/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tratanat <tawan.rtn@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 08:12:05 by tratanat          #+#    #+#             */
/*   Updated: 2022/04/11 01:21:05 by tratanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_loop(t_philo *head);

int	main(int argc, char **argv)
{
	t_philo		*table;
	int			num;
	int			death;
	int			fed;

	fed = 0;
	death = 0;
	if (checkargs(argc, argv))
		return (-1);
	num = ft_atoi(argv[1]);
	table = philo_birth(init_params(argc, argv, &fed, &death), 1, num);
	philo_loop(table);
	memset(&death, 0, 1);
	printf("numeat: %i\n", table->params->p_numeat);
	if (philo_thread(table, &death, num))
		return (-1);
	while (!checkdead(table, num))
	{
		if (table->params->p_numeat > 0 && fed >= num)
			table->params->p_ttdie = 0;
		usleep(1000);
	}
	usleep(5000);
	philo_clean(table);
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

int	philo_thread(t_philo *table, int *death, int num)
{
	t_philo		*temp;
	pthread_t	tid;
	int			i;

	(void)death;
	temp = table;
	i = 0;
	while (i < num)
	{
		if (pthread_create(&tid, NULL, (void *)philo_patt, temp))
			return (-1);
		usleep(25);
		pthread_detach(tid);
		temp->tid = tid;
		temp = temp->next;
		i++;
	}
	return (0);
}

void	*philo_patt(t_philo *philo)
{
	pthread_t	tid;
	int			it;

	if (pthread_create(&tid, NULL, (void *)deathcounter, philo))
		return (NULL);
	pthread_detach(tid);
	it = philo->params->init_time;
	while (!(*philo->params->death))
	{
		pthread_mutex_lock(&philo->rfork);
		philo_action(philo, A_FORK, it);
		pthread_mutex_lock(&philo->next->rfork);
		philo->eatflag = 1;
		philo_action(philo, A_FORK, it);
		philo_action(philo, A_EAT, it);
		usleep(1000 * philo->params->p_tteat);
		pthread_mutex_unlock(&philo->rfork);
		pthread_mutex_unlock(&philo->next->rfork);
		philo_action(philo, A_SLEEP, it);
		usleep(1000 * philo->params->p_ttsleep);
		philo_action(philo, A_THINK, it);
	}
	(*philo->params->death)++;
	philo->deathflag = 1;
	return (NULL);
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
	last = 0;
	while (counter < philo->params->p_ttdie * 1000 && !*(philo->params->death))
	{
		usleep(100);
		if (philo->eatflag == 1)
		{
			last = getts(philo->params->init_time);
			fed++;
			if (philo->params->p_numeat != 0)
				if (fed >= philo->params->p_numeat && !full)
					full = !!(++(*philo->params->fed));
			philo->eatflag = 0;
		}
		counter = getts(philo->params->init_time) - last;
	}
	philo_dying(counter, philo, fed);
	return (NULL);
}
