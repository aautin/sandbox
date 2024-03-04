/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:37:36 by aautin            #+#    #+#             */
/*   Updated: 2024/03/04 23:25:10 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_puthexa(unsigned int nbr, char maj_flag)
{
    const char  *hexa = "0123456789abcdef";
    const char  *majhexa = "0123456789ABCDEF";

    if (nbr >= 16 && maj_flag)
       return (ft_puthexa(nbr / 16, maj_flag) + ft_putchar(majhexa[nbr % 16]));
    if (nbr >= 16 && !maj_flag)
       return (ft_puthexa(nbr / 16, maj_flag) + ft_putchar(hexa[nbr % 16]));
    if (maj_flag)
        return (ft_putchar(majhexa[nbr % 16]));
    else
        return (ft_putchar(hexa[nbr % 16]));
}

static int		ft_putlonghexa(unsigned long nbr, char maj_flag)
{
    const char  *hexa = "0123456789abcdef";
    const char  *majhexa = "0123456789ABCDEF";

    if (nbr >= 16 && maj_flag)
       return (ft_putlonghexa(nbr / 16, maj_flag) + ft_putchar(majhexa[nbr % 16]));
    if (nbr >= 16 && !maj_flag)
       return (ft_putlonghexa(nbr / 16, maj_flag) + ft_putchar(hexa[nbr % 16]));
    if (maj_flag)
        return (ft_putchar(majhexa[nbr % 16]));
    else
        return (ft_putchar(hexa[nbr % 16]));
}

int		ft_putadress(unsigned long nbr)
{
    return (ft_putstr("0x") + ft_putlonghexa(nbr, 0));
}
