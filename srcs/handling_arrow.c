/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_arrow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:00:29 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/21 20:36:21 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	set_underline(t_group *grp, t_elem *curr)
{
	int i = -1;

	tputs(tgoto(tgetstr("cm", NULL), (grp->curr_col * 27), curr->pos), 1, ft_getchar);
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
			tputs(tgoto(tgetstr("cm", NULL), (grp->curr_col * 27), curr->pos), 1, ft_getchar);
			while (++i < ft_strlen(curr->name))
				ft_tputs("in"); // eo or in //
			if (curr->selected)
				ft_tputs("mr");
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
	else if (c == ARROW_D && grp->curs_pos + 2 == grp->window[y])
	{
		reset_underline(grp, c);
		grp->curs_pos = 0;
		grp->curr_col += 1;
		tputs(tgoto(tgetstr("cm", NULL), (grp->curr_col * 27), 0), 1, ft_getchar);
		set_underline(grp, grp->first[grp->curr_col]);
	}
	else if (c == ARROW_D)
		handle_it(grp, "do", c);
}

/*
	ce -> suppr char from line
	de -> remove line
	mr -> reverse video
*/
