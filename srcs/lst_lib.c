/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 17:17:17 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/29 00:07:20 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		padding_max(t_elem *curr)
{
	size_t	max;
	size_t	len;

	max = 0;
	len = 0;
	while (curr != NULL)
	{
		len = ft_strlen(curr->name);
		if (max < len)
			max = len;
		curr = curr->next;
	}
	return ((int)max);
}

int		insert_elem(t_group *grp, char *name)
{
	t_elem	*new;

	new = (t_elem *)malloc(sizeof(t_elem));
	if (!new)
		return (-1);
	new->name = ft_strdup(name);
	new->curs_on = false;
	new->selected = false;
	new->padding = 0;
	new->line = 0;
	new->next = NULL;
	if (grp->last != NULL)
		grp->last->next = new;
	else
		grp->first = new;
	grp->last = new;
	return (0);
}

t_group	*set_grp(void)
{
	t_group	*grp;

	grp = (t_group *)malloc(sizeof(t_group));
	grp->first = NULL;
	grp->last = NULL;
	grp->curr = NULL;
	grp->search = ft_strdup("");
	grp->window = (int *)malloc(sizeof(int) * 2);
	grp->window[x] = 0;
	grp->window[y] = 0;
	grp->curs_pos = -1;
	grp->is_locked = false;
	grp->is_search = false;
	return (grp);
}

t_group	*init_grp(void)
{
	static t_group *grp = NULL;

	if (grp == NULL)
		grp = set_grp();
	return (grp);
}
