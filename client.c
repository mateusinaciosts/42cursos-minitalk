/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateus <mateus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:17:15 by matsanto          #+#    #+#             */
/*   Updated: 2023/10/27 20:37:24 by mateus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_bit = 0;

void	received(int sig)
{
	if (sig == SIGUSR1)
		g_bit++;
	else if (sig == SIGUSR2)
	{
		write(1, "Send letter\n", 13);
		g_bit++;
	}
	else
	{
		write(1, "\tError: Signal is invalid.\n", 28);
		exit(22);
	}
}

void	send_bit(pid_t pid, char byte)
{
	int	shift_bits;

	shift_bits = 0;
	while (shift_bits < 8)
	{
		if ((byte >> shift_bits) & 1)
		{
			kill(pid, SIGUSR1);
		}
		else
		{
			kill(pid, SIGUSR2);
		}
		usleep(42);
		shift_bits++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	signal(SIGUSR1, received);
	signal(SIGUSR2, received);
	if (argc != 3)
		write(1, "Wrong number of arguments.", 27);
	pid = ft_atoi(argv[1]);
	i = 0;
	while (argv[2][i])
	{
		send_bit(pid, argv[2][i]);
		i++;
	}
	send_bit(pid, '\n');
	return (0);
}