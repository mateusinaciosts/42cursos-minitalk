/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsanto <matsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:17:15 by matsanto          #+#    #+#             */
/*   Updated: 2023/10/29 17:57:32 by matsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_signal;

void	handle_signal(int sig, siginfo_t *info, void *context)
{	
	int	pid;

	pid = info->si_pid;
	(void)context;
	if (sig == SIGUSR1 || sig == SIGUSR2)
		g_signal = 1;
	else
	{
		write(1, "Signal is invalid\n", 19);
		exit(1);
	}
}

void	send_bit(pid_t pid, char byte)
{
	int	shift_bits;

	shift_bits = 0;
	while (shift_bits < 8)
	{
		g_signal = 0;
		if ((byte << shift_bits) & 1)
		{
			kill(pid, SIGUSR1);
			while (!g_signal)
				;
		}
		else
		{
			kill(pid, SIGUSR2);
			while (!g_signal)
				;
		}
		shift_bits++;
	}
}

int	main(int argc, char **argv)
{
	pid_t				pid;
	int					i;
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	if (argc != 3)
	{
		write(1, "Error: incorrect number of arguments\n", 38);
		return (-1);
	}
	pid = ft_atoi(argv[1]);
	i = 0;
	g_signal = 0;
	while (argv[2][i])
	{
		send_bit(pid, argv[2][i]);
		i++;
	}
	send_bit(pid, '\n');
	return (0);
}
