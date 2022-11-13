/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dojannin <dojannin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:45:23 by dojannin          #+#    #+#             */
/*   Updated: 2022/11/13 20:53:24 by dojannin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *s)
{
	int	i;
	int	res;
	int	sign;
	// int	new_res;

	i = 0;
	sign = 1;
	res = 0;
	// new_res = 0;
	while (s[i] == '\f' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\v' || s[i] == ' ')
		i++;
	while (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign *= (-1);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		// new_res = res * 10 - (s[i] - '0');
		// if (new_res > res)
		// {
		// 	write(1, "Error\n", 6);
		// 	exit(1);
		// }
		// res = new_res;
		i++;
	}
	// res = do_atoi(s, i, res, new_res);
	// error_atoi(sign, res);
	return (res * sign);
}

int	ft_atol(char const *s)
{
	int	i;
	long	res;
	long	sign;
	// int	new_res;

	i = 0;
	sign = 1;
	res = 0;
	// new_res = 0;
	while (s[i] == '\f' || s[i] == '\t' || s[i] == '\n'
		|| s[i] == '\r' || s[i] == '\v' || s[i] == ' ')
		i++;
	while (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign *= (-1);
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		res = res * 10 + (s[i] - '0');
		// new_res = res * 10 - (s[i] - '0');
		// if (new_res > res)
		// {
		// 	write(1, "Error\n", 6);
		// 	exit(1);
		// }
		// res = new_res;
		i++;
	}
	// res = do_atoi(s, i, res, new_res);
	// error_atoi(sign, res);
	return (res * sign);
}

int	do_atoi(char const *s, int i, int res, int new_res)
{	
	while (s[i] >= '0' && s[i] <= '9')
	{
		new_res = res * 10 + (s[i] - '0');
		if (new_res > res)
		{
			write(1, "Error\n", 6);
			exit(1);
		}
		res = new_res;
		i++;
	}
	return (res);
}

void	error_atoi(int sign, int res)
{
	if (sign == 1 && res == -2147483648)
	{
		write(1, "Error\n", 6);
		exit(1);
	}
}

pthread_t	*tab_thread(pthread_t *tab, int	nombre)
{
	tab = (pthread_t *)malloc(sizeof(pthread_t) * nombre);
	return (tab);
}

useconds_t	philo_get_time(void);

void	parsing(char **av, t_all *all)
{
	int	i;

	i = 0;
	gettimeofday(&all->timeval, NULL);
	// printf("seconds : %ld micro seconds : %d\n", all->timeval.tv_sec, all->timeval.tv_usec);
	all->num_philo = ft_atoi(av[1]);
	if (all->num_philo < 0)
	{
		printf("Error: Number's Philos is negative.\n");
		return ;
	}
	all->philo.tab_philo = tab_thread(all->philo.tab_philo, all->num_philo);
	all->philo.time_for_dead = ft_atol(av[2]);
	printf("all->philo.time_for_dead == %ld\n", all->philo.time_for_dead);
	all->philo.time_for_eat = ft_atol(av[3]);
	all->philo.time_for_sleep = ft_atol(av[4]);
	if (av[5])
		all->philo.last_meal = ft_atoi(av[5]);
	else
		all->philo.last_meal = -1;
	all->num_fork = ft_atoi(av[1]);
	all->time_start = philo_get_time();
	all->actual_philo = 0;
	all->first_round = 1;
	pthread_mutex_init(&all->philo.left_fork, NULL);
	pthread_mutex_init(&all->philo.r_fork, NULL);
	printf("jamais vu\n");
}

// long	get_time(void)
// {
// 	struct timeval	tv;
// 	long			end;

// 	gettimeofday(&tv, NULL);
// 	end = ((tv.tv_sec * 1000) + tv.tv_usec / 1000);
// 	return (end);
// }

useconds_t	philo_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	ft_usleep(useconds_t usec)
{
	useconds_t		start;
	useconds_t		after;

	start = philo_get_time();
	after = start;
	while (after - start < usec)
	{
		if (usleep(usec) == -1)
			return (-1);
		after = philo_get_time();
	}
	return (0);
}

void	*function(void *data)
{
	printf("Philo se reveille\n");
	// printf("Thread est mort\n");
	return ((void *)data);
}

void	*eating(void *data)
{
	printf("Philo mange\n");
	return ((void *)data);
} 


void	*routine(void *all)
{
	useconds_t	end;

	end = 0;
	if (((t_all *)(all))->first_round == 1)
		((t_all *)(all))->time_act = ((t_all *)(all))->time_start;
	else
		((t_all *)(all))->time_act = philo_get_time();
	// if (((t_all *)(all))->actual_philo % 2 == 0)
	// {	
	// 	printf("1.1\n");
	// 	if (pthread_mutex_lock(&((t_all *)(all))->philo.left_fork) != 0)
	// 		return (0);
	// 	printf("%u %d has taken a fork\n", end, ((t_all *)(all))->actual_philo);
	// 	if (pthread_mutex_unlock(&((t_all *)(all))->philo.left_fork) != 0)
	// 		return (0);
	// }
	// else
	// {
	// 	printf("2.2\n");
	// 	ft_usleep(30);
	
	// printf("((t_all *)(all))->actual_philo == %d\n", ((t_all *)(all))->actual_philo);
	pthread_mutex_lock(&((t_all *)(all))->philo.left_fork);
	pthread_mutex_lock(&((t_all *)(all))->philo.r_fork);
	end = ((t_all *)(all))->time_act - ((t_all *)(all))->time_start;
	printf("%u %d has taken a fork\n", end, ((t_all *)(all))->actual_philo);
	printf("%u %d is eating\n", end, ((t_all *)(all))->actual_philo);
	ft_usleep(((t_all *)(all))->philo.time_for_eat);
	pthread_mutex_unlock(&((t_all *)(all))->philo.left_fork);
	pthread_mutex_unlock(&((t_all *)(all))->philo.r_fork);
	printf("%u %d is sleeping\n", end, ((t_all *)(all))->actual_philo);
	ft_usleep(((t_all *)(all))->philo.time_for_sleep);
	printf("%u %d is thinking\n", end, ((t_all *)(all))->actual_philo);
	if (((t_all *)(all))->philo.last_meal != -1)
		((t_all *)(all))->philo.last_meal--;
	return ((void *)all);
}

void	doing_all(t_all *all)
{
	int	i;

	i = 0;
	if (all->philo.tab_philo != NULL)
	{
		all->time_start = philo_get_time();
		while (all->philo.tab_philo[i])
		{
			// printf("i -- %d\n", i);
			all->actual_philo = i;
			// printf("all->actual_philo - %d\n", all->actual_philo);
			pthread_create(&all->philo.tab_philo[i], NULL, &routine, all);
			// pthread_create(&all->philo.tab_philo[i], NULL, &routine2, all);
			pthread_join(all->philo.tab_philo[i], NULL);

			// if (i % 2 == 0)
			// {
			// 	printf("0.1\n");
			// 	pthread_create(&all->philo.tab_philo[i], NULL, &routine, all);
			// }
			// else
			// {
			// 	printf("0.2\n");
			// 	pthread_create(&all->philo.tab_philo[i], NULL, &routine, all);
			// }
			i++;
			all->first_round = 0;
			if (i == all->num_philo)
				i = 0;
		}
	}
}

int	main(int ac, char **av)
{
	t_all	*all;

	all = malloc(sizeof(t_all *));
	all->num_philo = 0;
	if (!all)
		return (0);
	if (ac != 5 && ac != 6)
	{
		printf("Error: Missing parameters\n");
		return (0);
	}
	parsing(av, all);
	doing_all(all);
	return (0);
}