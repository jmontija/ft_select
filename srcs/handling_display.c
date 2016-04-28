/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handling_display.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 18:50:39 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/28 01:39:56 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	clear_pos(t_elem *curr, int curs_on)
{
	size_t i;

	i = -1;
	tputs(tgoto(tgetstr("cm", NULL), curr->padding, curr->line), 1, ft_getchar);
	while (++i < ft_strlen(curr->name))
		ft_tputs("in");
	if (curr->selected)
		ft_tputs("mr");
	curr->curs_on = curs_on;
}

void	set_underline(t_group *grp, t_elem *curr)
{
	clear_pos(curr, true);
	ft_tputs("us");
	ft_putstr_fd("\033[1;32m", 2);
	ft_putstr_fd(curr->name, 2);
	ft_putstr_fd("\033[0;m", 2);
	ft_tputs("ue");
	ft_tputs("me");
	grp->curr = curr;
	grp->curs_pos = curr->line;
}

t_elem	*reset_underline(t_group *grp, int c)
{
	t_elem	*curr;
	t_elem	*last;
	size_t	i;

	i = -1;
	last = NULL;
	curr = grp->first;
	while (curr != NULL)
	{
		if (curr->curs_on == true)
		{
			clear_pos(curr, false);
			ft_putstr_fd(curr->name, 2);
			ft_tputs("me");
			if (c == ARROW_D && curr->next)
				return (curr->next);
			else if (c == ARROW_U && last)
				return (last);
			else
				return (curr);
		}
		last = curr;
		curr = curr->next;
	}
	return (NULL);
}

/* penser au grp->curr pour se deplacer, le re set si lr*/

void	handle_reg(t_group *grp, char *cap_code, int c)
{
	t_elem	*curr;

	curr = reset_underline(grp, c);
	ft_tputs(cap_code);
	set_underline(grp, curr);
}

void	handle_spec(t_group *grp, t_elem *curr, int c)
{
	reset_underline(grp, c);
	set_underline(grp, curr);
}	

t_elem	*first_last_col(int lr, t_group *grp, t_elem *curr, int pad)
{
	t_elem *new;

	new = grp->first;
	while (new != NULL)
	{
		if ((lr > 0 && new->line == curr->line) || 
			(lr < 0 && new->line == curr->line && 
			new->padding == pad))
			break;
		new = new->next;
	}
	if (new != NULL)
		return (new);
	first_last_col(lr, grp, curr, (pad - padding_max(grp->first) - 5));
}

void	handle_lr(int lr, t_group *grp)
{
	t_elem *curr;
	t_elem *new;

	curr = reset_underline(grp, 0);
	new = grp->first;
	while (new != NULL)
	{
		if (new->line == curr->line && 
			new->padding == curr->padding + lr * padding_max(grp->first) + lr * 5)
			break ;
		new = new->next;
	}
	if (new == NULL)
		new = first_last_col(lr, grp, curr, grp->last->padding);
	set_underline(grp, new);
}

