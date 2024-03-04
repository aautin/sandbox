/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:35:28 by aautin            #+#    #+#             */
/*   Updated: 2024/03/04 22:33:17 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int		ft_putchar(char letter)
{
    return (write(1, &letter, 1));
}

int		ft_putstr(const char *str)
{
    unsigned int    i;

    i = 0;
    if (str == NULL)
        return (0);
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    return (i);
}
