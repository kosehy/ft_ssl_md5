/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sko <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/29 23:24:12 by sko               #+#    #+#             */
/*   Updated: 2019/12/29 23:24:25 by sko              ###   ########.fr       */
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

u_int64_t		rot_right_64(u_int64_t x, u_int64_t n)
{
	u_int64_t	tmp;

	tmp = (x >> n) | (x << (64 - n));
	return (tmp);
}

t_wd 			rot_left(t_wd x, t_wd n)
{
	t_wd	tmp;

	tmp = (x << n) | (x >> (32 - n));
	return (tmp);
}

t_wd 			rot_right(t_wd x, t_wd n)
{
	t_wd	tmp;

	tmp = (x >> n) | (x << (32 - n));
	return (tmp);
}