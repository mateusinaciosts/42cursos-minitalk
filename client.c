
#include "minitalk.h"

int	g_bit = 0;

void	received(int sig)
{
	if (sig == SIGUSR1)
		g_bit++;
	else if (sig == SIGUSR2)
	{
		ft_printf("Send letter\n");
		g_bit++;
	}
	else
	{
		ft_printf("\tError: Signal is invalid.\n");
		exit(22);
	}
}

void	error(char *msg)
{
	ft_printf("%s\n", msg);
	exit(0);
}

int	check_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
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
		usleep(42000);
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
		error("Wrong number of arguments.");
	if (check_digit(argv[1]) || ft_strlen(argv[1]) > 7)
		error("Invalid PID.");
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
