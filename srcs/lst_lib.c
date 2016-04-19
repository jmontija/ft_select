/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 17:17:17 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/19 22:43:08 by jmontija         ###   ########.fr       */
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

int		insert_elem(t_group *grp, char *name)
{
	t_elem	*new;

	new = (t_elem *)malloc(sizeof(t_elem));
	if (!new)
		return (-1);
	new->name = ft_strdup(name);
	new->used = false;
	new->next = NULL;
	if (grp->curr != NULL)
		grp->curr->next = new;
	else
		grp->first = new;
	grp->curr = new;
	grp->line_nb += 1;
	return (0);
}

t_group	*init_grp(void)
{
	t_group	*grp;

	grp = (t_group *)malloc(sizeof(t_group));
	grp->first = NULL;
	grp->curr = NULL;
	grp->line_nb = -1;
	return (grp);
}