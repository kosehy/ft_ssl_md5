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

void 				do_md5(char *str, t_ssl *ssl)
{
	char *tmp;

	if (md5(ssl, (uint8_t *)str, ft_strlen(str)) == -1)
		return ;
	tmp = ft_itoa_base_extra(revers_WD(ssl->state[0]), 16);
	add_zero(tmp);
	ft_putstr(tmp);
	free(tmp);
	tmp = ft_itoa_base_extra(revers_WD(ssl->state[1]), 16);
	add_zero(tmp);
	ft_putstr(tmp);
	free(tmp);
	tmp = ft_itoa_base_extra(revers_WD(ssl->state[2]), 16);
	add_zero(tmp);
	ft_putstr(tmp);
	free(tmp);
	tmp = ft_itoa_base_extra(revers_WD(ssl->state[3]), 16);
	add_zero(tmp);
	ft_putstr(tmp);
	free(tmp);
}

void				do_sha256(char *str, t_ssl *ssl)
{
	char *tmp;

	if (sha256(ssl, str, ft_strlen(str)) == -1)
		return ;
	tmp = ft_itoa_base_extra(ssl->state[0], 16);
	add_zero(tmp);
	ft_putstr(tmp);
	free(tmp);
	tmp = ft_itoa_base_extra(ssl->state[1], 16);
	add_zero(tmp);
	ft_putstr(tmp);
	free(tmp);
	tmp = ft_itoa_base_extra(ssl->state[2], 16);
	add_zero(tmp);
	ft_putstr(tmp);
	free(tmp);
	tmp = ft_itoa_base_extra(ssl->state[3], 16);
	add_zero(tmp);
	ft_putstr(tmp);
	free(tmp);
	tmp = ft_itoa_base_extra(ssl->state[4], 16);
	add_zero(tmp);
	ft_putstr(tmp);
	free(tmp);
	tmp = ft_itoa_base_extra(ssl->state[5], 16);
	add_zero(tmp);
	ft_putstr(tmp);
	free(tmp);
	tmp = ft_itoa_base_extra(ssl->state[6], 16);
	add_zero(tmp);
	ft_putstr(tmp);
	free(tmp);
	tmp = ft_itoa_base_extra(ssl->state[7], 16);
	add_zero(tmp);
	ft_putstr(tmp);
	free(tmp);
}