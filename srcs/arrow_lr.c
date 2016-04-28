/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_lr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 17:28:11 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/28 19:57:16 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_elem	*first_last_col(int lr, t_group *grp, t_elem *curr, int pad)
{
	t_elem *new;

	new = grp->first;
	while (new != NULL)
	{
		if ((lr > 0 && new->line == curr->line) ||
			(lr < 0 && new->line == curr->line &&
			new->padding == pad))
			break ;
		new = new->next;
	}
	return (new);
}

void	handle_lr(int lr, t_group *grp)
{
	t_elem	*curr;
	t_elem	*new;
	int		pad;

	curr = reset_underline(grp, 0);
	new = grp->first;
	pad = grp->last->padding;
	while (new != NULL)
	{
		if (new->line == curr->line &&
			new->padding == (curr->padding +
				lr * padding_max(grp->first) + lr * 5))
			break ;
		new = new->next;
	}
	while (new == NULL)
	{
		new = first_last_col(lr, grp, curr, pad);
		pad = pad - padding_max(grp->first) - 5;
	}
	set_underline(grp, new);
}
