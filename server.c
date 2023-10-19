#include "minitalk.h"

static char	g_bit;

void	signal_handle(int signum, siginfo_t *info, void *context)
{
	static char	temp;

	if (g_bit <= 8)
	{
		if (signum == SIGUSR1)
			temp += 1 << g_bit;
		else
			temp += 0 << g_bit;
		g_bit++;
	}
	if (g_bit == 8)
	{
		write(1, &temp, 1);
		g_bit = 0;
		temp = 0;
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
	ft_printf("server process = [%d]\n", getpid());
	while (1)
		pause();
	return (0);
}
