/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_arrow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:00:29 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/21 19:01:13 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	set_underline(t_group *grp, t_elem *curr)
{
	int i = -1;

	ft_tputs("cr");
	while (++i < ft_strlen(curr->name))
		ft_tputs("eo");
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
	t_elem **curr;
	t_elem *last;
	int		col;
	int i = -1;

	curr = grp->first;
	col = grp->curr_col;
	last = NULL;

	while (curr[col] != NULL)
	{
		if (curr[col]->curs_on == true)
		{
			curr[col]->curs_on = false;
			//ft_putstr("				");
			ft_tputs("cr");
			while (++i < ft_strlen(curr[col]->name))
				ft_tputs("eo"); // in
			if (curr[col]->selected)
				ft_tputs("mr");
			ft_putstr(curr[col]->name);
			ft_tputs("me");
			if (c == ARROW_D && curr[col]->next)
				return (curr[col]->next);
			else if (c == ARROW_U && last)
				return (last);
			else
				return (grp->first[0]);
		}
		last = curr[col];
		curr[col] = curr[col]->next;
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
	if (c == ARROW_U)
		handle_it(grp, "up", c);
	else if (c == ARROW_D)
		handle_it(grp, "do", c);
}

/*
	ce -> suppr char from line
	de -> remove line
	mr -> reverse video
*/
