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

void			md5_buffer_init(t_ssl *ssl)
{
	ssl->state[0] = 0x67452301;
	ssl->state[1] = 0xefcdab89;
	ssl->state[2] = 0x98badcfe;
	ssl->state[3] = 0x10325476;
}
t_WD	revers_WD(t_WD n)
{
	return ((n >> 24) | ((n & 0xff0000) >> 8) |
			((n & 0xff00) << 8) | (n << 24));
}

static int			ft_get_len(uint32_t n, int base)
{
	int i;

	i = 0;
	while (n != 0)
	{
		n = n / base;
		i++;
	}
	return (i);
}

static char			*free_str(char *str)
{
	char *tmp;

	tmp = str;
	str = ft_strsub(str, 1, ft_strlen(str) - 1);
	free(tmp);
	return (str);
}

char				*ft_itoa_base_extra(uint32_t n, int base)
{
	int		len;
	char	*str;
	char	*cmp;

	cmp = "0123456789abcdef";
	len = ft_get_len(n, base);
	if (n == 0)
		return (ft_strdup("0"));
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	str[len + 1] = 0;
	while (len + 1)
	{
		str[len] = cmp[n % base];
		n = n / base;
		len--;
	}
	if (str[0] == '0')
		str = free_str(str);
	return (str);
}

static void 		check_flag(t_ssl *ssl, int ac, char **av)
{
	int i = 2;
	ssl->p = 0;
	ssl->q = 0;
	ssl->r = 0;
	ssl->s = 0;

	while (i < ac)
	{
		if (ft_strcmp("-p", av[i]) == 0)
			ssl->p = 1;
		else if (ft_strcmp("-q", av[i]) == 0)
			ssl->q = 1;
		else if (ft_strcmp("-r", av[i]) == 0)
			ssl->r = 1;
		else if (ft_strcmp("-s", av[i]) == 0)
		{
			i++;
			ssl->s++;
		}
		else
			break ;
		i++;
	}
	ssl->n_file = i - ac;
}

char 				*add_zero(char *str)
{
	int	i;

	i = ft_strlen(str);
	while (i < 8)
	{
		ft_putstr("0");
		++i;
	}
	return (str);
}

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

void				decision_maker(t_ssl *ssl, int ac, char **av)
{
	check_flag(ssl, ac, av);
	if (ssl->p || (!ssl->n_file && !ssl->s))
	{
		gnl_ignore_nl(0, &ssl->stdin);
		if (ssl->p)
			ft_printf("%s", ssl->stdin);
		if (ft_strcmp(av[1], "sha256") == 0)
			do_md5(ssl->stdin, ssl);
		else
			do_md5(ssl->stdin, ssl);
		ft_printf("\n");
		free(ssl->stdin);
	}
	ssl->pars = 2;
	while (ssl->pars < ac)
		if (print_s(ssl, ac, av) == -1)
			break ;
	while (ssl->pars < ac)
		file_rotat(ssl, av);
}