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
	ssl->datalen = 0;
	ssl->bitlen = 0;
	ssl->state[0] = 0x67452301;
	ssl->state[1] = 0xefcdab89;
	ssl->state[2] = 0x98badcfe;
	ssl->state[3] = 0x10325476;
}

void			check_ssl(t_ssl *ssl, char *str)
{
	t_WD i;

	i = 0;
	while (i < ft_strlen(str))
	{
		ssl->data[ssl->datalen] = str[i];
		ssl->datalen++;
		if (ssl->datalen == 64)
		{
			simple_transform(ssl);
			ssl->bitlen += 512;
			ssl->datalen = 0;
		}
		++i;
	}
	i = ssl->datalen;
	if (ssl->datalen < 56)
	{
		ssl->data[i++] = 0x80;
		while (i < 56)
		{
			ssl->data[i] = 0x00;
			++i;
		}
	}
	else if (ssl->datalen >= 56)
	{
		ssl->data[i] = 0x80;
		while (i < 64)
		{
			ssl->data[i] = 0x00;
			++i;
		}
		simple_transform(ssl);
		ft_memset(ssl->data, 0, 56);
	}
	ssl->bitlen += ssl->datalen * 8;
	ssl->data[56] = ssl->bitlen;
	ssl->data[57] = ssl->bitlen >> 8;
	ssl->data[58] = ssl->bitlen >> 16;
	ssl->data[59] = ssl->bitlen >> 24;
	ssl->data[60] = ssl->bitlen >> 32;
	ssl->data[61] = ssl->bitlen >> 40;
	ssl->data[62] = ssl->bitlen >> 48;
	ssl->data[63] = ssl->bitlen >> 56;
	simple_transform(ssl);
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
	int i = 1;

	ssl->flag[0] = 2;
	while (i < 5)
		ssl->flag[i++] = 0;
	while (ssl->flag[0] < ac)
	{
		if (ft_strcmp("-p", av[ssl->flag[0]]) == 0)
			ssl->flag[1] = 1;
		else if (ft_strcmp("-q", av[ssl->flag[0]]) == 0)
			ssl->flag[2] = 1;
		else if (ft_strcmp("-r", av[ssl->flag[0]]) == 0)
			ssl->flag[3] = 1;
		else if (ft_strcmp("-s", av[ssl->flag[0]]) == 0)
		{
			ssl->flag[0]++;
			ssl->flag[4]++;
		}
		else
			break ;
		ssl->flag[0]++;
	}
	ssl->n_file = ssl->flag[0] - ac;
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

	md5_buffer_init(ssl);
	check_ssl(ssl, str);
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
	if (ssl->flag[1] || (!ssl->n_file && !ssl->flag[2]))
	{
		gnl_ignore_nl(0, &ssl->stdin);
		if (ssl->flag[1])
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