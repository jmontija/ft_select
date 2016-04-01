/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:56:15 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/01 20:49:28 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		set_shell(struct termios *term, int fd, int lflag)
{
	if (tcgetattr(0, term) == -1)
		return (-1);
	term->c_lflag = term->c_lflag & lflag;
	term->c_cc[VMIN] = 1; // nb de fois où la touche doit etre appuyé pour lancer la commande
	term->c_cc[VTIME] = 0; // retour de read tout les n délai
	if (tcsetattr(fd, TCSADRAIN, term)) // check pour le TCSAFLUSH
		return (-1);
	return (0);
}

int		reset_shell(struct termios *term, int lflag)
{
	if (tcgetattr(0, term) == -1)
		return (-1);
	term->c_lflag = lflag;
	if (tcsetattr(0, 0, term)) // check pour le TCSAFLUSH
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
	int		fd;
	int		key;

	fd = 0;
	key = 0;
	init_shell(fd);
	if (set_shell(&term, fd, (~ICANON & ~ECHO)) < 0)
		return (-1);
	while (7)
	{
		ft_putstr("fts> ");
		while (read(0, order, BUF_SIZE))
		{
			//printf("%d %d %d", order[0], order[1], order[2]);
			if (set_shell(&term, fd, (~ICANON & ~ECHO)) < 0)
				return (-1);
			key = order[0];
			if (key == '\n')
				break ;
			else if(key == ARROW)
				handling_arrow(order[2]);
			else if (key == TAB)
				handling_tab();
			else if (key == 4)
				return (-1);
			else if (key != TAB && key != ARROW)
			{
				cfmakeraw(&term);
				reset_shell(&term, (ICANON | ECHO));
				//break ;
			}
				//ft_putstr("need to set the shell en mode non CANONIQUE");
		}
		order[0] = false;
		ft_putchar('\n');
	}
	return (0);
}