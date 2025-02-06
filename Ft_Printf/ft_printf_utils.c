/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalkan <kalkan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 13:18:12 by kalkan            #+#    #+#             */
/*   Updated: 2024/11/22 13:19:08 by kalkan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	ft_print_int(int c)
{
	long	numb;
	int		len;
	int		temp;

	len = 0;
	numb = c;
	if (numb < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		numb *= -1;
		len++;
	}
	if (numb > 9)
	{
		temp = ft_print_int(numb / 10);
		if (temp == -1)
			return (-1);
		len += temp;
	}
	if (write(1, &"0123456789"[numb % 10], 1) == -1)
		return (-1);
	return (len + 1);
}

int	ft_unsigned(unsigned int c)
{
	int	len;
	int	tmp;

	len = 0;
	if (c >= 10)
	{
		tmp = ft_unsigned(c / 10);
		if (tmp == -1)
			return (-1);
		len += tmp;
	}
	if (write(1, &"0123456789"[c % 10], 1) == -1)
		return (-1);
	return (len + 1);
}

int	ft_hex_numb(unsigned long c, char a)
{
	int	len;
	int	tmp;

	len = 0;
	if (c >= 16)
	{
		tmp = ft_hex_numb(c / 16, a);
		if (tmp == -1)
			return (-1);
		len += tmp;
	}
	if (a == 'X')
	{
		if (write(1, &"0123456789ABCDEF"[c % 16], 1) == -1)
			return (-1);
	}
	if (a == 'x')
	{
		if (write(1, &"0123456789abcdef"[c % 16], 1) == -1)
			return (-1);
	}
	return (len + 1);
}

static int	ft_hex_null(void)
{
	if (write(1, "(nil)", 5) == -1)
		return (-1);
	return (5);
}

int	ft_p_address(void *ptr, int i)
{
	unsigned long	c;
	int				len;
	int				tmp;

	if (ptr == NULL)
		return (ft_hex_null());
	c = (unsigned long)ptr;
	len = 0;
	if (i)
	{
		if (write(1, "0x", 2) == -1)
			return (-1);
		len += 2;
	}
	if (c >= 16)
	{
		tmp = ft_p_address((void *)(c / 16), 0);
		if (tmp == -1)
			return (-1);
		len += tmp;
	}
	if (write(1, &"0123456789abcdef"[c % 16], 1) == -1)
		return (-1);
	return (len + 1);
}
