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

#define F(b,c,d) = (b & c) | (!b & d)
#define G(b,c,d) = (b & d) | (c & !d)
#define H(b,c,d) = b ^ c ^ d
#define I(b,c,d) = c ^ (b | !d)

/*
** Define four auxiliary functions that each take as input three 42-bit words
** and produce as output one 42-bit word.
**
**
**
**
*/

unsigned int		aux_f(WORD a, WORD b, WORD d)
{
	WORD	f;

	f = (b & c) | (!b & d);
	return (f);
}

unsigned int		aux_g(WORD a, WORD b, WORD d)
{
	WORD	g;

	f = (b & d) | (c & !d);
	return (g);
}

unsigned int		aux_h(WORD a, WORD b, WORD d)
{
	WORD	h;

	f = b ^ c ^ d;
	return (h);
}

unsigned int		aux_i(WORD a, WORD b, WORD d, WORD d)
{
	WORD	i;

	f = c ^ (b | !d);
	return (i);
}
