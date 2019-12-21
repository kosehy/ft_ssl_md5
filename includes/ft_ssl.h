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

typedef unsigned int	t_WD;

typedef struct			s_ssl
{
	unsigned char		data[64];
	int					datalen;
	unsigned long long	bitlen;
	unsigned int		state[4];
	t_WD				m[16];
	t_WD				a;
	t_WD				b;
	t_WD				c;
	t_WD				d;
	t_WD				f;
	t_WD				g;
	t_WD 				*t;
	int 				flag[5];
	int					p;
	int					q;
	int					r;
	int 				s;
	int 				n_file;
	int 				pars;
	int 				fd;
	int 				str;
	char 				*stdin;
	char				*byte;
}						t_ssl;

/*
** ft_auxiliary.c
*/

t_WD 					rot_left(t_WD x, t_WD n);
void					aux_f(t_ssl *ssl, t_WD i);
void					aux_g(t_ssl *ssl, t_WD i);
void					aux_h(t_ssl *ssl, t_WD i);
void					aux_i(t_ssl *ssl, t_WD i);

/*
** transform.c
*/

int						md5(t_ssl *md5, unsigned char *str, int len);

/*
** print.c
*/

void					gnl_ignore_nl(int fd, char **ptr);
int 					print_s(t_ssl *ssl, int ac, char **av);
void	 				file_rotat(t_ssl *ssl, char **av);

/*
** md5.c
*/

void					md5_buffer_init(t_ssl *ssl);
void	 				do_md5(char *str, t_ssl *ssl);
void					decision_maker(t_ssl *ssl, int ac, char **av);

#endif