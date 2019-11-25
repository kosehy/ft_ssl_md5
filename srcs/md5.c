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

void	*ft_memcpy1(unsigned int *dst, unsigned int *src, size_t n)
{
	unsigned int		*ptr;
	unsigned int		*ptr2;
	int			i;

	if (dst == NULL && src == NULL)
		return (dst);
	ptr = dst;
	ptr2 = src;
	i = 0;
	while (n-- > 0)
	{
		ptr[i] = ptr2[i];
		++i;
	}
	return (dst);
}

unsigned int		element_table1(void)
{
	unsigned int		*t;

	t[0] = 0xd76aa478;
	t[1] = 0xe8c7b756;
	t[2] = 0x242070db;
	t[3] = 0xc1bdceee;
	t[4] = 0xf57c0faf;
	t[5] = 0x4787c62a;
	t[6] = 0xa8304613;
	t[7] = 0xfd469501;
	t[8] = 0x698098d8;
	t[9] = 0x8b44f7af;
	t[10] = 0xffff5bb1;
	t[11] = 0x895cd7be;
	t[12] = 0x6b901122;
	t[13] = 0xfd987193;
	t[14] = 0xa679438e;
	t[15] = 0x49b40821;
	return (t);
}

unsigned int		element_table(void)
{
	unsigned int		table[16];

	ft_memcpy1(table, element_table1(), 16);
	return (table);
}

void			md_buffer_init(uint8_t *md)
{
	md[0] = 0x01;
	md[1] = 0x23;
	md[2] = 0x45;
	md[3] = 0x67;
	md[4] = 0x89;
	md[5] = 0xab;
	md[6] = 0xcd;
	md[7] = 0xef;
	md[8] = 0xfe;
	md[9] = 0xdc;
	md[10] = 0xba;
	md[11] = 0x98;
	md[12] = 0x76;
	md[13] = 0x54;
	md[14] = 0x32;
	md[15] = 0x10;
}

void			md5_buffer_init(t_md5 *md5)
{
	md5->datalen = 0;
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
	while (*str != '\0')
	{
		++md5->datalen;
		++str;
	}
}

void			check_md5(t_md5 *md5, char *str)
{
	int i = 0;
	while (i < md5->datalen) {
		md5->data[i] = str[i];
		++i;
	}
	md5->data[i++] = 0x80;
	while (i < 56) {
		md5->data[i] = 0x00;
		++i;
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
}

void			round(t_md5 *md5)
{
	size_t			i;
	size_t			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 16)
		{
			md5->message[j] = (md5->data[i * 16 + j] << 24);
			md5->message[j] += (md5->data[i * 16 + j] << 16);
			md5->message[j] += (md5->data[i * 16 + j] << 8);
			md5->message[j] += (md5->data[i * 16 + j]);
			++j;
		}
		++i;
	}
}

int		main(void)
{
	char	*str = "abc";
	t_md5	*md5;


	md5_buffer_init(md5);
	check_text(md5, str);
	check_md5(md5, str);
	round(md5);
	printf("%d\n", md5->message[0]);
	printf("%d\n", md5->message[1]);
	printf("%d\n", md5->message[2]);
	printf("%d\n", md5->message[3]);
}
