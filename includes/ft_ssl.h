/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:59:10 by sko               #+#    #+#             */
/*   Updated: 2019/11/23 20:59:13 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# include "libft.h"

/*
** Define four auxiliary functions that each take as input three 42-bit t_WDs
** and produce as output one 42-bit t_WD.
*/

#define ROTLEFT(a,b) ((a << b) | (a >> (32-b)))

#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x ^ y ^ z)
#define I(x,y,z) (y ^ (x | ~z))

typedef unsigned int	t_WD;

typedef struct			s_ssl
{
	unsigned char		data[64];
	unsigned int		datalen;
	unsigned long long	bitlen;
	unsigned int		state[4];
	t_WD				m[16];
	t_WD				a;
	t_WD				b;
	t_WD				c;
	t_WD				d;
	t_WD				f;
	t_WD				g;
	t_WD 				flag[5];
	int 				n_file;
	char 				*stdin;
}						t_ssl;

/*
** ft_auxiliary.c
*/

t_WD					ff(t_WD a, t_WD b, t_WD c, t_WD d, t_WD *m, int s,\
							t_WD t);
t_WD					gg(t_WD a, t_WD b, t_WD c, t_WD d, t_WD *m, int s, \
							t_WD t);
t_WD					hh(t_WD a, t_WD b, t_WD c, t_WD d, t_WD *m, int s, \
							t_WD t);
t_WD					ii(t_WD a, t_WD b, t_WD c, t_WD d, t_WD *m, int s, \
							t_WD t);

/*
** transform.c
*/

void					transform(t_ssl *md5);
void					simple_transform(t_ssl *md5);

#endif