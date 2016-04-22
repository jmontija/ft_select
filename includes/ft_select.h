/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:58:47 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/22 18:19:14 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <stdio.h>
# include "libft.h"
# include "get_next_line.h"
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/xattr.h>
# include <sys/acl.h>
# include <termios.h>
# include <term.h>
# include <signal.h>
# include <curses.h>

# define BUF_SIZE 3
# define ENTER 10
# define SPACE 32
# define ARROW 27
# define ARROW_L 68
# define ARROW_U 65
# define ARROW_R 67
# define ARROW_D 66

enum {x, y};

typedef struct		s_elem
{
	char			*name;
	int				curs_on;
	int				selected;
	int				pos;
	int				last;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_group
{
	struct s_elem	**first;
	struct s_elem	**last;
	int				curs_pos;
	int				curr_col;
	int				last_col;
	int				last_elem;
	int				*window;
}					t_group;

t_group				*init_grp(void);
int					init_shell();
int					set_shell(int lflag);
int					reset_shell();
int					ft_getchar(int c);
int					insert_elem(t_group *grp, char *name, int col);
int					padding_max(t_elem *curr);
void				ft_tputs(char *cap_code);
void				handling_arrow(t_group *grp, int c);
void				handling_space();

#endif