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
			break;
		tmp = str;
		str = ft_strjoin(str, c);
		free(tmp);
	}
	ptr[0] = str;
}


void					no_rotation(t_ssl *ssl, char **av)
{
	if (!ssl->flag[2])
	{
		if (ft_strcmp(av[1], "sha256") == 0)
			ft_printf("SHA256 (\"");
		else
			ft_printf("MD5 (\"");
		ft_putstr(av[ssl->pars]);
		ft_printf("\")= ");
	}
	if (ft_strcmp(av[1], "sha256") == 0)
		do_md5(av[ssl->pars], ssl);
	else
		do_md5(av[ssl->pars], ssl);
	ft_printf("\n");
}

void 					rotate_s(t_ssl *ssl, char **av)
{
	if (ft_strcmp(av[1], "sha256") == 0)
		do_md5(av[ssl->pars], ssl);
	else
	{
		ft_printf("MD5 (\"%s\")= ", av[ssl->pars]);
		do_md5(av[ssl->pars], ssl);
	}
	if (!ssl->flag[2])
		ft_printf(" \"%s\"\n", av[ssl->pars]);
	else
		ft_printf("\n");
}

int 					print_s(t_ssl *ssl, int ac, char **av)
{
	if (ft_strcmp("-p", av[ssl->flag[0]]) == 0)
		ssl->flag[1] = 1;
	else if (ft_strcmp("-q", av[ssl->flag[0]]) == 0)
		ssl->flag[2] = 1;
	else if (ft_strcmp("-r", av[ssl->flag[0]]) == 0)
		ssl->flag[3] = 1;
	else if (ft_strcmp("-s", av[ssl->flag[0]]) == 0)
	{
		ssl->pars++;
		if (ssl->pars < ac)
		{
			if (!ssl->flag[3])
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

static void 			file_no_rotat(t_ssl *ssl, char **av)
{
	if (!ssl->flag[2])
	{
		if (ft_strcmp(av[1], "sha256") == 0)
			ft_printf("SHA256(");
		else
			ft_printf("MD5(");
		ft_printf("%s)= ", av[ssl->pars]);
	}
	if (ft_strcmp(av[1], "sha256") == 0)
		do_md5(ssl->stdin, ssl);
	else
		do_md5(ssl->stdin, ssl);
	ft_printf("\n");
}

int 					bad_file(t_ssl *ssl, char **av)
{
	if ((ssl->fd = open(av[ssl->pars], O_RDWR)) < 0)
	{
		if (ft_strcmp(av[1], "sha256") == 0)
			ft_printf("ft_ssl: sha256: ");
		if (ft_strcmp(av[1], "sha224") == 0)
			ft_printf("ft_ssl: sha224: ");
		else
			ft_printf("ft_ssl: md5: ");
		ft_printf("%s", av[ssl->pars]);
		ft_printf(": No such file or directory\n");
		ssl->pars++;
		return (-1);
	}
	return (0);
}

void			 		file_rotat(t_ssl *ssl, char **av)
{
	if (bad_file(ssl, av) == -1)
		return ;
	gnl_ignore_nl(ssl->fd, &ssl->stdin);
	if (!ssl->flag[3])
		file_no_rotat(ssl, av);
	else
	{
		if (ft_strcmp(av[1], "sha256") == 0)
			do_md5(ssl->stdin, ssl);
		else
			do_md5(ssl->stdin, ssl);
		if (!ssl->flag[2])
			ft_printf(" %s\n", av[ssl->pars]);
		else
			ft_printf("\n");
	}
	free(ssl->stdin);
	close(ssl->fd);
	ssl->pars++;
}