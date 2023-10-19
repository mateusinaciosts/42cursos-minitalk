
#include "minitalk.h"

char	g_wait;

void	handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGUSR1)
		ft_printf("char sended!\n");
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
			usleep(5000);
		//	g_wait	= 1;
		}
	}
}

int	main(int ac, char *av[])
{
	char	*str;
	pid_t	pid;
	size_t	i;

	i = 0;
	g_wait = 0;
	init();
	if (ac != 3)
	{
		ft_printf("./client <process_id> <msg>!\n");
		return (-1);
	}
	pid = ft_atoi(av[1]);
	str = av[2];
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
