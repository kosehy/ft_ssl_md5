/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:58:29 by sko               #+#    #+#             */
/*   Updated: 2019/11/23 20:58:58 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			md5_buffer_init(t_md5 *md5)
{
	md5->datalen = 0;
	md5->bitlen = 0;
	md5->state[0] = 0x67452301;
	md5->state[1] = 0xefcdab89;
	md5->state[2] = 0x98badcfe;
	md5->state[3] = 0x10325476;
}

void			check_text(t_md5 *md5, char *str)
{
	if (*str == '\0')
		return ;
	md5->datalen = 0;
	while (str[md5->datalen] != '\0')
	{
		md5->data[md5->datalen] = str[md5->datalen];
		++md5->datalen;
	}
}

void			check_md5(t_md5 *md5, char *str)
{
	t_WD i = 0;
	while (i < md5->datalen)
	{
		md5->data[i] = str[i];
		++i;
	}
	if (md5->datalen < 56)
	{
		md5->data[i++] = 0x80;
		while (i < 56)
		{
			md5->data[i] = 0x00;
			++i;
		}
	}
	else if (md5->datalen >= 56)
	{
		md5->data[i] = 0x80;
		while (i < 64)
		{
			md5->data[i] = 0x00;
			++i;
		}
		transform(md5);
		ft_memset(md5->data, 0, 56);
	}
	md5->bitlen = md5->datalen * 8;
	md5->data[56] = md5->bitlen;
	md5->data[57] = md5->bitlen >> 8;
	md5->data[58] = md5->bitlen >> 16;
	md5->data[59] = md5->bitlen >> 24;
	md5->data[60] = md5->bitlen >> 32;
	md5->data[61] = md5->bitlen >> 40;
	md5->data[62] = md5->bitlen >> 48;
	md5->data[63] = md5->bitlen >> 56;
	transform(md5);
}

//#define FF(a,b,c,d,m,s,t) { a += F(b,c,d) + m + t; \
//                            a = b + ROTLEFT(a,s); }

void	mf(t_WD a, t_WD b, t_WD c, t_WD d, t_WD *m, t_md5 *md5)
{
	t_WD	i;
	t_WD	j;

	i = 0;
	j = 0;
	while (i < 16)
	{
		md5->m[i] = (md5->data[j]) + (md5->data[j + 1] << 8) + \
					(md5->data[j + 2] << 16) + (md5->data[j + 3] << 24);
		++i;
		j += 4;
	}
	a = md5->state[0];
	b = md5->state[1];
	c = md5->state[2];
	d = md5->state[3];

	a += F(b, c, d) + m[0] + 0xd76aa478;
	a = b + ROTLEFT(a, 7);
	md5->a = a;
}

int		main(void)
{
	char			*str = "abc";
	t_md5			md5;
	unsigned char	out[16];
	int				i;

	md5_buffer_init(&md5);
	check_text(&md5, str);
//	mf(md5.a, md5.b, md5.c, md5.d, md5.m[0], &md5);
	check_md5(&md5, str);
//	ft_printf("check_md5 (md5.data) : %64x\n", md5.data);
//	transform(&md5);
	i = 0;
//	printf("md5.state[0] : %u\n", md5.state[0]);
//	printf("md5.state[1] : %u\n", md5.state[1]);
//	printf("md5.state[2] : %u\n", md5.state[2]);
//	printf("md5.state[3] : %u\n", md5.state[3]);
	while (i < 4)
	{
		out[i] = md5.state[0] >> (i * 8) & 0x000000ff;
		out[i + 4] = md5.state[1] >> (i * 8) & 0x000000ff;
		out[i + 8] = md5.state[2] >> (i * 8) & 0x000000ff;
		out[i + 16] = md5.state[3] >> (i * 8) & 0x000000ff;
		++i;
	}
	i = 0;
	while (i < 4)
		ft_printf("%x", out[i++]);
	ft_printf("\n");
	ft_printf("%.8x%.8x%.8x%.8x", out[0], out[4], out[8], out[12]);
//	ft_printf("%.8x%.8x%.8x%.8x", md5.state[0], md5.state[1], md5.state[2], md5.state[3]);
}
