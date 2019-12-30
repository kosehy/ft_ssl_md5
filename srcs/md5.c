/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 11:50:58 by sko               #+#    #+#             */
/*   Updated: 2019/12/20 11:51:00 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void				print_tmp_with_zero(t_wd state, int n)
{
	char *tmp;

	tmp = ft_itoa_base_extra(state, n);
	add_zero(tmp);
	ft_putstr(tmp);
	free(tmp);
}

void				do_md5(char *str, t_ssl *ssl)
{
	if (md5(ssl, (uint8_t *)str, ft_strlen(str)) == -1)
		return ;
	print_tmp_with_zero(revers_wd(ssl->state[0]), 16);
	print_tmp_with_zero(revers_wd(ssl->state[1]), 16);
	print_tmp_with_zero(revers_wd(ssl->state[2]), 16);
	print_tmp_with_zero(revers_wd(ssl->state[3]), 16);
}

void				do_sha256(char *str, t_ssl *ssl)
{
	if (sha256(ssl, str, ft_strlen(str)) == -1)
		return ;
	if (ft_strcmp(ssl->type, "sha224") == 0)
	{
		print_tmp_with_zero(ssl->state[0], 16);
		print_tmp_with_zero(ssl->state[1], 16);
		print_tmp_with_zero(ssl->state[2], 16);
		print_tmp_with_zero(ssl->state[3], 16);
		print_tmp_with_zero(ssl->state[4], 16);
		print_tmp_with_zero(ssl->state[5], 16);
		print_tmp_with_zero(ssl->state[6], 16);
	}
	else if (ft_strcmp(ssl->type, "sha256") == 0)
	{
		print_tmp_with_zero(ssl->state[0], 16);
		print_tmp_with_zero(ssl->state[1], 16);
		print_tmp_with_zero(ssl->state[2], 16);
		print_tmp_with_zero(ssl->state[3], 16);
		print_tmp_with_zero(ssl->state[4], 16);
		print_tmp_with_zero(ssl->state[5], 16);
		print_tmp_with_zero(ssl->state[6], 16);
		print_tmp_with_zero(ssl->state[7], 16);
	}
}

void				do_sha512(char *str, t_s5 *ssl)
{
	if (sha512(ssl, str, ft_strlen(str)) == -1)
		return ;
	if (ft_strcmp(ssl->type, "sha384") == 0)
		sha384_print(ssl);
	else if (ft_strcmp(ssl->type, "sha512") == 0)
		sha512_print(ssl);
	else if (ft_strcmp(ssl->type, "sha512224") == 0)
		sha512224_print(ssl);
	else if (ft_strcmp(ssl->type, "sha512256") == 0)
		sha512256_print(ssl);
}
