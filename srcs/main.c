/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:56:15 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/22 18:47:35 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	display_selection(t_group *grp)
{
	int	i;
	int	select;
	t_elem	*curr;

	i = -1;
	select = 0;
	ft_tputs("cl");
	ft_putendl("Your selection:");
	ft_putstr("->");
	while (grp->first[++i])
	{
		curr = grp->first[i];
		while (curr != NULL)
		{
			if (curr->selected)
			{
				ft_putchar(' ');
				ft_putstr(curr->name);
				select++;
			}
			curr = curr->next;
		}
	}
	select == 0 ? ft_putendl("Nothing have been selected") : 0;
	reset_shell();
}

t_elem	*underline_first(t_group *grp, t_elem *curr)
{
	curr->curs_on = true;
	ft_tputs("us");
	ft_putendl(curr->name);
	ft_tputs("ue");
	grp->curs_pos = curr->pos;
	return (curr->next);
}

void	display_elements(t_group *grp)
{
	int	i;
	int	l;
	int pad;
	t_elem	*curr;

	i = -1;
	l = 0;
	while (grp->first[++i])
	{
		curr = (i == 0) ? underline_first(grp, grp->first[i]) : grp->first[i];
		pad = (i > 0) ? padding_max(grp->first[i - 1]) : 0;
		while (curr != NULL)
		{
			if (i > 0)
			{
				tputs(tgoto(tgetstr("cm", NULL), i * (pad + 5), l), 1, ft_getchar);
				l++;
			}
			ft_putendl(curr->name);
			curr = curr->next;
		}
		l = 0;
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
			elem_col_nb = 1;
		}
		insert_elem(grp, argv[i], col);
		grp->last[col]->pos = elem_col_nb - 1;
	}
	grp->last_col = col;
	grp->last_elem = elem_col_nb;
}

void	init_selection(t_group *grp, char **argv)
{
	init_shell();
	set_shell((~ICANON & ~ECHO));
	ft_tputs("cl");
	//ft_tputs("vi");
	dimension_shell(grp, argv);
	display_elements(grp);
}

void	handle_win(int sig)
{

}

int main (int argc, char **argv)
{
	t_group	*grp;
	t_group *tmp;
	char	order[BUF_SIZE];

	grp = init_grp();
	argc < 2 ? exit(0) : 0;
	init_selection(grp, argv);
	signal(SIGWINCH, handle_win);
	while (read(0, order, BUF_SIZE))
	{
		if (order[0] == ENTER)
			break ;
		if (order[0] == ARROW)
			handling_arrow(grp, order[2]);
		else if (order[0] == SPACE)
			handling_space(grp);
	}
	display_selection(grp);
	return (0);
}