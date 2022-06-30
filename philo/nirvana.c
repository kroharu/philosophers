/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nirvana.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ladrian <ladrian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 13:48:33 by ladrian           #+#    #+#             */
/*   Updated: 2022/06/01 13:50:08 by ladrian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bit_ili_ne_bit.h"

static t_bool	forkhunter(t_phela *phela, pthread_mutex_t **first,
	pthread_mutex_t **second, struct timeval *tp)
{
	*first = &phela->meta->forks[phela->id
		* (phela->id != phela->meta->numphelas)];
	if (phela->id % 2)
		*first = &phela->meta->forks[phela->id - 1];
	pthread_mutex_lock(*first);
	logger(tp, phela, FORK);
	while (phela->meta->numphelas == 1)
		;
	*second = &phela->meta->forks[phela->id - 1];
	if (phela->id % 2)
		*second = &phela->meta->forks[phela->id
			* (phela->id != phela->meta->numphelas)];
	pthread_mutex_lock(*second);
	if (phela->lastmeal >= phela->meta->lifetime)
	{
		pthread_mutex_unlock(*first);
		pthread_mutex_unlock(*second);
		return (TRUE);
	}
	logger(tp, phela, FORK);
	return (FALSE);
}

static void	timemachine(int sleeptime)
{
	struct timeval	tp[2];

	gettimeofday(&tp[0], NULL);
	usleep(sleeptime * 1000 * 95 / 100);
	gettimeofday(&tp[1], NULL);
	while ((tp[1].tv_sec - tp[0].tv_sec) * 1000 + tp[1].tv_usec / 1000
		- tp[0].tv_usec / 1000 < sleeptime)
	{
		usleep(100);
		gettimeofday(&tp[1], NULL);
	}
}

static t_bool	jrat(t_phela *phela, struct timeval *tp)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	if (forkhunter(phela, &first, &second, tp))
		return (TRUE);
	logger(tp, phela, EAT);
	phela->kushoet = TRUE;
	timemachine(phela->meta->eattime);
	phela->lastmeal = 0;
	phela->kushoet = FALSE;
	phela->eatcount++;
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	return (FALSE);
}

void	*what_a_wonderful_life(void *arg)
{
	t_phela			*phela;
	struct timeval	tp;

	phela = (t_phela *)arg;
	phela->lastmeal = 0;
	phela->eatcount = 0;
	while (!phela->meta->ad)
		;
	while (1)
	{
		if ((phela->meta->appocalipsis
				|| phela->lastmeal >= phela->meta->lifetime))
			break ;
		logger(&tp, phela, THINK);
		if (jrat(phela, &tp))
			break ;
		logger(&tp, phela, SLEEP);
		timemachine(phela->meta->sleeptime);
	}
	pthread_mutex_lock(&phela->meta->matyugalnik);
	phela->meta->dvuhsotiye++;
	pthread_mutex_unlock(&phela->meta->matyugalnik);
	return (NULL);
}
