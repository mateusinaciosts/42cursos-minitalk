/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mateus <mateus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 21:17:19 by matsanto          #+#    #+#             */
/*   Updated: 2023/10/27 23:14:32 by mateus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handle_signal(int signum)
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
	}
}

int	main(void)
{
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	ft_printf("server: %d\n", getpid());
	while (1)
		pause();
	return (0);
}
