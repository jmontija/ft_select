/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_lib.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/19 17:17:17 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/20 20:16:08 by jmontija         ###   ########.fr       */
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
	if (grp->curr[col] != NULL)
		grp->curr[col]->next = new;
	else
		grp->first[col] = new;
	grp->curr[col] = new;
	return (0);
}

t_group	*init_grp(void)
{
	t_group	*grp;
	int i;

	i = -1;
	grp = (t_group *)malloc(sizeof(t_group));
	grp->first = (t_elem **)malloc(sizeof(t_elem *) * 10);
	grp->curr  = (t_elem **)malloc(sizeof(t_elem *) * 10);
	grp->curr[10] = NULL;
	grp->first[10] = NULL;
	while (++i <= 10)
		grp->first[i] = NULL;
	i = -1;
	while (++i <= 10)
		grp->curr[i] = NULL;
	grp->window = (int *)malloc(sizeof(int) * 2);
	grp->window[x] = 0;
	grp->window[y] = 0;
	grp->elem_nb = -1;
	grp->curs_pos = 0;
	return (grp);
}