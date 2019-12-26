/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sha.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 12:34:26 by sko               #+#    #+#             */
/*   Updated: 2019/12/26 12:34:27 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		init_sha224(t_ssl *ssl)
{
	ssl->state[0] = 0xc1059ed8;
	ssl->state[1] = 0x367cd507;
	ssl->state[2] = 0x3070dd17;
	ssl->state[3] = 0xf70e5939;
	ssl->state[4] = 0xffc00b31;
	ssl->state[5] = 0x68581511;
	ssl->state[6] = 0x64f98fa7;
	ssl->state[7] = 0xbefa4fa4;
}

void		init_sha256(t_ssl *ssl)
{
	ssl->state[0] = 0x6a09e667;
	ssl->state[1] = 0xbb67ae85;
	ssl->state[2] = 0x3c6ef372;
	ssl->state[3] = 0xa54ff53a;
	ssl->state[4] = 0x510e527f;
	ssl->state[5] = 0x9b05688c;
	ssl->state[6] = 0x1f83d9ab;
	ssl->state[7] = 0x5be0cd19;
}
