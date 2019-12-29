/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 22:59:46 by sko               #+#    #+#             */
/*   Updated: 2019/12/20 22:59:49 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void					no_rotation(t_ssl *ssl, char **av)
{
	if (!(ssl->flag.q == 1))
	{
		if (ft_strcmp(ssl->type, "sha224") == 0)
			ft_putstr("SHA224 (\"");
		else if (ft_strcmp(ssl->type, "sha256") == 0)
			ft_putstr("SHA256 (\"");
		else
			ft_putstr("MD5 (\"");
		ft_putstr(av[ssl->pars]);
		ft_putstr("\")= ");
	}
	if (ft_strcmp(ssl->type, "sha224") == 0)
		do_sha256(av[ssl->pars], ssl);
	else if (ft_strcmp(ssl->type, "sha256") == 0)
		do_sha256(av[ssl->pars], ssl);
	else
		do_md5(av[ssl->pars], ssl);
	ft_putstr("\n");
}

void					no_rotation_512(t_s5 *ssl, char **av)
{
	if (!(ssl->flag.q == 1))
	{
		if (ft_strcmp(ssl->type, "sha512") == 0)
			ft_putstr("SHA512 (\"");
		ft_putstr(av[ssl->pars]);
		ft_putstr("\")= ");
	}
	if (ft_strcmp(ssl->type, "sha512") == 0)
		do_sha512(av[ssl->pars], ssl);
	ft_putstr("\n");
}

void					rotate_s(t_ssl *ssl, char **av)
{
	if (ft_strcmp(ssl->type, "sha224") == 0)
		do_sha256(av[ssl->pars], ssl);
	else if (ft_strcmp(ssl->type, "sha256") == 0)
		do_sha256(av[ssl->pars], ssl);
	else
		do_md5(av[ssl->pars], ssl);
	if (!(ssl->flag.q == 1))
	{
		ft_putstr(" ");
		ft_putendl(av[ssl->pars]);
	}
	else
		ft_putstr("\n");
}

void					rotate_s_512(t_s5 *ssl, char **av)
{
	if (ft_strcmp(ssl->type, "sha512") == 0)
		do_sha512(av[ssl->pars], ssl);
	if (!(ssl->flag.q == 1))
	{
		ft_putstr(" ");
		ft_putendl(av[ssl->pars]);
	}
	else
		ft_putstr("\n");
}

static void				file_no_rotat(t_ssl *ssl, char **av)
{
	if (!(ssl->flag.q == 1))
	{
		if (ft_strcmp(ssl->type, "sha224") == 0)
			ft_putstr("SHA224(");
		else if (ft_strcmp(ssl->type, "sha256") == 0)
			ft_putstr("SHA256(");
		else
			ft_putstr("MD5(");
		ft_putstr(av[ssl->pars]);
		ft_putstr(")= ");
	}
	if (ft_strcmp(ssl->type, "sha224") == 0)
		do_sha256(ssl->stdin, ssl);
	else if (ft_strcmp(ssl->type, "sha256") == 0)
		do_sha256(ssl->stdin, ssl);
	else
		do_md5(ssl->stdin, ssl);
	ft_putstr("\n");
}

static void				file_no_rotat_512(t_s5 *ssl, char **av)
{
	if (!(ssl->flag.q == 1))
	{
		if (ft_strcmp(ssl->type, "sha512") == 0)
			ft_putstr("SHA512(");
		ft_putstr(av[ssl->pars]);
		ft_putstr(")= ");
	}
	if (ft_strcmp(ssl->type, "sha512") == 0)
		do_sha512(ssl->stdin, ssl);
	ft_putstr("\n");
}

void					file_rotat(t_ssl *ssl, char **av)
{
	if (bad_file(ssl, av) == -1)
		return ;
	gnl_ignore_nl(ssl->fd, &ssl->stdin);
	if (!(ssl->flag.r == 1))
		file_no_rotat(ssl, av);
	else
	{
		if (ft_strcmp(ssl->type, "sha224") == 0)
			do_sha256(ssl->stdin, ssl);
		else if (ft_strcmp(ssl->type, "sha256") == 0)
			do_sha256(ssl->stdin, ssl);
		else
			do_md5(ssl->stdin, ssl);
		if (!(ssl->flag.q == 1))
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

void					file_rotat_512(t_s5 *ssl, char **av)
{
	if (bad_file_512(ssl, av) == -1)
	if (bad_file_512(ssl, av) == -1)
		return ;
	gnl_ignore_nl(ssl->fd, &ssl->stdin);
	if (!(ssl->flag.r == 1))
		file_no_rotat_512(ssl, av);
	else
	{
		if (ft_strcmp(ssl->type, "sha512") == 0)
			do_sha512(ssl->stdin, ssl);
		if (!(ssl->flag.q == 1))
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