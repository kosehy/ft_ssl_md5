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
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a,
	0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340,
	0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8,
	0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa,
	0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92,
	0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

void		ff_transform(t_md5 *md5)
{
	FF(md5->a, md5->b, md5->c, md5->d, md5->m[0],  7,  g_t[0]);
	FF(md5->d, md5->a, md5->b, md5->c, md5->m[1],  12, g_t[1]);
	FF(md5->c, md5->d, md5->a, md5->b, md5->m[2],  17, g_t[2]);
	FF(md5->b, md5->c, md5->d, md5->a, md5->m[3],  22, g_t[3]);
	FF(md5->a, md5->b, md5->c, md5->d, md5->m[4],  7,  g_t[4]);
	FF(md5->d, md5->a, md5->b, md5->c, md5->m[5],  12, g_t[5]);
	FF(md5->c, md5->d, md5->a, md5->b, md5->m[6],  17, g_t[6]);
	FF(md5->b, md5->c, md5->d, md5->a, md5->m[7],  22, g_t[7]);
	FF(md5->a, md5->b, md5->c, md5->d, md5->m[8],  7,  g_t[8]);
	FF(md5->d, md5->a, md5->b, md5->c, md5->m[9],  12, g_t[9]);
	FF(md5->c, md5->d, md5->a, md5->b, md5->m[10], 17, g_t[10]);
	FF(md5->b, md5->c, md5->d, md5->a, md5->m[11], 22, g_t[11]);
	FF(md5->a, md5->b, md5->c, md5->d, md5->m[12], 7,  g_t[12]);
	FF(md5->d, md5->a, md5->b, md5->c, md5->m[13], 12, g_t[13]);
	FF(md5->c, md5->d, md5->a, md5->b, md5->m[14], 17, g_t[14]);
	FF(md5->b, md5->c, md5->d, md5->a, md5->m[15], 22, g_t[15]);
}

void		gg_transform(t_md5 *md5)
{
	GG(md5->a, md5->b, md5->c, md5->d, md5->m[1],  5,  g_t[16]);
	GG(md5->d, md5->a, md5->b, md5->c, md5->m[6],  9, g_t[17]);
	GG(md5->c, md5->d, md5->a, md5->b, md5->m[11],  14, g_t[18]);
	GG(md5->b, md5->c, md5->d, md5->a, md5->m[0],  20, g_t[19]);
	GG(md5->a, md5->b, md5->c, md5->d, md5->m[5],  5,  g_t[20]);
	GG(md5->d, md5->a, md5->b, md5->c, md5->m[10],  9, g_t[21]);
	GG(md5->c, md5->d, md5->a, md5->b, md5->m[15],  14, g_t[22]);
	GG(md5->b, md5->c, md5->d, md5->a, md5->m[4],  20, g_t[23]);
	GG(md5->a, md5->b, md5->c, md5->d, md5->m[9],  5,  g_t[24]);
	GG(md5->d, md5->a, md5->b, md5->c, md5->m[14],  9, g_t[25]);
	GG(md5->c, md5->d, md5->a, md5->b, md5->m[3], 14, g_t[26]);
	GG(md5->b, md5->c, md5->d, md5->a, md5->m[8], 20, g_t[27]);
	GG(md5->a, md5->b, md5->c, md5->d, md5->m[13], 5,  g_t[28]);
	GG(md5->d, md5->a, md5->b, md5->c, md5->m[2], 9, g_t[29]);
	GG(md5->c, md5->d, md5->a, md5->b, md5->m[7], 14, g_t[30]);
	GG(md5->b, md5->c, md5->d, md5->a, md5->m[12], 20, g_t[31]);
}

void		hh_transform(t_md5 *md5)
{
	HH(md5->a, md5->b, md5->c, md5->d, md5->m[5],  4,  g_t[32]);
	HH(md5->d, md5->a, md5->b, md5->c, md5->m[8],  11, g_t[33]);
	HH(md5->c, md5->d, md5->a, md5->b, md5->m[11],  16, g_t[34]);
	HH(md5->b, md5->c, md5->d, md5->a, md5->m[14],  23, g_t[35]);
	HH(md5->a, md5->b, md5->c, md5->d, md5->m[1],  4,  g_t[36]);
	HH(md5->d, md5->a, md5->b, md5->c, md5->m[4],  11, g_t[37]);
	HH(md5->c, md5->d, md5->a, md5->b, md5->m[7],  16, g_t[38]);
	HH(md5->b, md5->c, md5->d, md5->a, md5->m[10],  23, g_t[39]);
	HH(md5->a, md5->b, md5->c, md5->d, md5->m[13],  4,  g_t[40]);
	HH(md5->d, md5->a, md5->b, md5->c, md5->m[0],  11, g_t[41]);
	HH(md5->c, md5->d, md5->a, md5->b, md5->m[3], 16, g_t[42]);
	HH(md5->b, md5->c, md5->d, md5->a, md5->m[6], 23, g_t[43]);
	HH(md5->a, md5->b, md5->c, md5->d, md5->m[9], 4,  g_t[44]);
	HH(md5->d, md5->a, md5->b, md5->c, md5->m[12], 11, g_t[45]);
	HH(md5->c, md5->d, md5->a, md5->b, md5->m[15], 16, g_t[46]);
	HH(md5->b, md5->c, md5->d, md5->a, md5->m[2], 23, g_t[47]);
}

void		ii_transform(t_md5 *md5)
{
	II(md5->a, md5->b, md5->c, md5->d, md5->m[0],  6,  g_t[48]);
	II(md5->d, md5->a, md5->b, md5->c, md5->m[7],  10, g_t[49]);
	II(md5->c, md5->d, md5->a, md5->b, md5->m[14],  15, g_t[50]);
	II(md5->b, md5->c, md5->d, md5->a, md5->m[5],  21, g_t[51]);
	II(md5->a, md5->b, md5->c, md5->d, md5->m[12],  6,  g_t[52]);
	II(md5->d, md5->a, md5->b, md5->c, md5->m[3],  10, g_t[53]);
	II(md5->c, md5->d, md5->a, md5->b, md5->m[10],  15, g_t[54]);
	II(md5->b, md5->c, md5->d, md5->a, md5->m[1],  21, g_t[55]);
	II(md5->a, md5->b, md5->c, md5->d, md5->m[8],  6,  g_t[56]);
	II(md5->d, md5->a, md5->b, md5->c, md5->m[15],  10, g_t[57]);
	II(md5->c, md5->d, md5->a, md5->b, md5->m[6], 15, g_t[58]);
	II(md5->b, md5->c, md5->d, md5->a, md5->m[13], 21, g_t[59]);
	II(md5->a, md5->b, md5->c, md5->d, md5->m[4], 6,  g_t[60]);
	II(md5->d, md5->a, md5->b, md5->c, md5->m[11], 10, g_t[61]);
	II(md5->c, md5->d, md5->a, md5->b, md5->m[2], 15, g_t[62]);
	II(md5->b, md5->c, md5->d, md5->a, md5->m[9], 21, g_t[63]);
}

void		transform(t_md5 *md5)
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
	md5->a = md5->state[0];
	md5->b = md5->state[1];
	md5->c = md5->state[2];
	md5->d = md5->state[3];
	ff_transform(md5);
	gg_transform(md5);
	hh_transform(md5);
	ii_transform(md5);
	md5->state[0]+= md5->a;
	md5->state[1]+= md5->b;
	md5->state[2]+= md5->c;
	md5->state[3]+= md5->d;
}
