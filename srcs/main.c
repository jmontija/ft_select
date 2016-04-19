/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:56:15 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/19 21:04:33 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		set_shell(int lflag)
{
	struct termios	term;

	if (tcgetattr(0, &term) == -1)
		return (-1);
	term.c_lflag = term.c_lflag & lflag;
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term))
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

int		init_shell()
{
	char	*name;

	if ((name = getenv("TERM")) == NULL)
		name = "xterm-256color";
	if (tgetent(NULL, name) == ERR)
		return (-1);
	return (0);
}

void	display_select(t_elem *first)
{
	ft_tputs("us");
	ft_putendl(first->name);
	first->used = true;
	first = first->next;
	ft_tputs("ue");
	while (first != NULL)
	{
		ft_putendl(first->name);
		first = first->next;
	}
}

int main(int argc, char **argv)
{
	t_group	*grp;
	char	order[BUF_SIZE];
	int		i;

	i = 0;
	grp = init_grp();
	init_shell();
	set_shell((~ICANON & ~ECHO));
	tputs(tgetstr("cl", NULL), 1, ft_getchar);
	if (argc < 2)
		return (0);
	while (argv[++i])
		insert_elem(grp, argv[i]);
	display_select(grp->first);
	tputs(tgetstr("ho", NULL), 1, ft_getchar);
	while (read(0, order, BUF_SIZE))
	{
		if (order[0] == ENTER)
			break ;
		if(order[0] == ARROW)
			handling_arrow(grp, order[2]);
		else if (order[0] == SPACE)
			ft_tputs("mr");
	}
	reset_shell();
	return (0);
}