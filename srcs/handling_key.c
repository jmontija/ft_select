/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:00:29 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/28 16:34:59 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	manage_list(t_group *grp, t_elem *curr, t_elem *prev)
{
	if (prev == NULL && curr->next == NULL)
	{
		reset_shell();
		exit(0);
	}
	if (prev == NULL)
	{
		grp->first = curr->next;
		curr->next->curs_on = true;
	}
	else
		prev->next = curr->next;
	if (curr->next == NULL)
	{
		grp->last = prev;
		prev->curs_on = true;
	}
	else
		curr->next->curs_on = true;
}

void	handling_backspace(t_group *grp)
{
	t_elem	*curr;
	t_elem	*prev;
	int		i;

	i = -1;
	curr = grp->first;
	prev = NULL;
	while (curr != NULL)
	{
		if (curr->curs_on == true)
		{
			manage_list(grp, curr, prev);
			ft_strdel(&curr->name);
			curr->curs_on = false;
			curr->selected = false;
			curr->padding = 0;
			curr->line = 0;
			curr->next = NULL;
			ft_memdel((void *)&curr);
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
	handler_display(grp, 0);
}

void	handling_space(t_group *grp)
{
	t_elem	*curr;
	size_t	i;

	i = -1;
	curr = grp->first;
	while (curr != NULL)
	{
		if (curr->curs_on == true && curr->selected == false)
			curr->selected = true;
		else if (curr->curs_on == true && curr->selected == true)
			curr->selected = false;
		curr = curr->next;
	}
	handling_arrow(grp, ARROW_D);
}

void	handling_arrow(t_group *grp, int c)
{
	if (c == ARROW_U && grp->first->curs_on == true)
		handle_spec(grp, grp->last, c);
	else if (c == ARROW_U)
		handle_reg(grp, "up", c);
	else if (c == ARROW_D && grp->last->curs_on == true)
		handle_spec(grp, grp->first, c);
	else if (c == ARROW_D)
		handle_reg(grp, "do", c);
	else if (c == ARROW_L)
		handle_lr(-1, grp);
	else if (c == ARROW_R)
		handle_lr(1, grp);
}
