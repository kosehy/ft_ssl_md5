/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/26 13:18:24 by sko               #+#    #+#             */
/*   Updated: 2019/12/26 13:18:25 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static uint64_t	g_t_sha512[80] =
{
	0x428a2f98d728ae22, 0x7137449123ef65cd,
	0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
	0x3956c25bf348b538, 0x59f111f1b605d019,
	0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
	0xd807aa98a3030242, 0x12835b0145706fbe,
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
	0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
	0x9bdc06a725c71235, 0xc19bf174cf692694,
	0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
	0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
	0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
	0x983e5152ee66dfab, 0xa831c66d2db43210,
	0xb00327c898fb213f, 0xbf597fc7beef0ee4,
	0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70,
	0x27b70a8546d22ffc, 0x2e1b21385c26c926,
	0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
	0x650a73548baf63de, 0x766a0abb3c77b2a8,
	0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001,
	0xc24b8b70d0f89791, 0xc76c51a30654be30,
	0xd192e819d6ef5218, 0xd69906245565a910,
	0xf40e35855771202a, 0x106aa07032bbd1b8,
	0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
	0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
	0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
	0x748f82ee5defb2fc, 0x78a5636f43172f60,
	0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9,
	0xbef9a3f7b2c67915, 0xc67178f2e372532b,
	0xca273eceea26619c, 0xd186b8c721c0c207,
	0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
	0x06f067aa72176fba, 0x0a637dc5a2c898a6,
	0x113f9804bef90dae, 0x1b710b35131c471b,
	0x28db77f523047d84, 0x32caab7b40c72493,
	0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
	0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
	0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

u_int64_t				rot_right_64(u_int64_t x, u_int64_t n)
{
	u_int64_t	tmp;

	tmp = (x >> n) | (x << (32 - n));
	return (tmp);
}

u_int64_t				s1_64(u_int64_t x)
{
	u_int64_t tmp;

	tmp = rot_right_64(x, 6) ^ rot_right_64(x, 11) ^ rot_right_64(x, 25);
	return (tmp);
}

u_int64_t				ch_64(u_int64_t x, u_int64_t y, u_int64_t z)
{
	u_int64_t tmp;

	tmp = (x & y) ^ (~x & z);
	return (tmp);
}

u_int64_t				s0_64(u_int64_t x)
{
	u_int64_t tmp;

	tmp = rot_right_64(x, 2) ^ rot_right_64(x, 13) ^ rot_right_64(x, 22);
	return (tmp);
}

u_int64_t				maj_64(u_int64_t x, u_int64_t y, u_int64_t z)
{
	u_int64_t tmp;

	tmp = (x & y) ^ (x & z) ^ (y & z);
	return (tmp);
}

void					swap_words_512(t_s5 *ssl, int i)
{
	ssl->s_data[1] = s1_64(ssl->e);
	ssl->s_data[2] = ch_64(ssl->e, ssl->f, ssl->g);
	ssl->s_data[3] = ssl->h + ssl->s_data[1] + \
		ssl->s_data[2] + g_t_sha512[i] + ssl->t[i];
	ssl->s_data[0] = s0_64(ssl->a);
	ssl->s_data[4] = maj_64(ssl->a, ssl->b, ssl->c);
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

u_int64_t				revers_64(u_int64_t n)
{
	return ((n >> 48) | ((n & 0x0000ffff00000000) >> 16) |
			((n & 0x00000000ffff0000) << 16) | (n << 48));
}

static int				padding_sha512(char *str, int len, t_s5 *ssl)
{
	int	i;
	int	index;

	if (ft_strcmp(ssl->type, "sha512") == 0)
		init_sha512(ssl);
	ssl->datalen = len * 8;
	ssl->str = 1 + ((ssl->datalen + 16 + 64) / 1024);
	if (!(ssl->byte_64 = malloc(16 * ssl->str * 4)))
		return (-1);
	ft_bzero(ssl->byte_64, 16 * ssl->str * 4);
	ft_memcpy((char *)ssl->byte_64, str, ft_strlen(str));
	((char *)ssl->byte_64)[len] = 0x80;
	i = 0;
	while (i < (ssl->str * 16) - 1)
	{
		ssl->byte_64[i] = revers_64(ssl->byte_64[i]);
		++i;
	}
	index = (ssl->str * 1024 - 128) / 64;
	ssl->byte_64[index + 1] = ssl->datalen;
	return (0);
}

/*
** Block size 1024 bits
**
*/

static void				round_word_sha512(t_s5 *ssl, int i)
{
	int j;

	ssl->t = malloc(1024);
	ft_bzero(ssl->t, 1024);
	ft_memcpy(ssl->t, &ssl->byte_64[i * 16], 16 * 64);
	j = 16;
	while (j < 80)
	{
		ssl->s_data[0] = rot_right_64(ssl->t[j - 15], 7) ^ \
			rot_right_64(ssl->t[j - 15], 18) ^ (ssl->t[j - 15] >> 3);
		ssl->s_data[1] = rot_right_64(ssl->t[j - 2], 17) ^ \
			rot_right_64(ssl->t[j - 2], 19) ^ (ssl->t[j - 2] >> 10);
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

int			sha512(t_s5 *ssl, char *str, int len)
{
	int i;
	int j;

	padding_sha512(str, len, ssl);
	i = 0;
	while (i < ssl->str)
	{
		round_word_sha512(ssl, i);
		j = -1;
		while (++j < 80)
			swap_words_512(ssl, j);
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
	free(ssl->byte_64);
	return (0);
}
