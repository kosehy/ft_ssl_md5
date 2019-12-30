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

char			*ft_itoa_hex_512(uint64_t state[], int size, int i, char end)
{
	char		*ret;
	int			j;
	uint64_t	r;
	uint64_t	temp;
	char	*cmp;

	cmp = "0123456789abcdef";
	ret = ft_strnew(size);
	r = 0x1000000000000000;
	while (i < size)
	{
		temp = (end == 'L' ? 0 : state[i / 16]);
		j = 0;
		while (j < 16)
		{
			ret[i] = cmp[temp / (r >> (4 * j))];
			temp = temp % (r >> (4 * j));
			j++;
			i++;
		}
	}
	return (ret);
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

void					sha512_print(t_s5 *ctx)
{
	char			*ret;

	ret = ft_itoa_hex_512(ctx->state, 128, 0, 'B');
	write(1, ret, 128);
	free(ret);
}


