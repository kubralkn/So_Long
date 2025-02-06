/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:16:47 by kalkan            #+#    #+#             */
/*   Updated: 2024/11/22 13:21:53 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>
#include <stdarg.h>

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *str)
{
	int	i;

	i = -1;
	if (str == NULL)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	while (str[++i])
	{
		if (write(1, &str[i], 1) == -1)
			return (-1);
	}
	return (i);
}

static int	ft_format_check(char str)
{
	return (str == 'c' || str == 's' || str == 'p'
		|| str == 'd' || str == 'i' || str == 'u'
		|| str == 'x' || str == 'X' || str == '%');
}

static int	ft_format(va_list *args, const char a)
{
	if (a == 'c')
		return (ft_print_char(va_arg ((*args), int)));
	else if (a == '%')
		return (ft_print_char('%'));
	else if (a == 's')
		return (ft_print_str(va_arg ((*args), char *)));
	else if (a == 'd' || a == 'i')
		return (ft_print_int(va_arg ((*args), int)));
	else if (a == 'u')
		return (ft_unsigned(va_arg ((*args), unsigned int)));
	else if (a == 'p')
		return (ft_p_address(va_arg ((*args), void *), 1));
	else if (a == 'x' || a == 'X')
		return (ft_hex_numb(va_arg ((*args), unsigned long), a));
	else
		return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		len;
	int		i;
	int		result;

	len = 0;
	i = -1;
	if (!format)
		return (-1);
	va_start(arg, format);
	while (format[++i])
	{
		if (format[i] == '%' && ft_format_check(format[i + 1]))
		{
			result = ft_format(&arg, format[++i]);
			if (result == -1)
				return (-1);
			len += result;
		}
		else if (format[i] != '%' && ft_print_char(format[i]) == -1)
			return (-1);
		else if (format[i] != '%')
			len++;
	}
	return (va_end(arg), len);
}
