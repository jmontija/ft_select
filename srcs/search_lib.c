/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_lib.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 17:32:39 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/28 20:02:12 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

t_elem	*find_search(t_group *grp, char *search)
{
	t_elem *curr;

	curr = grp->first;
	reset_underline(grp, 0);
	grp->curr = NULL;
	while (curr != NULL)
	{
		if (ft_strncmp(search, curr->name, ft_strlen(search)) == 0)
			break ;
		curr = curr->next;
	}
	if (curr != NULL)
		handle_spec(grp, curr, -1);
	grp->curs_pos = 10 + ft_strlen(search);
	tputs(tgoto(tgetstr("cm", NULL), grp->curs_pos, 0), 1, ft_getchar);
	return (curr);
}

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
