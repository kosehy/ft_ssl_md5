/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 21:48:27 by sko               #+#    #+#             */
/*   Updated: 2019/12/29 21:48:28 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void		sha512_var_assign(t_s5 *ssl, char order)
{
	if (order == '<')
	{
		ssl->a = ssl->state[0];
		ssl->b = ssl->state[1];
		ssl->c = ssl->state[2];
		ssl->d = ssl->state[3];
		ssl->e = ssl->state[4];
		ssl->f = ssl->state[5];
		ssl->g = ssl->state[6];
		ssl->h = ssl->state[7];
	}
	else if (order == '>')
	{
		ssl->state[0] += ssl->a;
		ssl->state[1] += ssl->b;
		ssl->state[2] += ssl->c;
		ssl->state[3] += ssl->d;
		ssl->state[4] += ssl->e;
		ssl->state[5] += ssl->f;
		ssl->state[6] += ssl->g;
		ssl->state[7] += ssl->h;
	}
}

void		sha512_padding(char *str, uint64_t **input, t_s5 *ssl)
{
	int			i;
	size_t		n;
	int			u;

	n = 0;
	i = 0;
	u = 56;
	while (n < ssl->len)
	{
		u = (n % 8 == 0 ? 56 : u - 8);
		input[i][n % 128 / 8] |= (((uint64_t)str[n] << u) &
			(0xffffffffffffffff >> (((n) % 8)) * 8));
		(((++n) % 128)) == 0 ? i++ : 0;
	}
	u = (n % 8 == 0 ? 56 : u - 8);
	input[i][(n) % 128 / 8] |= (uint64_t)0x80 << u;
	input[ssl->blocks - 1][14] = ((uint64_t)ssl->len * 8) >> 56;
	input[ssl->blocks - 1][15] = ((uint64_t)ssl->len * 8) & 0xffffffffffffffff;
}

void		sha512_round_word(uint64_t *input, t_s5 *ssl, int i)
{
	int j;

	while (++i < 16)
		ssl->w[i] = input[i];
	i -= 1;
	while (++i < 80)
	{
		ssl->s_data[0] = rot_right_64(ssl->w[i - 15], 1) ^ \
			rot_right_64(ssl->w[i - 15], 8) ^ (ssl->w[i - 15] >> 7);
		ssl->s_data[1] = rot_right_64(ssl->w[i - 2], 19) ^ \
			rot_right_64(ssl->w[i - 2], 61) ^ (ssl->w[i - 2] >> 6);
		ssl->w[i] = ssl->w[i - 16] + ssl->s_data[0] + \
			ssl->w[i - 7] + ssl->s_data[1];
	}
	sha512_var_assign(ssl, '<');
	j = -1;
	while (++j < 80)
		swap_words_512(ssl, j);
	sha512_var_assign(ssl, '>');
}

void		sha512_process(uint64_t **input, t_s5 *ssl)
{
	int		j;

	j = 0;
	if (ft_strcmp(ssl->type, "sha384") == 0)
		init_sha384(ssl);
	else if (ft_strcmp(ssl->type, "sha512") == 0)
		init_sha512(ssl);
	else if (ft_strcmp(ssl->type, "sha512224") == 0 || \
			ft_strcmp(ssl->type, "sha512256") == 0)
		init_sha512t(ssl);
	while (j < ssl->blocks)
	{
		sha512_round_word(input[j], ssl, -1);
		j++;
	}
}

int			sha512(t_s5 *ssl, char *str, int len)
{
	int			i;
	uint64_t	**input;

	i = -1;
	ssl->len = len;
	len = ssl->len * 8 + 1;
	while (len % 1024 != 896)
		len++;
	ssl->blocks = (len += 128) / 1024;
	input = (uint64_t **)malloc(sizeof(uint64_t *) * ssl->blocks);
	while (++i < ssl->blocks)
	{
		input[i] = (uint64_t *)malloc(sizeof(uint64_t) * 16);
		ft_bzero(input[i], sizeof(uint64_t) * 16);
	}
	sha512_padding(str, input, ssl);
	sha512_process(input, ssl);
	i = -1;
	while (++i < ssl->blocks)
		free(input[i]);
	free(input);
	return (1);
}
