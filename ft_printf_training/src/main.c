/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aautin <aautin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 19:37:02 by aautin            #+#    #+#             */
/*   Updated: 2024/03/04 23:21:27 by aautin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static int  insertion(const char *format, va_list args)
{
    unsigned int    printed_char;

    if (*format == '%')
        return (write(1, "%", 1));
    if (*format == 'c')
        return (ft_putchar(va_arg(args, int)));
    if (*format == 's')
        return (ft_putstr(va_arg(args, char *)));
    if (*format == 'd' || *format == 'i')
        return (ft_putint(va_arg(args, unsigned int)));
    if (*format == 'u')
        return (ft_putuint(va_arg(args, unsigned int)));
    if (*format == 'x' || *format == 'X')
        return (ft_puthexa(va_arg(args, unsigned int), *format == 'X'));
    if (*format == 'p')
        return (ft_putadress(va_arg(args, unsigned long)));
    return (0);
}

int		ft_printf(const char *format, ...)
{
    va_list         args;
    unsigned int    i;
    unsigned int    printed_char;

    va_start(args, format);
    if (format == NULL)
        return (-1);
    printed_char = 0;
    i = 0;
    while (format[i] != '\0')
    {
        if (format[i] != '%')
            printed_char += write(1, &format[i], 1);
        else
            printed_char += insertion(&format[++i], args);
        i++;
    }
    va_end(args);
    return (printed_char);
}

int     main(void)
{
    const char  *example;
    printf("%p\n", 98769873454565);
    ft_printf("%p\n", 98769873454565);
    return (0);

}
