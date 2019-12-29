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
	return ((n >> 24) | ((n & 0x00ff0000) >> 8) |
			((n & 0x0000ff00) << 8) | (n << 24));
}

static int	padding_sha256(char *str, int len, t_ssl *ssl)
{
	int	i;
	int	index;

	if (ft_strcmp(ssl->type, "sha224") == 0)
		init_sha224(ssl);
	else if (ft_strcmp(ssl->type, "sha256") == 0)
		init_sha256(ssl);
	ssl->datalen = len * 8;
	ssl->str = 1 + ((ssl->datalen + 16 + 64) / 512);
	// if plain text length is less than 512bits, make 512 bits message.
	// Otherwise, str * 512 bits message
	if (!(ssl->byte_32 = malloc(16 * ssl->str * 4)))
		return (-1);
	// zero initialize
	ft_bzero(ssl->byte_32, 16 * ssl->str * 4);
	// copy plain text to message(byte_32)
	ft_memcpy((char *)ssl->byte_32, str, len);
	// append the bit "1" to the end of the messagee
	((char *)ssl->byte_32)[len] = 0x80;
	i = 0;
	// big endian to little endian conversion
	while (i < (ssl->str * 16) - 1)
	{
		ssl->byte_32[i] = revers_t_wd(ssl->byte_32[i]);
		++i;
	}
	// put the plain text length
	index = (ssl->str * 512 - 64) / 32;
	ssl->byte_32[index + 1] = ssl->datalen;
	return (0);
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
