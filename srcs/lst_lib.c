/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 17:17:17 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/22 19:11:54 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int			ft_getchar(int c)
{
	return (write(1, &c, 1));
}

void	ft_tputs(char *cap_code)
{
	tputs(tgetstr(cap_code, NULL), 1, ft_getchar);
}

int		padding_max(t_elem *curr)
{
	size_t	max;
	size_t len;

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

int		insert_elem(t_group *grp, char *name, int col)
{
	t_elem	*new;

	new = (t_elem *)malloc(sizeof(t_elem));
	if (!new)
		return (-1);
	new->name = ft_strdup(name);
	new->curs_on = false;
	new->selected = false;
	new->next = NULL;
	new->last = false;
	if (grp->last[col] != NULL)
		grp->last[col]->next = new;
	else
		grp->first[col] = new;
	grp->last[col] = new;
	return (0);
}

t_group	*init_grp(void)
{
	t_group	*grp;
	int		i;

	i = -1;
	grp = (t_group *)malloc(sizeof(t_group));
	grp->first = (t_elem **)malloc(sizeof(t_elem *) * 10);
	grp->last  = (t_elem **)malloc(sizeof(t_elem *) * 10);
	grp->last[10] = NULL;
	grp->first[10] = NULL;
	while (++i <= 10)
	{
		grp->first[i] = NULL;
		grp->last[i] = NULL;
	}
	grp->window = (int *)malloc(sizeof(int) * 2);
	grp->window[x] = 0;
	grp->window[y] = 0;
	grp->last_col = 0;
	grp->last_elem = 0;
	grp->curs_pos = 0;
	grp->curr_col = 0;
	return (grp);
}