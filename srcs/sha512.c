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

# define RR(a, b) (((a) >> (b)) | ((a) << (64 - (b))))
# define CH(x, y, z) (((x) & (y)) ^ (~(x) & (z)))
# define MAJ(x, y, z) (((x) & (y)) ^ ((x) & (z)) ^ ((y) & (z)))
# define E0(x) (RR(x, 28) ^ RR(x, 34) ^ RR(x, 39))
# define E1(x) (RR(x, 14) ^ RR(x, 18) ^ RR(x, 41))
# define S0(x) (RR(x, 1) ^ RR(x, 8) ^ ((x) >> 7))
# define S1(x) (RR(x, 19) ^ RR(x, 61) ^ ((x) >> 6))

static uint64_t	g_words64[80] =
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

void		sha512_var_assign(t_s5 *ctx, char order)
{
	if (order == '<')
	{
		ctx->a = ctx->state[0];
		ctx->b = ctx->state[1];
		ctx->c = ctx->state[2];
		ctx->d = ctx->state[3];
		ctx->e = ctx->state[4];
		ctx->f = ctx->state[5];
		ctx->g = ctx->state[6];
		ctx->h = ctx->state[7];
	}
	else if (order == '>')
	{
		ctx->state[0] += ctx->a;
		ctx->state[1] += ctx->b;
		ctx->state[2] += ctx->c;
		ctx->state[3] += ctx->d;
		ctx->state[4] += ctx->e;
		ctx->state[5] += ctx->f;
		ctx->state[6] += ctx->g;
		ctx->state[7] += ctx->h;
	}
}

void		sha512_padding(char *str, uint64_t **input, t_s5 *ssl)
{
	int			i;
	size_t		n;
	int 		u;

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
	uint64_t	t1;
	uint64_t	t2;

	while (++i < 16)
		ssl->w[i] = input[i];
	i -= 1;
	while (++i < 80)
		ssl->w[i] = ssl->w[i - 16] + S0(ssl->w[i - 15]) + ssl->w[i - 7] + S1(ssl->w[i - 2]);
	sha512_var_assign(ssl, '<');
	j = -1;
	while (++j < 80)
	{
		t1 = ssl->h + E1(ssl->e) + CH(ssl->e, ssl->f, ssl->g)
			 + g_words64[j] + ssl->w[j];
		t2 = E0(ssl->a) + MAJ(ssl->a, ssl->b, ssl->c);
		ssl->h = ssl->g;
		ssl->g = ssl->f;
		ssl->f = ssl->e;
		ssl->e = ssl->d + t1;
		ssl->d = ssl->c;
		ssl->c = ssl->b;
		ssl->b = ssl->a;
		ssl->a = t1 + t2;
	}
	sha512_var_assign(ssl, '>');
}

void		sha512_process(uint64_t **input, t_s5 *ssl)
{
	int		j;

	j = 0;
	init_sha512(ssl);
	while (j < ssl->blocks)
	{
		sha512_round_word(input[j], ssl, -1);
		j++;
	}
}

int			sha512(t_s5 *ssl, char *str, int len)
{
	int 		i;
	uint64_t	**input;

	i = -1;
	ssl->len = len;
	len = ssl->len * 8 + 1;
	while (len % 1024 != 896)
		len++;
	ssl->blocks = (len += 128) / 1024;
	input = (uint64_t **) malloc(sizeof(uint64_t *) * ssl->blocks);
	while (++i < ssl->blocks)
	{
		input[i] = (uint64_t *) malloc(sizeof(uint64_t) * 16);
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