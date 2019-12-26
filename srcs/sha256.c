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

t_wd		revers_t_wd(t_wd n)
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
		ssl->byte_32[i] = revers_t_wd(ssl->byte_32[i]);
		++i;
	}
	ssl->byte_32[((ssl->str * 512 - 64) / 32) + 1] = ssl->datalen;
	return (0);
}

static int	padding_sha224(char *str, int len, t_ssl *ssl)
{
	int	i;

	ssl->state[0] = 0xc1059ed8;
	ssl->state[1] = 0x367cd507;
	ssl->state[2] = 0x3070dd17;
	ssl->state[3] = 0xf70e5939;
	ssl->state[4] = 0x68581511;
	ssl->state[5] = 0xffc00b31;
	ssl->state[6] = 0x64f98fa7;
	ssl->state[7] = 0xbefa4fa4;
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
		ssl->byte_32[i] = revers_t_wd(ssl->byte_32[i]);
		++i;
	}
	ssl->byte_32[((ssl->str * 512 - 64) / 32) + 1] = ssl->datalen;
	return (0);
}

static void	round_word_sha224(t_ssl *ssl, int i)
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

static void	round_word_sha256(t_ssl *ssl, int i)
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



int			sha224(t_ssl *ssl, char *str, int len)
{
	int i;
	int j;

	padding_sha224(str, len, ssl);
	i = 0;
	while (i < ssl->str)
	{
		round_word_sha224(ssl, i);
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

int			sha256(t_ssl *ssl, char *str, int len)
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
