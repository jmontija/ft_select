/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 19:39:22 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/28 18:19:38 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	key_tab(t_group *grp)
{
	t_elem	*curr;
	int		curs_pos;

	curs_pos = 0;
	curs_pos = grp->curs_pos;
	if (ft_strlen(grp->search) > 0 && grp->curr)
	{
		curr = grp->curr->next;
		while (curr != NULL)
		{
			if (ft_strncmp(grp->search, curr->name,
				ft_strlen(grp->search)) == 0)
				break ;
			curr = curr->next;
		}
		curr != NULL ?
		handle_spec(grp, curr, -1) : find_search(grp, grp->search);
	}
	grp->curs_pos = curs_pos;
	tputs(tgoto(tgetstr("cm", NULL), curs_pos, 0), 1, ft_getchar);
}

void	key_ctrl_r(t_group *grp)
{
	int	i;

	i = -1;
	tputs(tgoto(tgetstr("cm", NULL), 10, 0), 1, ft_getchar);
	while (++i < ft_strlen(grp->search))
		ft_putchar_fd(' ', 2);
	free(grp->search);
	grp->search = ft_strdup("");
	grp->curs_pos = 10;
	reset_underline(grp, 0);
	grp->curr = NULL;
	tputs(tgoto(tgetstr("cm", NULL), 10, 0), 1, ft_getchar);
}

void	key_bkspace(t_group *grp)
{
	grp->curs_pos -= 1;
	tputs(tgoto(tgetstr("cm", NULL), grp->curs_pos, 0), 1, ft_getchar);
	ft_tputs("dc");
	grp->search = ft_free_char(grp->search);
	find_search(grp, grp->search);
}

void	handling_search(t_group *grp, int key)
{
	if (key == ENTER)
	{
		ft_tputs("vi");
		grp->is_search = false;
		grp->curr && ft_strlen(grp->search) > 0 ?
		handling_space(grp) : handle_spec(grp, grp->first, -1);
	}
	else if (key == BACKSPACE && grp->curs_pos > 10)
		key_bkspace(grp);
	else if (key == TAB)
		key_tab(grp);
	else if (key == CTRL_R)
		key_ctrl_r(grp);
	else if (ft_isprint(key))
	{
		grp->curs_pos += 1;
		ft_putchar_fd(key, 2);
		grp->search = ft_charjoin(grp->search, key);
		find_search(grp, grp->search);
	}
}
