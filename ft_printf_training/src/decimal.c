/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:36:47 by aautin            #+#    #+#             */
/*   Updated: 2024/03/04 22:49:43 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_putint(int nbr)
{
    if (nbr == -2147483648)
        return (ft_putstr("-2147483648"));
    if (nbr < 0)
    {
        write(1, "-", 1);
        return (ft_putint(-nbr));
    }
    if (nbr > 10)
       return (ft_putint(nbr / 10) + ft_putchar((nbr % 10) + 48));
    return (ft_putchar((nbr % 10) + 48));
}

int		ft_putuint(unsigned int nbr)
{
    if (nbr > 10)
       return (ft_putint(nbr / 10) + ft_putchar((nbr % 10) + 48));
    return (ft_putchar((nbr % 10) + 48));
}
