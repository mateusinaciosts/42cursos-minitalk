/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateus <mateus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:17:15 by matsanto          #+#    #+#             */
/*   Updated: 2023/10/27 23:38:32 by mateus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int sig)
{
	static int	bit = 0;

	if (bit == 7)
	{
		write(1, "Send letter\n", 13);
		bit = 0;
	}
	else if (sig == SIGUSR1 || sig == SIGUSR2)
		bit++;
	else
	{
		write(1, "Signal is invalid\n", 19);
		exit(1);
	}
}

void	end_bit(pid_t pid, char byte)
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
		usleep(420);
		shift_bits++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	if (argc != 3)
	{
		write(1, "error in the number of arguments\n", 34);
		return (-1);
	}
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
