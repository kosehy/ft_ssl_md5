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

t_wd					rot_right(t_wd x, t_wd n)
{
	t_wd	tmp;

	tmp = (x >> n) | (x << (32 - n));
	return (tmp);
}

void					aux_f(t_ssl *ssl, t_wd i)
{
	ssl->f = (ssl->b & ssl->c) | (~ssl->b & ssl->d);
	ssl->g = i;
}

void					aux_g(t_ssl *ssl, t_wd i)
{
	ssl->f = (ssl->b & ssl->d) | (ssl->c & ~ssl->d);
	ssl->g = (i * 5 + 1) % 16;
}

void					aux_h(t_ssl *ssl, t_wd i)
{
	ssl->f = (ssl->b ^ ssl->c ^ ssl->d);
	ssl->g = (i * 3 + 5) % 16;
}

void					aux_i(t_ssl *ssl, t_wd i)
{
	ssl->f = ssl->c ^ (ssl->b | ~ssl->d);
	ssl->g = (i * 7) % 16;
}
