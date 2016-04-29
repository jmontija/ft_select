/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_elements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/24 19:18:32 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/29 01:35:16 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	clear_elements(void)
{
	int				i;
	struct winsize	window;

	i = -1;
	ft_tputs("ho");
	ioctl(0, TIOCGWINSZ, &window);
	while (++i <= window.ws_row)
		ft_tputs("dl");
}

void	display_col(t_elem *curr, int pad, int l)
{
	tputs(tgoto(tgetstr("cm", NULL), pad, l), 1, ft_getchar);
	if (curr->selected == false && curr->curs_on == false)
		ft_putstr_fd("\033[1;37m", 2);
	else if (curr->curs_on == true)
	{
		ft_tputs("us");
		ft_putstr_fd("\033[1;32m", 2);
		if (curr->selected == true)
			ft_putstr_fd("\033[1;37m", 2);
	}
	else
		ft_putstr_fd("\033[1;32m", 2);
	if (curr->selected)
		ft_tputs("mr");
	ft_putendl_fd(curr->name, 2);
	ft_putstr_fd("\033[0;m", 2);
	ft_tputs("ue");
	ft_tputs("me");
	curr->padding = pad;
	curr->line = l;
}

int		display_elements(t_group *grp, int first)
{
	int				l;
	int				pad;
	t_elem			*curr;
	struct winsize	window;

	l = 2;
	pad = 0;
	ioctl(0, TIOCGWINSZ, &window);
	first ? ft_tputs("cl") : clear_elements();
	display_search(window);
	curr = grp->first;
	while (curr != NULL)
	{
		if (l + 1 >= window.ws_row)
		{
			pad += padding_max(grp->first) + 5;
			l = 2;
		}
		display_col(curr, pad, l);
		curr = curr->next;
		l++;
	}
	tputs(tgoto(tgetstr("cm", NULL), 0, 2), 1, ft_getchar);
	return (1);
}
