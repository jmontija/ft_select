/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:56:15 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/03 19:12:28 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		set_shell(int lflag)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	cfmakeraw(&term);
	term.c_lflag = term.c_lflag & lflag;
	term.c_cc[VMIN] = 1; // nb de fois où la touche doit etre appuyé pour lancer la commande
	term.c_cc[VTIME] = 0; // retour de read tout les n délai*/
	if (tcsetattr(0, TCSADRAIN, &term)) // check pour le TCSAFLUSH
		return (-1);
	return (0);
}

int		reset_shell()
{
	struct termios term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	if (tcsetattr(0, 0, &term) == -1)
		return (-1);
	return (0);
}

int		init_shell(int fd)
{
	char	*name;

	if ((name = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name) == ERR)
		return (-1);
	return (0);
}

int main(int argc, char **argv)
{
	struct termios	term;
	char	order[BUF_SIZE];
	int		key;
	int		ret;

	key = 0;
	init_shell(0);
	while (7)
	{
		ft_putstr("fts> ");
		while ((ret = read(0, order, BUF_SIZE)))
		{
			key = order[0];
			if (key == 10)
				break ;
			else if(key == ARROW)
			{
				set_shell((~ICANON & ~ECHO));
				handling_arrow(order[2]);
				reset_shell();
			}
			else if (key == TAB)
			{
				set_shell((~ICANON & ~ECHO));
				handling_tab();
				reset_shell();
			}
			else if (key != TAB && key != ARROW)
				ft_putstr("key_pressed $");
		}
	}
	return (0);
}