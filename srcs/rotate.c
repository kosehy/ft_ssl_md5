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

void					sha256_var_assign(t_ssl *ssl, char order)
{
	if (order == '<')
	{
		ssl->a = ssl->state[0];
		ssl->b = ssl->state[1];
		ssl->c = ssl->state[2];
		ssl->d = ssl->state[3];
		ssl->e = ssl->state[4];
		ssl->f = ssl->state[5];
		ssl->g = ssl->state[6];
		ssl->h = ssl->state[7];
	}
	else if (order == '>')
	{
		ssl->state[0] += ssl->a;
		ssl->state[1] += ssl->b;
		ssl->state[2] += ssl->c;
		ssl->state[3] += ssl->d;
		ssl->state[4] += ssl->e;
		ssl->state[5] += ssl->f;
		ssl->state[6] += ssl->g;
		ssl->state[7] += ssl->h;
	}
}

void					no_rotation(t_ssl *ssl, char **av)
{
	if (!(ssl->flag.q))
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

void					rotate_s(t_ssl *ssl, char **av)
{
	if (ft_strcmp(ssl->type, "sha224") == 0)
		do_sha256(av[ssl->pars], ssl);
	else if (ft_strcmp(ssl->type, "sha256") == 0)
		do_sha256(av[ssl->pars], ssl);
	else
		do_md5(av[ssl->pars], ssl);
	if (!(ssl->flag.q))
	{
		ft_putstr(" ");
		ft_putendl(av[ssl->pars]);
	}
	else
		ft_putstr("\n");
}

static void				file_no_rotat(t_ssl *ssl, char **av)
{
	if (!(ssl->flag.q))
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

void					file_rotat(t_ssl *ssl, char **av)
{
	if (bad_file(ssl, av) == -1)
		return ;
	gnl_ignore_nl(ssl->fd, &ssl->stdin);
	if (!(ssl->flag.r))
		file_no_rotat(ssl, av);
	else
	{
		if (ft_strcmp(ssl->type, "sha224") == 0)
			do_sha256(ssl->stdin, ssl);
		else if (ft_strcmp(ssl->type, "sha256") == 0)
			do_sha256(ssl->stdin, ssl);
		else
			do_md5(ssl->stdin, ssl);
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
