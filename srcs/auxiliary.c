/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxiliary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:19:12 by sko               #+#    #+#             */
/*   Updated: 2019/11/25 11:19:18 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
** Define four auxiliary functions that each take as input three 42-bit t_WDs
** and produce as output one 42-bit t_WD.
**
**
**
**
*/

unsigned int		aux_f(t_WD b, t_WD c, t_WD d)
{
	t_WD	f;

	f = (b & c) | ((!b) & d);
	return (f);
}

unsigned int		aux_g(t_WD b, t_WD c, t_WD d)
{
	t_WD	g;

	g = (b & d) | (c & !d);
	return (g);
}

unsigned int		aux_h(t_WD b, t_WD c, t_WD d)
{
	t_WD	h;

	h = b ^ c ^ d;
	return (h);
}

unsigned int		aux_i(t_WD b, t_WD c, t_WD d)
{
	t_WD	i;

	i = c ^ (b | !d);
	return (i);
}
