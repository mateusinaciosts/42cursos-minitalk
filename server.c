/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateus <mateus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:17:19 by matsanto          #+#    #+#             */
/*   Updated: 2023/10/27 20:33:45 by mateus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	signal_handle(int signum, siginfo_t *info, void *context)
{
	static t_char_bit	bit;

	if (bit.index <= 7)
	{
		if (signum == SIGUSR1)
			bit.bit += 1 << bit.index;
		else
			bit.bit += 0 << bit.index;
		bit.index++;
	}
	if (bit.index == 8)
	{
		write(1, &bit.bit, 1);
		bit.bit = 0;
		bit.index = 0;
		kill(info->si_pid, SIGUSR1);
	}
	kill(info->si_pid, SIGUSR2);
	(void)context;
}

void	init(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = signal_handle;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(void)
{
	init();
	ft_printf("server: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
