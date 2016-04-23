/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 23:08:02 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/23 20:02:21 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	handling_space(t_group *grp)
{
	t_elem *curr;
	int i = -1;

	curr = grp->first[grp->curr_col];
	ft_tputs("mr");
	while (curr != NULL)
	{
		if (curr->selected == false && curr->pos == grp->curs_pos)
		{
			tputs(tgoto(tgetstr("cm", NULL), curr->padding, curr->pos), 1, ft_getchar);
			while (++i < ft_strlen(curr->name))
				ft_tputs("in");
			ft_putstr(curr->name);
			curr->selected = true;
		}
		else if (curr->selected == true && curr->pos == grp->curs_pos)
		{
			tputs(tgoto(tgetstr("cm", NULL), curr->padding, curr->pos), 1, ft_getchar);
			while (++i < ft_strlen(curr->name))
				ft_tputs("in");
			ft_tputs("me");
			ft_putstr(curr->name);
			curr->selected = false;
		}
		curr = curr->next;
	}
	ft_tputs("me");
}