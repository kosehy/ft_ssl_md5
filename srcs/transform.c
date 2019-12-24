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

void		round_word(t_ssl *ssl, int i)
{
	t_WD	tmp;

	if (i <= 15)
		aux_f(ssl, i);
	else if (i >= 16 && i <= 31)
		aux_g(ssl, i);
	else if (i >= 32 && i <= 47)
		aux_h(ssl, i);
	else if (i >= 48)
		aux_i(ssl, i);
	tmp = ssl->d;
	ssl->d = ssl->c;
	ssl->c = ssl->b;
//	printf("i        : %d\n", i);
//	printf("ssl->b   : %u\n", ssl->b);
//	printf("ssl->a   : %u\n", ssl->a);
//	printf("ssl->f   : %u\n", ssl->f);
//	printf("g_t[i]   : %u\n", g_t[i]);
//	printf("ssl->m[g]: %u\n", ssl->t[ssl->g]);
//	printf("g_s[i]   : %u\n", g_s[i]);
	ssl->b += rot_left(ssl->a + ssl->f + g_t[i] + ssl->t[ssl->g], g_s[i]);
//	ft_printf("ssl->b : %u\n", ssl->b);
	ssl->a = tmp;
	++i;
}

void		*void_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t 			b;

	b = 0;
	ptr = (unsigned char*)s;
	while (b < n)
	{
		ptr[b] = '\0';
		++b;
	}
	return (s);
}

static int	padding_md5(unsigned char *str, int len, t_ssl *ssl)
{
	ssl->state[0] = 0x67452301;
	ssl->state[1] = 0xefcdab89;
	ssl->state[2] = 0x98badcfe;
	ssl->state[3] = 0x10325476;
	ssl->datalen = len + 1;
	while (ssl->datalen % 64 != 56)
		ssl->datalen++;
	if (!(ssl->byte = malloc(ssl->datalen + 64)))
		return (-1);
	ssl->byte = void_bzero(ssl->byte, ssl->datalen + 64);
	ft_strcpy((char *)ssl->byte, (char *)str);
	*(t_WD *)(ssl->byte + len) = 0x80;
	*(t_WD *)(ssl->byte + ssl->datalen) = (t_WD)(8 * len);
	ssl->str = 0;
	return (0);
}

int			md5(t_ssl *ssl, unsigned char * str, int len)
{
	int	i;

	if (padding_md5(str, len, ssl) == -1)
		return (-1);
	while (ssl->str < ssl->datalen)
	{
		ssl->t = (t_WD *)(ssl->byte + ssl->str);
		ssl->a = ssl->state[0];
		ssl->b = ssl->state[1];
		ssl->c = ssl->state[2];
		ssl->d = ssl->state[3];
		i = -1;
		while (++i < 64)
			round_word(ssl, i);
		ssl->state[0] += ssl->a;
		ssl->state[1] += ssl->b;
		ssl->state[2] += ssl->c;
		ssl->state[3] += ssl->d;
		ssl->str += 64;
	}
	free(ssl->byte);
	return (0);
}