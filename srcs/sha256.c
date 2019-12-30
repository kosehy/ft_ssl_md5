/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 17:27:00 by sko               #+#    #+#             */
/*   Updated: 2019/12/29 21:48:20 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		sha256_padding(char *str, uint32_t **input, t_ssl *ssl)
{
	int			i;
	size_t		n;

	n = 0;
	i = 0;
	while (n < ssl->len)
	{
		input[i][n % 64 / 4] |= ((str[n] << (3 - ((n) % 4)) * 8) &
								 (0xffffffff >> (((n) % 4)) * 8));
		(((++n) % 64)) == 0 ? i++ : 0;
	}
	input[i][(n) % 64 / 4] |= 0x80 << (3 - ((n) % 4)) * 8;
	input[ssl->blocks - 1][14] = (uint32_t)((ssl->len * 8) >> 32);
	input[ssl->blocks - 1][15] = (uint32_t)((ssl->len * 8) & 0xffffffff);
}

/*
** prepare the message schedule
** @param input
** @param ssl
** @param i
** @param rnd
*/

void		sha256_round_word(uint32_t *input, t_ssl *ssl, int i)
{
	int j;

	while (++i < 16)
		ssl->w[i] = input[i];
	i -= 1;
	while (++i < 64)
	{
		ssl->s_data[0] = rot_right(ssl->w[i - 15], 7) ^ \
			rot_right(ssl->w[i - 15], 18) ^ (ssl->w[i - 15] >> 3);
		ssl->s_data[1] = rot_right(ssl->w[i - 2], 17) ^ \
			rot_right(ssl->w[i - 2], 19) ^ (ssl->w[i - 2] >> 10);
		ssl->w[i] = ssl->w[i - 16] + ssl->s_data[0] + \
			ssl->w[i - 7] + ssl->s_data[1];
	}
	sha256_var_assign(ssl, '<');
	j = -1;
	while (++j < 64)
		swap_words(ssl, j);
	sha256_var_assign(ssl, '>');
}

void		sha256_process(uint32_t **input, t_ssl *ssl)
{
	int		j;

	j = 0;
	init_sha256(ssl);
	while (j < ssl->blocks)
	{
		sha256_round_word(input[j], ssl, -1);
		j++;
	}
}

int			sha256(t_ssl *ssl, char *str, int len)
{
	int 		i;
	uint32_t	**input;

	i = -1;
	ssl->len = len;
	len = ssl->len * 8 + 1;
	while (len % 512 != 448)
		len++;
	ssl->blocks = (len += 64) / 512;
	input = (uint32_t **) malloc(sizeof(uint32_t *) * ssl->blocks);
	while (++i < ssl->blocks)
	{
		input[i] = (uint32_t *) malloc(sizeof(uint32_t) * 16);
		ft_bzero(input[i], sizeof(uint32_t) * 16);
	}
	sha256_padding(str, input, ssl);
	sha256_process(input, ssl);
	i = -1;
	while (++i < ssl->blocks)
		free(input[i]);
	free(input);
	return (1);
}
