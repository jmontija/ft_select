/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 20:39:28 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/27 01:01:22 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	handler_win(int sig)
{
	t_group			*grp;
	int first;

	sig = 0;
	grp = init_grp();
	first = (grp->curs_pos < 0) ? 1 : 0;
	grp = init_grp();
	handler_display(grp, first);
}

void	handler_cont(int sig)
{
	t_group	*grp;

	sig = 0;
	grp = init_grp();
	init_shell();
	set_shell((~ICANON & ~ECHO));
	handler_display(grp, 0);
}

void	handler_ctrl(int sig)
{
	char	order[2];

	order[0] = sig == SIGTSTP ? 26 : 3;
	order[1] = 0;
	reset_shell();
	signal(sig, SIG_DFL);
	ioctl(0, TIOCSTI, order);
}

void	sig_handler(void)
{
	signal(SIGWINCH, handler_win);
	signal(SIGINT, handler_ctrl);
	signal(SIGTSTP, handler_ctrl);
	signal(SIGCONT, handler_cont);
}
