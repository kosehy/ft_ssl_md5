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
** Define four auxiliary functions that each take as input three 42-bit t_wds
** and produce as output one 42-bit t_wd.
*/

typedef unsigned int	t_wd;

typedef struct			s_flag
{
	int 				p;
	int 				q;
	int 				r;
	int 				s;
}						t_flag;

typedef struct			s_ssl
{
	int					datalen;
	unsigned int		state[8];
	t_wd				a;
	t_wd				b;
	t_wd				c;
	t_wd				d;
	t_wd				e;
	t_wd				f;
	t_wd				g;
	t_wd				h;
	t_wd 				s_data[6];
	t_wd 				*t;
	t_wd 				*byte_32;
	t_flag 				flag;
	int 				s;
	int 				n_file;
	int 				pars;
	int 				fd;
	int 				str;
	char 				*stdin;
	char				*byte;
	char				*type;
	int 				blocks;
	size_t 				len;
	t_wd 				w[64];
}						t_ssl;

typedef struct			s_s5
{
	int					datalen;
	uint64_t			state[8];
	uint64_t			a;
	uint64_t			b;
	uint64_t			c;
	uint64_t			d;
	uint64_t			e;
	uint64_t			f;
	uint64_t			g;
	uint64_t			h;
	uint64_t 			s_data[6];
	uint64_t 			*t;
	uint64_t 			*byte_32;
	t_flag 				flag;
	int 				s;
	int 				n_file;
	int 				pars;
	int 				fd;
	int 				str;
	char 				*stdin;
	char				*byte;
	char				*type;
	int 				blocks;
	size_t 				len;
	uint64_t 			w[64];
}						t_s5;

/*
** ft_auxiliary.c
*/

void					aux_f(t_ssl *ssl, t_wd i);
void					aux_g(t_ssl *ssl, t_wd i);
void					aux_h(t_ssl *ssl, t_wd i);
void					aux_i(t_ssl *ssl, t_wd i);

/*
** transform.c
*/

int						md5(t_ssl *md5, unsigned char *str, int len);

/*
** print.c
*/

int						bad_file(t_ssl *ssl, char **av);
int						bad_file_512(t_s5 *ssl, char **av);
void					gnl_ignore_nl(int fd, char **ptr);
int						print_s(t_ssl *ssl, int ac, char **av);
int						print_s_512(t_s5 *ssl, int ac, char **av);


/*
** md5.c
*/

void					do_sha512(char *str, t_s5 *ssl);
void					do_sha256(char *str, t_ssl *ssl);
void	 				do_md5(char *str, t_ssl *ssl);

/*
** rotate.c
*/

void					file_rotat(t_ssl *ssl, char **av);
void					no_rotation(t_ssl *ssl, char **av);
void					rotate_s(t_ssl *ssl, char **av);
void					sha256_var_assign(t_ssl *ssl, char order);

/*
** util.c
*/

t_wd					revers_WD(t_wd n);
char					*ft_itoa_base_extra(uint32_t n, int base);
char 					*add_zero(char *str);

/*
** util2.c
*/

char					*ft_itoa_hex_512(uint64_t state[], int size, int i, char end);
uint64_t				rot_right_64(uint64_t x, uint64_t n);
t_wd 					rot_left(t_wd x, t_wd n);
t_wd 					rot_right(t_wd x, t_wd n);

/*
** util_sha512.c
*/

void					file_rotat_512(t_s5 *ssl, char **av);
void					no_rotation_512(t_s5 *ssl, char **av);
void					rotate_s_512(t_s5 *ssl, char **av);
void					sha384_print(t_s5 *ctx);
void					sha512_print(t_s5 *ctx);
void					sha512224_print(t_s5 *ctx);
void					sha512256_print(t_s5 *ctx);

/*
** sha256.c
*/

int 					sha256(t_ssl *ssl, char *str, int len);

/*
** sha512.c
*/

int 					sha512(t_s5 *ssl, char *str, int len);

/*
** init_sha.c
*/

void					init_sha224(t_ssl *ssl);
void					init_sha256(t_ssl *ssl);
void					init_sha384(t_s5 *ssl);
void					init_sha512(t_s5 *ssl);
void					init_sha512224(t_s5 *ssl);
void					init_sha512256(t_s5 *ssl);

/*
** auxiliary_sha256.c
*/

void					swap_words(t_ssl *ssl, int i);

/*
** auxiliary_sha512.c
*/

void					swap_words_512(t_s5 *ssl, int i);

#endif