#include "minitalk.h"

char	g_char = 0;

void	print_char(int signal, siginfo_t *siginfo, void *context)
{
	static int	i = 0;

	(void)context;
	if (signal == SIGUSR1)
		g_char += (1 << i);
	if (i == 7)
	{
		write(1, &g_char, 1);
		g_char = 0;
		i = 0;
		kill(siginfo->si_pid, SIGUSR2);
		return ;
	}
	i++;
	kill(siginfo->si_pid, SIGUSR1);
}

int	main(void)
{
	siginfo_t siginfo;
	struct sigaction sa;
	sigset_t sigset;

	sa = (struct sigaction){0};
	sigemptyset(&sigset);
	sigaddset(&sigset, SIGUSR1);
	sigaddset(&sigset, SIGUSR2);
	sa.sa_mask = sigset;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = print_char;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	pid_t process_id = getpid();
	ft_printf("PID: %i\n", process_id);
	while (1)
	{
		pause();
	}	
	return (0);
}