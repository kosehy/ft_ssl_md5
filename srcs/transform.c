/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 13:01:15 by sko               #+#    #+#             */
/*   Updated: 2019/11/25 13:01:24 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_WD		g_t[64] =
{
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

t_WD		g_s[64] =
{
	7, 12, 17, 22,
	7, 12, 17, 22,
	7, 12, 17, 22,
	7, 12, 17, 22,
	5, 9, 14, 20,
	5, 9, 14, 20,
	5, 9, 14, 20,
	5, 9, 14, 20,
	4, 11, 16, 23,
	4, 11, 16, 23,
	4, 11, 16, 23,
	4, 11, 16, 23,
	6, 10, 15, 21,
	6, 10, 15, 21,
	6, 10, 15, 21,
	6, 10, 15, 21
};

/* Process each 16-word block. */
//For i = 0 to N/16-1 do
//	/* Copy block i into X. */
//	For j = 0 to 15 do
//	Set X[j] to M[i*16+j].
//	end /* of loop on j */

void		*make_zero(void *s, size_t n)
{
	unsigned char	*i;
	size_t			b;

	b = 0;
	i = (unsigned char *)s;
	while (b < n)
	{
		i[b] = '\0';
		++b;
	}
	return (s);
}

//static int	padding_md5(unsigned char *str, int len, t_ssl *ssl)
//{
//	ssl->datalen = len + 1;
//	while (ssl->datalen % 64 != 56)
//		ssl->datalen++;
//	if (!(ssl->byte = malloc(ssl->datalen + 64)))
//		return (-1);
//	ssl->byte = make_zero(ssl->byte, ssl->datalen + 64);
//	ft_strcpy((char*)ssl->byte + len, (const char *)str);
//	*(t_WD*)(ssl->byte + len) = 0x80;
//	*(t_WD*)(ssl->byte + ssl->datalen) = (t_WD)(8 * len);
//	ssl->str = 0;
//	return (0);
//}

void		process_message(t_ssl *ssl)
{
	t_WD	i;

	i = 0;
	while (i < 16)
	{
		ssl->m[i] = (ssl->data[i * 4 + 0]) + (ssl->data[i * 4 + 1] << 8) +\
		(ssl->data[i * 4 + 2] << 16) + (ssl->data[i * 4 + 3] << 24);
		++i;
	}
}

void		aux_f(t_ssl *ssl, t_WD i)
{
	ssl->f = F(ssl->b, ssl->c, ssl->d);
	ssl->g = i;
}

void		aux_g(t_ssl *ssl, t_WD i)
{
	ssl->f = G(ssl->b, ssl->c, ssl->d);
	ssl->g = i;
}

void		aux_h(t_ssl *ssl, t_WD i)
{
	ssl->f = H(ssl->b, ssl->c, ssl->d);
	ssl->g = i;
}

void		aux_i(t_ssl *ssl, t_WD i)
{
	ssl->f = I(ssl->b, ssl->c, ssl->d);
	ssl->g = i;
}

t_WD 		rot_left(t_WD x, t_WD n)
{
	t_WD	tmp;

	tmp = (x << n) | (x >> (32 - n));
	return (tmp);
}

void		simple_transform(t_ssl *ssl)
{
	t_WD	i;
	t_WD	f;
	t_WD	g;
	t_WD	tmp;

	process_message(ssl);
	ssl->a = ssl->state[0];
	ssl->b = ssl->state[1];
	ssl->c = ssl->state[2];
	ssl->d = ssl->state[3];
	i = 0;
	while (i < 64)
	{
		if (i <= 15)
		{
			f = F(ssl->b, ssl->c, ssl->d);
			g = i;
		}
		else if (i >= 16 && i <= 31)
		{
			f = G(ssl->b, ssl->c, ssl->d);
			g = (i * 5 + 1) % 16;
		}
		else if (i >= 32 && i <= 47)
		{
			f = H(ssl->b, ssl->c, ssl->d);
			g = (i * 3 + 5) % 16;
		}
		else if (i >= 48)
		{
			f = I(ssl->b, ssl->c, ssl->d);
			g = (i * 7) % 16;
		}
		tmp = ssl->d;
		ssl->d = ssl->c;
		ssl->c = ssl->b;
		printf("i        : %d\n", i);
		printf("ssl->b   : %u\n", ssl->b);
		printf("ssl->a   : %u\n", ssl->a);
		printf("f        : %u\n", f);
		printf("g_t[i]   : %u\n", g_t[i]);
		printf("ssl->m[g]: %u\n", ssl->m[g]);
		printf("g_s[i]   : %u\n", g_s[i]);
		ssl->b += rot_left(ssl->a + f + g_t[i] + ssl->m[g], g_s[i]);
		ft_printf("ssl->b : %u\n", ssl->b);
		ssl->a = tmp;
		++i;
	}
	ssl->state[0] += ssl->a;
	ssl->state[1] += ssl->b;
	ssl->state[2] += ssl->c;
	ssl->state[3] += ssl->d;
}