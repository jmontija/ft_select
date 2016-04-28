/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/20 15:38:42 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/28 19:30:28 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		set_shell(int lflag)
{
	struct termios	term;
	t_group			*grp;

	grp = init_grp();
	if (tcgetattr(0, &term) == -1)
		return (-1);
	grp->cpy_term = term;
	term.c_lflag = term.c_lflag & lflag;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term))
		return (-1);
	ft_tputs("vi");
	return (0);
}

int		reset_shell(void)
{
	t_group	*grp;

	grp = init_grp();
	ft_tputs("ve");
	if (tcsetattr(0, 0, &(grp->cpy_term)) == -1)
		return (-1);
	return (0);
}

int		init_shell(void)
{
	char	*name;

	if ((name = getenv("TERM")) == NULL ||
		(ft_strcmp(name, "xterm-256color") != 0))
		name = "xterm-256color";
	if (tgetent(NULL, name) == ERR)
		return (-1);
	return (0);
}
