/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/21 16:51:57 by sko               #+#    #+#             */
/*   Updated: 2019/12/21 16:51:58 by sko              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_wd				revers_WD(t_wd n)
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

char				*ft_itoa_base_extra_512(uint64_t n, int base)
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