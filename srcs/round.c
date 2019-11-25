/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   round.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:19:25 by sko               #+#    #+#             */
/*   Updated: 2019/11/25 11:19:30 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

WORD		rotleft(WORD a, int b)
{
	return ((a << b) | (a >> (32 - b)));
}

WORD		ff(WORD a, WORD b, WORD c, WORD d, WORD *m, int s, WORD t)
{
	a += aux_f(b, c, d) + m + t;
	a = b + rotleft(a, s);
}

WORD		gg(WORD a, WORD b, WORD c, WORD d, WORD *m, int s, WORD t)
{
	a += aux_g(b, c, d) + m + t;
	a = b + rotleft(a, s);
}

WORD		hh(WORD a, WORD b, WORD c, WORD d, WORD *m, int s, WORD t)
{
	a += aux_h(b, c, d) + m + t;
	a = b + rotleft(a, s);
}

WORD		ii(WORD a, WORD b, WORD c, WORD d, WORD *m, int s, WORD t)
{
	a += aux_i(b, c, d) + m + t;
	a = b + rotleft(a, s);
}