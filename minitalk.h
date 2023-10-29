/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matsanto <matsanto@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:47:21 by mateus            #+#    #+#             */
/*   Updated: 2023/10/29 17:40:32 by matsanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../printf/ft_printf.h"
# include "../libft/libft.h"
# include <signal.h>
# include <sys/types.h>
# include <unistd.h>

typedef struct s_char_bit
{
	char	bit;
	int		index;
}t_char_bit;

#endif
