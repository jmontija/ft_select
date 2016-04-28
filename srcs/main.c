/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:56:15 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/28 19:57:18 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	display_selection(t_group *grp)
{
	int		i;
	int		select;
	t_elem	*curr;

	i = -1;
	select = 0;
	curr = grp->first;
	clear_elements();
	while (curr != NULL)
	{
		if (curr->selected == true)
		{
			select > 0 ? ft_putchar(' ') : 0;
			ft_putstr(curr->name);
			select++;
		}
		curr = curr->next;
	}
	reset_shell();
}

void	init_selection(t_group *grp, char **argv)
{
	int	i;

	i = 0;
	init_shell();
	set_shell((~ICANON & ~ECHO));
	while (argv[++i])
		insert_elem(grp, argv[i]);
	grp->first->curs_on = true;
	grp->curs_pos = 2;
	grp->curr = grp->first;
	handler_display(grp, 1);
}

void	unselect_all(t_group *grp)
{
	t_elem	*curr;
	int		i;

	i = 0;
	curr = grp->first;
	while (curr != NULL)
	{
		if (curr->selected == true)
		{
			i++;
			curr->selected = false;
		}
		curr = curr->next;
	}
	i > 0 ? handler_display(grp, 0) : 0;
}

int		key_selection(t_group *grp, int key)
{
	if (grp->is_locked == false && grp->is_search == false)
	{
		if (key == ENTER)
			return (ENTER);
		if (key == ARROW_L || key == ARROW_R ||
			key == ARROW_U || key == ARROW_D)
			handling_arrow(grp, key);
		else if (key == SPACE)
			handling_space(grp);
		else if (key == BACKSPACE || key == DEL)
			handling_backspace(grp);
		else if (key == CTRL_R)
			init_search(grp);
		else if (key == 'd')
			unselect_all(grp);
	}
	else if (grp->is_locked == false && grp->is_search == true)
		handling_search(grp, key);
	if (key == ESC)
	{
		reset_shell();
		clear_elements();
		exit(0);
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_group	*grp;
	int		key;
	char	order[BUF_SIZE + 1];
	char	tmp[512];

	argc < 2 ? exit(0) : 0;
	sig_handler();
	grp = init_grp();
	init_selection(grp, argv);
	ft_bzero(order, BUF_SIZE + 1);
	while (read(0, order, BUF_SIZE))
	{
		key = KEY(order[0], order[1], order[2], order[3]);
		if (key_selection(grp, key) == ENTER)
			break ;
		ft_bzero(order, BUF_SIZE + 1);
	}
	display_selection(grp);
	return (0);
}
