/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 17:27:00 by sko               #+#    #+#             */
/*   Updated: 2019/12/21 17:27:01 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_WD		g_t_sha[64] =
{
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

t_WD 		revers_t_WD(t_WD n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) |
			((n & 0xff00) << 8) | (n << 24));
}

static int	padding_sha256(char *str, int len, t_ssl *ssl)
{
	int	i;
	ssl->state[0] = 0x6a09e667;
	ssl->state[1] = 0xbb67ae85;
	ssl->state[2] = 0x3c6ef372;
	ssl->state[3] = 0xa54ff53a;
	ssl->state[4] = 0x510e527f;
	ssl->state[5] = 0x9b05688c;
	ssl->state[6] = 0x1f83d9ab;
	ssl->state[7] = 0x5be0cd19;

	ssl->datalen = len * 8;
	ssl->str = 1 + ((ssl->datalen + 16 + 64) / 512);
	if (!(ssl->byte_32 = malloc(16 * ssl->str * 4)))
		return (-1);
	ft_bzero(ssl->byte_32, 16 * ssl->str * 4);
	ft_memcpy((char *)ssl->byte_32, str, ft_strlen(str));
	((char *)ssl->byte_32)[ft_strlen(str)] = 0x80;
	i = 0;
	while (i < (ssl->str * 16) - 1)
	{
		ssl->byte_32[i] = revers_t_WD(ssl->byte_32[i]);
		++i;
	}
	ssl->byte_32[((ssl->str * 512 - 64) / 32) + 1] = ssl->datalen;
	return (0);
}

static void round_word_sha256(t_ssl *ssl, int i)
{
	int j;

	ssl->t = malloc(512);
	ft_bzero(ssl->t, 512);
	ft_memcpy(ssl->t, &ssl->byte_32[i * 16], 16 * 32);
	j = 16;
	while (j < 64)
	{
		ssl->s_data[0] = rot_right(ssl->t[j - 15], 7) ^ \
			rot_right(ssl->t[j - 15], 18) ^ (ssl->t[j - 15] >> 3);
		ssl->s_data[1] = rot_right(ssl->t[j - 2], 17) ^ \
			rot_right(ssl->t[j - 2], 19) ^ (ssl->t[j - 2] >> 10);
		ssl->t[j] = ssl->t[j - 16] + ssl->s_data[0] + \
			ssl->t[j - 7] + ssl->s_data[1];
		++j;
	}
	ssl->a = ssl->state[0];
	ssl->b = ssl->state[1];
	ssl->c = ssl->state[2];
	ssl->d = ssl->state[3];
	ssl->e = ssl->state[4];
	ssl->f = ssl->state[5];
	ssl->g = ssl->state[6];
	ssl->h = ssl->state[7];
}

t_WD		s1(t_WD x)
{
	t_WD tmp;

	tmp = rot_right(x, 6) ^ rot_right(x, 11) ^ rot_right(x, 25);
	return (tmp);
}

t_WD 		ch(t_WD x, t_WD y, t_WD z)
{
	t_WD tmp;

	tmp = (x & y) ^ (~x & z);
	return (tmp);
}

t_WD		s0(t_WD x)
{
	t_WD tmp;

	tmp = rot_right(x, 2) ^ rot_right(x, 13) ^ rot_right(x, 22);
	return (tmp);
}

t_WD 		maj(t_WD x, t_WD y, t_WD z)
{
	t_WD tmp;

	tmp = (x & y) ^ (x & z) ^ (y & z);
	return (tmp);
}

static void	swap_words(t_ssl *ssl, int i)
{
	ssl->s_data[1] = s1(ssl->e);
	ssl->s_data[2] = ch(ssl->e, ssl->f, ssl->g);
	ssl->s_data[3] = ssl->h + ssl->s_data[1] + \
		ssl->s_data[2] + g_t_sha[i] + ssl->t[i];
	ssl->s_data[0] = s0(ssl->a);
	ssl->s_data[4] = maj(ssl->a, ssl->b, ssl->c);
	ssl->s_data[5] = ssl->s_data[0] + ssl->s_data[4];
	ssl->h = ssl->g;
	ssl->g = ssl->f;
	ssl->f = ssl->e;
	ssl->e = ssl->d + ssl->s_data[3];
	ssl->d = ssl->c;
	ssl->c = ssl->b;
	ssl->b = ssl->a;
	ssl->a = ssl->s_data[3] + ssl->s_data[5];
}

int 		sha256(t_ssl *ssl, char *str, int len)
{
	int i;
	int j;

	padding_sha256(str, len, ssl);
	i = 0;
	while (i < ssl->str)
	{
		round_word_sha256(ssl, i);
		j = -1;
		while (++j < 64)
			swap_words(ssl, j);
		ssl->state[0] += ssl->a;
		ssl->state[1] += ssl->b;
		ssl->state[2] += ssl->c;
		ssl->state[3] += ssl->d;
		ssl->state[4] += ssl->e;
		ssl->state[5] += ssl->f;
		ssl->state[6] += ssl->g;
		ssl->state[7] += ssl->h;
		free(ssl->t);
		++i;
	}
	free(ssl->byte_32);
	return (0);
}