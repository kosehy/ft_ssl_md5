/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/20 11:25:07 by sko               #+#    #+#             */
/*   Updated: 2019/12/20 11:25:09 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void					gnl_ignore_nl(int fd, char **ptr)
{
	char	c[2];
	char	*str;
	char	*tmp;
	int		check;

	c[1] = 0;
	check = 1;
	str = ft_strdup("");
	while (check > 0)
	{
		check = read(fd, c, 1);
		if (check == 0)
			break ;
		tmp = str;
		str = ft_strjoin(str, c);
		free(tmp);
	}
	ptr[0] = str;
}

int						print_s(t_ssl *ssl, int ac, char **av)
{
	if (ft_strcmp("-p", av[ssl->pars]) == 0)
		ssl->flag.p = 1;
	else if (ft_strcmp("-q", av[ssl->pars]) == 0)
		ssl->flag.q = 1;
	else if (ft_strcmp("-r", av[ssl->pars]) == 0)
		ssl->flag.r = 1;
	else if (ft_strcmp("-s", av[ssl->pars]) == 0)
	{
		ssl->pars++;
		if (ssl->pars < ac)
		{
			if (!(ssl->flag.r))
				no_rotation(ssl, av);
			else
				rotate_s(ssl, av);
		}
	}
	else
		return (-1);
	ssl->pars++;
	return (0);
}

int						print_s_512(t_s5 *ssl, int ac, char **av)
{
	if (ft_strcmp("-p", av[ssl->pars]) == 0)
		ssl->flag.p = 1;
	else if (ft_strcmp("-q", av[ssl->pars]) == 0)
		ssl->flag.q = 1;
	else if (ft_strcmp("-r", av[ssl->pars]) == 0)
		ssl->flag.r = 1;
	else if (ft_strcmp("-s", av[ssl->pars]) == 0)
	{
		ssl->pars++;
		if (ssl->pars < ac)
		{
			if (!(ssl->flag.r))
				no_rotation_512(ssl, av);
			else
				rotate_s_512(ssl, av);
		}
	}
	else
		return (-1);
	ssl->pars++;
	return (0);
}

int						bad_file(t_ssl *ssl, char **av)
{
	if ((ssl->fd = open(av[ssl->pars], O_RDWR)) < 0)
	{
		if (ft_strcmp(ssl->type, "sha224") == 0)
			ft_putstr("ft_ssl: sha224: ");
		else if (ft_strcmp(ssl->type, "sha256") == 0)
			ft_putstr("ft_ssl: sha256: ");
		else
			ft_putstr("ft_ssl: md5: ");
		ft_putstr(av[ssl->pars]);
		ft_putstr(": No such file or directory\n");
		ssl->pars++;
		return (-1);
	}
	return (0);
}

int						bad_file_512(t_s5 *ssl, char **av)
{
	if ((ssl->fd = open(av[ssl->pars], O_RDWR)) < 0)
	{
		if (ft_strcmp(ssl->type, "sha224") == 0)
			ft_putstr("ft_ssl: sha224: ");
		else if (ft_strcmp(ssl->type, "sha256") == 0)
			ft_putstr("ft_ssl: sha256: ");
		else
			ft_putstr("ft_ssl: md5: ");
		ft_putstr(av[ssl->pars]);
		ft_putstr(": No such file or directory\n");
		ssl->pars++;
		return (-1);
	}
	return (0);
}
