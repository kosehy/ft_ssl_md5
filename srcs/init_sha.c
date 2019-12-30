/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sha.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/28 20:56:06 by sko               #+#    #+#             */
/*   Updated: 2019/12/28 20:56:07 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		init_sha256(t_ssl *ssl)
{
	if (ft_strcmp(ssl->type, "sha224") == 0)
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
	else if (ft_strcmp(ssl->type, "sha256") == 0)
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
}

void		init_sha384(t_s5 *ssl)
{
	ssl->state[0] = 0xcbbb9d5dc1059ed8;
	ssl->state[1] = 0x629a292a367cd507;
	ssl->state[2] = 0x9159015a3070dd17;
	ssl->state[3] = 0x152fecd8f70e5939;
	ssl->state[4] = 0x67332667ffc00b31;
	ssl->state[5] = 0x8eb44a8768581511;
	ssl->state[6] = 0xdb0c2e0d64f98fa7;
	ssl->state[7] = 0x47b5481dbefa4fa4;
}

void		init_sha512(t_s5 *ssl)
{
	ssl->state[0] = 0x6a09e667f3bcc908;
	ssl->state[1] = 0xbb67ae8584caa73b;
	ssl->state[2] = 0x3c6ef372fe94f82b;
	ssl->state[3] = 0xa54ff53a5f1d36f1;
	ssl->state[4] = 0x510e527fade682d1;
	ssl->state[5] = 0x9b05688c2b3e6c1f;
	ssl->state[6] = 0x1f83d9abfb41bd6b;
	ssl->state[7] = 0x5be0cd19137e2179;
}

void		init_sha512t(t_s5 *ssl)
{
	if (ft_strcmp(ssl->type, "sha512224") == 0)
	{
		ssl->state[0] = 0x8C3D37C819544DA2;
		ssl->state[1] = 0x73E1996689DCD4D6;
		ssl->state[2] = 0x1DFAB7AE32FF9C82;
		ssl->state[3] = 0x679DD514582F9FCF;
		ssl->state[4] = 0x0F6D2B697BD44DA8;
		ssl->state[5] = 0x77E36F7304C48942;
		ssl->state[6] = 0x3F9D85A86A1D36C8;
		ssl->state[7] = 0x1112E6AD91D692A1;
	}
	else if (ft_strcmp(ssl->type, "sha512256") == 0)
	{
		ssl->state[0] = 0x22312194FC2BF72C;
		ssl->state[1] = 0x9F555FA3C84C64C2;
		ssl->state[2] = 0x2393B86B6F53B151;
		ssl->state[3] = 0x963877195940EABD;
		ssl->state[4] = 0x96283EE2A88EFFE3;
		ssl->state[5] = 0xBE5E1E2553863992;
		ssl->state[6] = 0x2B0199FC2C85B8AA;
		ssl->state[7] = 0x0EB72DDC81C52CA2;
	}
}
