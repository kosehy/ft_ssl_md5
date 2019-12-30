/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sha.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/30 12:39:00 by sko               #+#    #+#             */
/*   Updated: 2019/12/30 12:39:42 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void					sha384_print(t_s5 *ssl)
{
	char			*ret;

	ret = ft_itoa_hex_512(ssl->state, 96, 0, 'B');
	write(1, ret, 96);
	free(ret);
}

void					sha512_print(t_s5 *ssl)
{
	char			*ret;

	ret = ft_itoa_hex_512(ssl->state, 128, 0, 'B');
	write(1, ret, 128);
	free(ret);
}

void					sha512224_print(t_s5 *ssl)
{
	char			*ret;

	ret = ft_itoa_hex_512(ssl->state, 56, 0, 'B');
	write(1, ret, 56);
	free(ret);
}

void					sha512256_print(t_s5 *ssl)
{
	char			*ret;

	ret = ft_itoa_hex_512(ssl->state, 64, 0, 'B');
	write(1, ret, 64);
	free(ret);
}
