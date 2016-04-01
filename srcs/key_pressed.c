/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_pressed.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 16:00:29 by jmontija          #+#    #+#             */
/*   Updated: 2016/04/01 16:07:08 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

void	arrow_LEFT()
{
	ft_putstr("arrow_LEFT");
}

void	arrow_UP()
{
	ft_putstr("arrow_UP");
}

void	arrow_RIGHT()
{
	ft_putstr("arrow_RIGHT");
}

void	arrow_DOWN()
{
	ft_putstr("arrow_DOWN");
}

void	handling_arrow(int c)
{
	c == ARROW_L ?  arrow_LEFT() : 0;
	c == ARROW_U ?  arrow_UP() : 0;
	c == ARROW_R ?  arrow_RIGHT() : 0;
	c == ARROW_D ?  arrow_DOWN() : 0;
}
