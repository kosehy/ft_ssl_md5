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

static void 		check_flag(t_ssl *ssl, int ac, char **av)
{
	int i = 2;
	ssl->s = 0;

	while (i < ac)
	{
		if (ft_strcmp("-p", av[i]) == 0)
			ssl->flag.p = 1;
		else if (ft_strcmp("-q", av[i]) == 0)
			ssl->flag.q = 1;
		else if (ft_strcmp("-r", av[i]) == 0)
			ssl->flag.r = 1;
		else if (ft_strcmp("-s", av[i]) == 0)
		{
			i++;
			ssl->flag.s++;
		}
		else
			break ;
		i++;
	}
	ssl->n_file = i - ac;
}

void				decision_maker(t_ssl *ssl, int ac, char **av)
{
	check_flag(ssl, ac, av);
	if ((ssl->flag.p == 1) || (!ssl->n_file && !ssl->s))
	{
		gnl_ignore_nl(0, &ssl->stdin);
		if (ssl->flag.p == 1)
			ft_putstr(ssl->stdin);
		if (ft_strcmp(av[1], "sha256") == 0)
			do_sha256(ssl->stdin, ssl);
		else
			do_md5(ssl->stdin, ssl);
		ft_putstr("\n");
		free(ssl->stdin);
	}
	ssl->pars = 2;
	while (ssl->pars < ac)
		if (print_s(ssl, ac, av) == -1)
			break ;
	while (ssl->pars < ac)
		file_rotat(ssl, av);
}

int					main(int ac, char **av)
{
	t_ssl			ssl;

	if (ac == 1)
	{
		ft_putstr("wrong!\n");
		ft_putstr("use follow command\n");
		ft_putstr("ft ssl command [flag] [argument]\n");
		exit(-1);
	}
	if (ft_strcmp(av[1], "md5") == 0 || ft_strcmp(av[1], "sha256") == 0)
		decision_maker(&ssl, ac, av);
	else
	{
		ft_putstr("ft_ssl : ");
		ft_putstr(av[1]);
		ft_putstr("is an invalid\n");
		exit(-1);
	}
	return (0);
}
