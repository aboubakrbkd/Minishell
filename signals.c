/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukdid <aboukdid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 17:25:50 by aboukdid          #+#    #+#             */
/*   Updated: 2024/07/20 19:45:22 by aboukdid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	function_sigint(int sig)
{
	if (sig == SIGINT && g_signal_status == 0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		ex_st(1, 1);
	}
	else if (sig == SIGINT && g_signal_status == 1)
		write(1, "\n", 1);
}

void	function_sigwuit(int sig)
{
	if (sig == SIGQUIT && g_signal_status == 1)
		write(1, "Quit: 3\n", 8);
}

void	check_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, function_sigint);
	signal(SIGQUIT, function_sigwuit);
}
