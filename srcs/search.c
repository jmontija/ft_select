/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 19:39:22 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/28 01:44:39 by julio            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	display_search(struct winsize window)
{
	int	i;

	i = -1;
	ft_putstr_fd("\033[1;32m", 2);
	ft_putendl_fd("search ->", 2);
	ft_tputs("us");
	while (++i < (window.ws_col))
		ft_putchar_fd(' ', 2);
	ft_putstr_fd("\033[0;m", 2);
	ft_tputs("ue");
}

t_elem	*find_search(t_group *grp, char *search)
{
	t_elem *curr;

	curr = grp->first;
	reset_underline(grp, 0);
	grp->curr = NULL;
	while (curr != NULL)
	{
		if (ft_strncmp(search, curr->name, ft_strlen(search)) == 0)
			break;
		curr = curr->next;
	}
	if (curr != NULL)
		handle_spec(grp, curr, -1);
	grp->curs_pos = 10 + ft_strlen(search);
	tputs(tgoto(tgetstr("cm", NULL), grp->curs_pos, 0), 1, ft_getchar);
	return (curr);
}

void	init_search(t_group *grp)
{
	ft_tputs("ve");
	reset_underline(grp, 0);
	grp->curr = NULL;
	if (grp->is_search)
	{
		tputs(tgoto(tgetstr("cm", NULL), 10, 0), 1, ft_getchar);
		ft_putstr_fd(grp->search, 2);
	}
	if (ft_strlen(grp->search) > 0)
		find_search(grp, grp->search);
	grp->is_search = true;
	grp->curs_pos = 10 + ft_strlen(grp->search);
	tputs(tgoto(tgetstr("cm", NULL), grp->curs_pos, 0), 1, ft_getchar);
}

char	*ft_charjoin(char *s1, char c)
{
	char	*dup;
	size_t	size;

	size = ft_strlen(s1) + 1;
	dup = ft_strnew(size);
	dup = ft_strcpy(dup, s1);
	dup[size - 1] = c;
	dup[size] = '\0';
	return (dup);
}

char	*ft_free_char(char *s1)
{
	char	*new;
	size_t	size;

	size = ft_strlen(s1) - 1;
	new = ft_strnew(size);
	new = ft_strncpy(new, s1, size);
	return (new);
}

void	handling_search(t_group *grp, int key)
{
	int curs_pos = 0;
	int i = -1;
	t_elem *curr;

	if (key == ENTER)
	{
		ft_tputs("vi");
		grp->is_search = false;
		grp->curr ? handling_space(grp) : handle_spec(grp, grp->first, -1);
	}
	else if (key == BACKSPACE && grp->curs_pos > 10)
	{
		grp->curs_pos -= 1;
		tputs(tgoto(tgetstr("cm", NULL), grp->curs_pos, 0), 1, ft_getchar);
		ft_tputs("dc");
		grp->search = ft_free_char(grp->search);
		find_search(grp, grp->search);
	}
	else if (key == TAB)
	{
		curs_pos = grp->curs_pos;
		if (ft_strlen(grp->search) > 0 && grp->curr)
		{
			if (grp->curr->next &&
			ft_strncmp(grp->search, grp->curr->next->name, ft_strlen(grp->search)) == 0)
				handle_reg(grp, "do", ARROW_D);
			/*else
			{
				curr = grp->curr;
				while (curr != NULL)
				{
					if (ft_strncmp(grp->search, curr->name, ft_strlen(grp->search)) == 0)
						break ;
					curr = curr->next;
				}
				curr != NULL ? handle_spec(grp, curr, -1) : handle_spec(grp, grp->first, -1);
			}*/ // a checker
		}
		grp->curs_pos = curs_pos;
		tputs(tgoto(tgetstr("cm", NULL), curs_pos, 0), 1, ft_getchar);
	}
	else if (key == CTRL_R)
	{
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
	else if (ft_isprint(key))
	{
		grp->curs_pos += 1;
		ft_putchar_fd(key, 2);
		grp->search = ft_charjoin(grp->search, key);
		find_search(grp, grp->search);
	}
}