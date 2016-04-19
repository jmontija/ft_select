/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_arrow.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:00:29 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/19 21:41:20 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	set_underline(t_elem *curr)
{
	ft_tputs("ce");
	ft_tputs("cr");
	ft_tputs("us");
	ft_putstr(curr->name);
	ft_tputs("ue");
	curr->used = true;
}

t_elem	*reset_underline(t_group *grp, int c)
{
	t_elem *curr;
	t_elem *last;

	curr = grp->first;
	last = NULL;
	while (curr != NULL)
	{
		if (curr->used)
		{
			curr->used = false;
			ft_tputs("ce");
			ft_tputs("cr");
			ft_putstr(curr->name);
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
	set_underline(curr);

}

void	handling_arrow(t_group *grp, int c)
{
	c == ARROW_U && grp->first->used == false ? handle_it(grp, "up", c) : 0;
	c == ARROW_D && grp->curr->used == false ? handle_it(grp, "do", c) : 0;
}

/*
	ce -> suppr char from line
	de -> dele line
	mr -> reverse video
*/
