/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:56:15 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/01 16:19:35 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"



int	set_terminal(int fd)
{
	char			*name;
	struct termios	term;

	if ((name = getenv("TERM")) == NULL)
		return (-1);
	if (tgetent(NULL, name) == ERR)
		return (-1);
	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag = term.c_lflag & (~ICANON);
	term.c_lflag = term.c_lflag & (~ECHO);
	term.c_cc[VMIN] = 1; // nb de fois où la touche doit etre appuyé pour lancer la commande
	term.c_cc[VTIME] = 0; // retour de read tout les n délai
	if (tcsetattr(fd, TCSAFLUSH, &term))
		return (-1);
	return (0);
}

int main(int argc, char **argv)
{
	char	order[3];
	int		fd;
	int		ret;

	fd = 0;
	ret = 0;
	if (set_terminal(fd) < 0)
		return (-1);
	while (7)
	{
		ft_putstr("fsh-> ");
		while (order[0] != '\n')
		{
			ret = read(0, order, 3);
			//printf("%d %d %d\n", order[0], order[1], order[2]);
			if(order[0] == ARROW)
				handling_arrow(order[2]);
			else if (order[0] == TAB)
				handling_tab();
			else if (order[0] == 4)
				exit(0);
		}
		order[0] = false;
		ft_putchar('\n');
	}
	return (0);
}