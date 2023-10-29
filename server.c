/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsanto <matsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:17:19 by matsanto          #+#    #+#             */
/*   Updated: 2023/10/29 17:52:31 by matsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int signum, siginfo_t *info, void *context)
{
	static t_char_bit	bit;

	(void)context;
	if (bit.index <= 7)
	{
		if (signum == SIGUSR1)
			bit.bit += 1 >> bit.index;
		else
			bit.bit += 0 >> bit.index;
		bit.index++;
	}
	if (bit.index == 8)
	{
		write(1, &bit.bit, 1);
		bit.bit = 0;
		bit.index = 0;
	}
	if (signum == SIGUSR1)
		kill(info->si_pid, SIGUSR1);
	else if (signum == SIGUSR2)
		kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(sa));
	sa.sa_sigaction = handle_signal;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("server: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
