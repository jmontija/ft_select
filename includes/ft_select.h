/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julio <julio@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/31 15:58:47 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/28 00:46:16 by julio            ###   ########.fr       */
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
# include <sys/ioctl.h>

# define BUF_SIZE 4
# define PADDING
# define FIRT_ROW 2
# define ENTER 10
# define SPACE 32
# define TAB 9
# define ESC 27
# define ARROW_L 4479771
# define ARROW_U 4283163
# define ARROW_R 4414235
# define ARROW_D 4348699
# define BACKSPACE 127
# define CTRL_R 18
# define KEY(a, b, c, d) ((d << 24) + (c << 16) + (b << 8) + a)

enum {x, y};

typedef struct		s_elem
{
	char			*name;
	int				curs_on;
	int				selected;
	int				line;
	int				padding;
	struct s_elem	*next;
}					t_elem;

typedef struct		s_group
{
	struct s_elem	*first;
	struct s_elem	*last;
	struct s_elem	*curr;
	char			*search;
	int				is_locked;
	int				is_search;
	int				curs_pos;
	int				*window;
}					t_group;

t_group				*init_grp(void);
t_elem				*reset_underline(t_group *grp, int c);
int					init_shell(void);
int					set_shell(int lflag);
int					reset_shell(void);
int					insert_elem(t_group *grp, char *name);
int					display_elements(t_group *grp, int first);
void				clear_elements(void);
int					padding_max(t_elem *curr);
int					ft_getchar(int c);
void				ft_tputs(char *cap_code);
void				handler_display(t_group *grp, int first);
void				handling_arrow(t_group *grp, int c);
void				handling_backspace(t_group *grp);
void				handling_space(t_group *grp);
void				handle_reg(t_group *grp, char *cap_code, int c);
void				handle_spec(t_group *grp, t_elem *curr, int c);
void				handle_lr(int lr, t_group *grp);
void				sig_handler(void);
void				init_search(t_group *grp);
void				display_search(struct winsize window);
void				handling_search(t_group *grp, int key);

#endif