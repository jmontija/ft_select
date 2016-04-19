/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_arrow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:00:29 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/19 23:35:40 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	set_underline(t_group *grp, t_elem *curr)
{
	ft_tputs("ce");
	ft_tputs("cr");
	if (curr->selected)
		ft_tputs("mr");
	ft_tputs("us");
	ft_putstr(curr->name);
	ft_tputs("ue");
	ft_tputs("me");
	curr->curson = true;
	grp->pos_y = curr->pos;
}

t_elem	*reset_underline(t_group *grp, int c)
{
	t_elem *curr;
	t_elem *last;

	curr = grp->first;
	last = curr;
	while (curr != NULL)
	{
		if (curr->curson)
		{
			curr->curson = false;
			ft_tputs("ce");
			ft_tputs("cr");
			if (curr->selected)
				ft_tputs("mr");
			ft_putstr(curr->name);
			ft_tputs("me");
			if (c == ARROW_D && curr->next)
				return (curr->next);
			else if (c == ARROW_U && last)
				return (last);
			else
				return (grp->first);
		}
		last = curr;
		curr = curr->next;
	}
	return (NULL);
}

void	handle_it(t_group *grp, char *cap_code, int c)
{
	t_elem	*curr;

	curr = reset_underline(grp, c);
	ft_tputs(cap_code);
	set_underline(grp, curr);
}

void	handling_arrow(t_group *grp, int c)
{
	if (c == ARROW_U && grp->first->curson == false)
		handle_it(grp, "up", c);
	else if (c == ARROW_U && grp->first->curson == true)
	{
		reset_underline(grp, c);
		tputs(tgoto(tgetstr("cm", NULL), 0, grp->line_nb), 0, ft_getchar);
		set_underline(grp, grp->curr);
	}
	else if (c == ARROW_D && grp->curr->curson == false)
		handle_it(grp, "do", c);
	else if (c == ARROW_D && grp->curr->curson == true)
		handle_it(grp, "ho", c);
}

/*
	ce -> suppr char from line
	de -> remove line
	mr -> reverse video
*/
