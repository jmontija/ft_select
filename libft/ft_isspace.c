/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmontija <jmontija@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 16:07:27 by jmontija          #+#    #+#             */
/*   Updated: 2016/03/04 22:26:29 by jmontija         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isspace(int c)
{
	if (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\f' ||
		c == '\v')
		return (1);
	else
		return (0);
}
