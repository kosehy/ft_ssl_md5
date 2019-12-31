/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_sha512.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 22:35:25 by sko               #+#    #+#             */
/*   Updated: 2019/12/29 22:35:35 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void					no_rotation_512(t_s5 *ssl, char **av)
{
	if (!(ssl->flag.q))
	{
		if (ft_strcmp(ssl->type, "sha384") == 0)
			ft_putstr("SHA384 (\"");
		else if (ft_strcmp(ssl->type, "sha512") == 0)
			ft_putstr("SHA512 (\"");
		else if (ft_strcmp(ssl->type, "sha512224") == 0)
			ft_putstr("SHA512224 (\"");
		else if (ft_strcmp(ssl->type, "sha512256") == 0)
			ft_putstr("SHA512256 (\"");
		ft_putstr(av[ssl->pars]);
		ft_putstr("\")= ");
	}
	if (ft_strcmp(ssl->type, "sha384") == 0 || \
		ft_strcmp(ssl->type, "sha512") == 0 || \
		ft_strcmp(ssl->type, "sha512224") == 0 || \
		ft_strcmp(ssl->type, "sha512256") == 0)
		do_sha512(av[ssl->pars], ssl);
	ft_putstr("\n");
}

void					rotate_s_512(t_s5 *ssl, char **av)
{
	if (ft_strcmp(ssl->type, "sha384") == 0 || \
		ft_strcmp(ssl->type, "sha512") == 0 || \
		ft_strcmp(ssl->type, "sha512224") == 0 || \
		ft_strcmp(ssl->type, "sha512256") == 0)
		do_sha512(av[ssl->pars], ssl);
	if (!(ssl->flag.q))
	{
		ft_putstr(" ");
		ft_putendl(av[ssl->pars]);
	}
	else
		ft_putstr("\n");
}

static void				file_no_rotat_512(t_s5 *ssl, char **av)
{
	if (!(ssl->flag.q))
	{
		if (ft_strcmp(ssl->type, "sha384") == 0)
			ft_putstr("SHA384 (\"");
		else if (ft_strcmp(ssl->type, "sha512") == 0)
			ft_putstr("SHA512 (\"");
		else if (ft_strcmp(ssl->type, "sha512224") == 0)
			ft_putstr("SHA512224 (\"");
		else if (ft_strcmp(ssl->type, "sha512256") == 0)
			ft_putstr("SHA512256 (\"");
		ft_putstr(av[ssl->pars]);
		ft_putstr(")= ");
	}
	if (ft_strcmp(ssl->type, "sha384") == 0 || \
		ft_strcmp(ssl->type, "sha512") == 0 || \
		ft_strcmp(ssl->type, "sha512224") == 0 || \
		ft_strcmp(ssl->type, "sha512256") == 0)
		do_sha512(ssl->stdin, ssl);
	ft_putstr("\n");
}

void					file_rotat_512(t_s5 *ssl, char **av)
{
	if (bad_file_512(ssl, av) == -1)
		if (bad_file_512(ssl, av) == -1)
			return ;
	gnl_ignore_nl(ssl->fd, &ssl->stdin);
	if (!(ssl->flag.r))
		file_no_rotat_512(ssl, av);
	else
	{
		if (ft_strcmp(ssl->type, "sha384") == 0 || \
			ft_strcmp(ssl->type, "sha512") == 0 || \
			ft_strcmp(ssl->type, "sha512224") == 0 || \
			ft_strcmp(ssl->type, "sha512256") == 0)
			do_sha512(ssl->stdin, ssl);
		if (!(ssl->flag.q))
		{
			ft_putstr(" ");
			ft_putstr(av[ssl->pars]);
		}
		else
			ft_putstr("\n");
	}
	free(ssl->stdin);
	close(ssl->fd);
	ssl->pars++;
}
