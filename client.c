/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsanto <matsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:17:15 by matsanto          #+#    #+#             */
/*   Updated: 2023/10/20 21:34:34 by matsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

char	g_wait;

void	handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGUSR1)
		write(1, "char sended!\n", 14);
	else
		g_wait = 0;
}

void	init(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof (sa));
	sa.sa_flags = 0;
	sa.sa_sigaction = handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

void	putstr(char *c)
{
	while (*c)
	{
		write(1, c, 1);
		c++;
	}
}

void	sendbit(pid_t pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (!g_wait)
		{
			g_wait	= 1;
			if (c & 1)
				kill (pid, SIGUSR1);
			else
				kill (pid, SIGUSR2);
			c >>= 1;
			i++;
			usleep(42);
		//	g_wait	= 1;
		}
	}
}

int	main(int argc, char *argv[])
{
	char	*str;
	pid_t	pid;
	size_t	i;

	i = 0;
	g_wait = 0;
	init();
	if (argc != 3)
	{
		write(1, "./client <PID> <msg>!\n", 30);
		return (-1);
	}
	pid = ft_atoi(argv[1]);
	str = argv[2];
	while (str[i] != '\0')
	{
		sendbit(pid, str[i]);
		i++;
	}
	sendbit(pid, '\n');
	exit (0);
	while (1)
		pause();
	return (0);
}
