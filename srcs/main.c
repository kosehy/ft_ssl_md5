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

int					main(int ac, char **av)
{
	t_ssl			ssl;
	if (ac == 1)
	{
		ft_printf("wrong!\n");
		ft_printf("use follow command\n");
		ft_printf("ft ssl command [flag] [argument]\n");
		exit(-1);
	}
	if (ft_strcmp(av[1], "md5") == 0 || ft_strcmp(av[1], "sha256") == 0)
		decision_maker(&ssl, ac, av);
	else
	{
		ft_printf("ft_ssl : '%s' is an invalid\n", av[1]);
		exit(-1);
	}
	return (0);
}
