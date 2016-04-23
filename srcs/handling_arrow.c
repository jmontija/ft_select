/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_arrow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:00:29 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/23 20:32:48 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	set_underline(t_group *grp, t_elem *curr)
{
	int i = -1;

	tputs(tgoto(tgetstr("cm", NULL), curr->padding, curr->pos), 1, ft_getchar);
	while (++i < ft_strlen(curr->name))
		ft_tputs("in");
	if (curr->selected)
		ft_tputs("mr");
	ft_tputs("us");
	ft_putstr(curr->name);
	ft_tputs("ue");
	ft_tputs("me");
	curr->curs_on = true;
	grp->curs_pos = curr->pos;
}

t_elem	*reset_underline(t_group *grp, int c)
{
	t_elem *curr;
	t_elem *last;
	int		i;

	i = -1;
	last = NULL;
	curr = grp->first[grp->curr_col];
	while (curr != NULL)
	{
		if (curr->curs_on == true)
		{
			curr->curs_on = false;
			tputs(tgoto(tgetstr("cm", NULL), curr->padding, curr->pos), 1, ft_getchar);
			while (++i < ft_strlen(curr->name))
				ft_tputs("in");
			if (curr->selected)
				ft_tputs("mr");
			if (curr->pos == grp->curs_pos)
			ft_putstr(curr->name);
			ft_tputs("me");
			if (c == ARROW_D && curr->next)
				return (curr->next);
			else if (c == ARROW_U && last)
				return (last);
		}
		last = curr;
		curr = curr->next;
	}
	return (NULL);
}

void	handle_reg(t_group *grp, char *cap_code, int c)
{
	t_elem	*curr;

	curr = reset_underline(grp, c);
	ft_tputs(cap_code);
	set_underline(grp, curr);
}

void	handle_spec(t_group *grp, int c, int col, t_elem *curr)
{
	reset_underline(grp, c);
	grp->curr_col = col;
	set_underline(grp, curr);
}

void	handling_arrow(t_group *grp, int c)
{
	if (c == ARROW_U && grp->curs_pos == 0 && grp->curr_col == 0)
		handle_spec(grp, c, grp->last_col, grp->last[grp->last_col]);
	else if (c == ARROW_U && grp->curs_pos == 0)
		handle_spec(grp, c, grp->curr_col - 1, grp->last[grp->curr_col - 1]);
	else if (c == ARROW_U)
		handle_reg(grp, "up", c);
	else if (c == ARROW_D && grp->last[grp->curr_col + 1] == NULL && grp->curs_pos + 1 == grp->last_elem)
		handle_spec(grp, c, 0, grp->first[0]);
	else if (c == ARROW_D && grp->curs_pos + 2 == grp->window[y])
		handle_spec(grp, c, grp->curr_col + 1, grp->first[grp->curr_col + 1]);
	else if (c == ARROW_D)
		handle_reg(grp, "do", c);
}
