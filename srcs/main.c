/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:56:15 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/23 22:26:02 by jmontija         ###   ########.fr       */
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

void	display_elements(t_group *grp, int first)
{
	int	i;
	int	l;
	int pad;
	int next;
	t_elem	*curr;

	i = -1;
	l = 0;
	pad = 0;
	next = false
	while (grp->first[++i])
	{
		curr = (i == 0 && first) ? underline_first(grp, grp->first[i]) : grp->first[i];
		while (curr != NULL)
		{
			if (i > 0)
			{
				tputs(tgoto(tgetstr("cm", NULL), pad, l), 1, ft_getchar);
				l++;
			}
			if (curr->selected)
				ft_tputs("mr");
			if (curr->curs_on)
				ft_tputs("us");
			ft_putendl(curr->name);
			ft_tputs("ue");
			ft_tputs("me");
			curr->padding = pad;
			curr = curr->next;
		}
		l = 0;
		pad += padding_max(grp->first[i]) + 5;
	}
	ft_tputs("ho");
}

void	reset_all(t_group *grp)
{
	int	i;
	t_elem	*curr;
	t_elem	*tmp;

	i = -1;
	while (grp->first[++i])
	{
		curr = grp->first[i];
		while (curr != NULL)
		{
			ft_strdel(&curr->name);
			curr->curs_on = false;
			curr->selected = false;
			curr->padding = 0;
			curr->next = NULL;
			tmp = curr;
			ft_memdel((void *)&tmp);
			curr = curr->next;
		}
	}
}

void	make_copy(t_group *grp)
{
	int	i;
	t_elem	*curr;
	t_elem	**copy
	t_elem	curr_cpy;

	if (grp->first == NULL)
		return ;
	i = -1;
	copy = (t_elem **)malloc(sizeof(t_elem *) * 10);
	copy[10] = NULL;
	while (++i <= 10)
		copy[i] = NULL;
	while (grp->first[++i])
	{
		curr = grp->first[i];
		curr_cpy = copy[i];
		while (curr != NULL)
		{
			curr_cpy = (t_elem *)malloc(sizeof(t_elem));
			curr_cpy->curs_on = curr->curs_on;
			curr_cpy->selected = curr->selected;
			curr = curr->next;
		}
	}
	reset_all(grp);
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
	make_copy(grp);
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
		grp->last[col]->num = i;
	}
	grp->last_col = col;
	grp->last_elem = elem_col_nb;
}

void	init_selection(t_group *grp, char **argv)
{
	init_shell();
	set_shell((~ICANON & ~ECHO));
	ft_tputs("cl");
	ft_tputs("vi");
	dimension_shell(grp, argv);
	display_elements(grp, 1);
}

void	handler(int sig)
{
	struct winsize	window;
	int				x_max;
	t_group			*grp;

	grp = init_grp();
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &window);
	x_max = (grp->first[grp->last_col]->padding) + padding_max(grp->first[grp->last_col]);
	if (window.ws_col < x_max || window.ws_row < grp->window[y])
	{
		ft_tputs("cl");
		ft_putendl("window needs to be bigger to display the selection");
	}
	else
	{
		ft_tputs("cl");
		display_elements(grp, 0);
	}
}

int main (int argc, char **argv)
{
	t_group	*grp;
	t_group *tmp;
	char	order[BUF_SIZE];

	grp = init_grp();
	argc < 2 ? exit(0) : 0;
	init_selection(grp, argv);
	signal(SIGWINCH, handler);
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