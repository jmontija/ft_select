/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:56:15 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/20 20:23:15 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	display_selection(t_elem *curr)
{
	int	i;

	i = -1;
	ft_tputs("cl");
	ft_putendl("Your selection:");
	ft_putstr("->");
	while (curr != NULL)
	{
		if (curr->selected)
		{
			ft_putchar(' ');
			ft_putstr(curr->name);
			i++;
		}
		curr = curr->next;
	}
	i < 1 ? ft_putendl("Nothing have been selected") : 0;
	reset_shell();
}

void	display_elements(t_group *grp, t_elem **curr)
{
	int	i;
	int	l;

	i = -1;
	l = -1;
	ft_tputs("us");
	ft_putendl(curr[0]->name);
	curr[0]->curs_on = true;
	grp->curs_pos = curr[0]->pos;
	ft_tputs("ue");
	while (curr[++i])
	{
		while ((curr[i] = curr[i]->next) != NULL)
		{
			if (i > 0)
				tputs(tgoto(tgetstr("cm", NULL), (i * 27), l++), 1, ft_getchar);
			ft_putendl(curr[i]->name);
		}
		l = -1;
	}
	ft_tputs("ho");
}

void	dimension_shell(t_group *grp, char **argv)
{
	int i;
	int col;
	int elem_col_nb;

	i = 0;
	col = 0;
	elem_col_nb = 0;
	grp->window[x] = tgetnum("co");
	grp->window[y] = tgetnum("li");
	while (argv[++i])
	{
		elem_col_nb++;
		if (elem_col_nb >= grp->window[y])
		{
			col++;
			elem_col_nb = 0;
		}
		insert_elem(grp, argv[i], col);
		grp->curr[col]->pos = i;
	}
	grp->elem_nb = i - 2;
}

void	init_selection(t_group *grp, char **argv)
{
	init_shell();
	set_shell((~ICANON & ~ECHO));
	ft_tputs("cl");
	//ft_tputs("vi");
	dimension_shell(grp, argv);
	display_elements(grp, grp->first);
}

int main(int argc, char **argv)
{
	t_group	*grp;
	char	order[BUF_SIZE];

	grp = init_grp();
	argc < 2 ? exit(0) : 0;
	init_selection(grp, argv);
	while (read(0, order, BUF_SIZE))
	{
		if (order[0] == ENTER)
			break ;
		if(order[0] == ARROW)
			handling_arrow(grp, order[2]);
		/*else if (order[0] == SPACE)
			handling_space(grp);*/
	}
	//display_selection(grp->first);
	return (0);
}