/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 20:50:08 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/28 17:24:39 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

int		check_window(t_group *grp, t_elem *curr)
{
	int				l;
	int				pad;
	struct winsize	window;

	l = 2;
	pad = 0;
	ioctl(0, TIOCGWINSZ, &window);
	while (curr != NULL)
	{
		if (l + 1 >= window.ws_row)
		{
			pad += padding_max(grp->first) + 5;
			if (window.ws_col < pad + padding_max(grp->first))
				return (-1);
			l = 2;
		}
		curr = curr->next;
		l++;
	}
	return (1);
}

void	handler_display(t_group *grp, int first)
{
	if (check_window(grp, grp->first) < 0)
	{
		clear_elements();
		ft_putendl_fd("too small", 2);
		grp->is_locked = true;
		return ;
	}
	display_elements(grp, first);
	grp->is_locked = false;
	if (grp->is_search)
		init_search(grp);
	else
	{
		tputs(tgoto(tgetstr("cm", NULL), 10, 0), 1, ft_getchar);
		ft_putstr_fd(grp->search, 2);
		tputs(tgoto(tgetstr("cm", NULL), grp->curs_pos, 0), 1, ft_getchar);
	}
}

int		ft_getchar(int c)
{
	return (write(2, &c, 1));
}

void	ft_tputs(char *cap_code)
{
	tputs(tgetstr(cap_code, NULL), 1, ft_getchar);
}
