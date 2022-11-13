/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:46:42 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/13 20:49:45 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
// COMMENT FOR COMPIL : gcc -g -pthread main.c"

typedef struct s_philo
{
	pthread_t		*tab_philo;
	pthread_mutex_t	is_dead;
	pthread_mutex_t *fork;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	r_fork;
	long			time_for_dead;
	long			time_for_eat;
	long			time_for_sleep;
	int				last_meal;
	
}t_philo;


typedef	struct	s_all 
{
			
	t_philo			philo;
	int				num_philo;
	useconds_t		time_act;
	useconds_t		time_start;
	struct timeval	timeval;
	int				num_fork;
	int				actual_philo;
	int				first_round;
	/* data */
}t_all;


#endif